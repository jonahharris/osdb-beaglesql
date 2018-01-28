static const char  rcsfile []= "$Header: /home/magrasjc/test/src/RCS/bsql.c,v 0.87.2.1 2000/02/05 06:12:59 magrasjc Exp $";
#include <sys/time.h>
#include <netdb.h>

#include "config.h"
#include "beagle.h"
#include "sha.h"
/*

 bsql.c

 Copyright (c) 1996   Robert Klein

 Permission to use, copy, modify and distribute this software and its
 documentation, is hereby granted to educational institutions, their
 faculty, and full-time students, non-commercial research organizations,
 registered charities, and registered not-for-profit and non-profit
 organizations without fee provided that this license agreement and
 copyright information appears in all copies.

 Permission to use this software by any other person or organization 
 is hereby granted for the current version of the software and it's
 documentation provided that this license agreement and copyright
 information appears in all copies.
 
 Commercial redistribution of this software, by itself or as part of
 another application is allowed only under express written permission of
 Robert Klein and may entail licensing fees.
 
 ROBERT KLEIN DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, 
 INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO 
 EVENT SHALL ROBERT KLEIN BE LIABLE FOR ANY SPECIAL, INDIRECT OR 
 CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF 
 USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR 
 OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR 
 PERFORMANCE OF THIS SOFTWARE.
 
*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/socket.h>

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <time.h>

#include "beagle.h"
#include "commands.h"
#include "linklist.h"

int BSQLConnect (char *host,char *,unsigned long);
int BSQLSetCurrentDB (int socket, char *dbname);
char *BSQLGetCurrentDB (int socket);
void BSQLDisconnect (int socket);
struct bresult *BSQLQueryDB (int socket, char *query);
void gettuples (int socket, struct bresult *p);
long BSQLntuples (struct bresult *res);
long BSQLnfields (struct bresult *res);
char *BSQLFieldValue (struct bresult *res, long row, long col);
char *BSQLFieldName (struct bresult *res, long col);
int BSQLFieldType (struct bresult *res, long col);
char *BSQLresult (struct bresult *res);
void BSQLFreeResult (struct bresult *p);
   time_t   transmitTime;
char *BSQLservice=SERVICE;

/* connect to the server so it can fork a new process */
int BSQLConnect (char *host,char *passwd,magic_t magicNumber)
{
   extern time_t transmitTime;
   unsigned int size=sizeof(struct sockaddr);
   int ret, socket,index,df;
   struct   sockaddr AddrInfo;
   void    *memPtr;
   char length[11], hostname[MAX_HOST_NAME_LEN+1],greeter[32],negotBuff[32];
   char errcode[MAX_ERROR_LENGTH+1],username[16],*loginnameP,authconfirm[16];
   unsigned char pcktBuffer[512]="101\n\r00",SHAbuffer[65536],temp[48];
   struct sha_info      ShaBlock;

   if (gethostname (hostname, MAX_HOST_NAME_LEN))
      hostname[0]='\0';

   socket = connectTCP(host, BSQLservice);

   if (socket!=-1 && (loginnameP=getlogin())!=NULL) {
      strcpy(username,loginnameP);
      ret = read(socket,greeter,27);
      /*
          42 for  SHA string (40 chars + newline+cr each)
          2 for packet length's cr+nl
          27=gmtimes 26 char output(includes nl) + cr
          2 for username's cr+nl
       */
      sprintf(&pcktBuffer[7],"%2.2x\n\r%s\n\r",42+strlen(username)+2+26+2,username);
      getsockname(socket,&AddrInfo,&size);
      time(&transmitTime);
      strcat(pcktBuffer,asctime(localtime(&transmitTime)));
      strcat(pcktBuffer,"\r");

      SHAbuffer[4]=SHAbuffer[5]=SHAbuffer[6]=SHAbuffer[7]=0x5c;
      SHAbuffer[12]=SHAbuffer[13]=SHAbuffer[14]=SHAbuffer[15]=0x5c;
      memcpy(SHAbuffer,&magicNumber,sizeof(unsigned long));
      memcpy(&SHAbuffer[8],&transmitTime,sizeof(time_t));

      for (memPtr=SHAbuffer+65514;
             memPtr<SHAbuffer+65536;
             *((char*)memPtr++)=0x5c);
      for (memPtr=SHAbuffer+16;
	   memPtr < SHAbuffer+65536-strlen(username)-strlen(passwd)/*-sizeof(AddrInfo.sin_port)-sizeof(AddrInfo.sin_port)*/-6;
	   memPtr+=2/*sizeof(AddrInfo.sin_port)*/) {
        memcpy(memPtr,username,strlen(username));
        memPtr += strlen(username);
        memcpy(memPtr,passwd,strlen(passwd));
        memPtr += strlen(passwd);
        memcpy(memPtr,  &AddrInfo.sa_data[2],
	       4/*sizeof(AddrInfo.sin_addr.s_addr)*/);
        memPtr +=4/* sizeof(AddrInfo.sin_addr.s_addr)*/;
        memcpy(memPtr,&AddrInfo.sa_data[0],2/*sizeof(AddrInfo.sin_port)*/);
      }

   df=open("clientdebug",O_CREAT|O_RDWR);
   write(df,SHAbuffer,65536);
   close(df);

      sha1Initial(&ShaBlock);
      sha1Update(&ShaBlock,SHAbuffer,65536);
      sha1Final(&ShaBlock);

      sprintf(temp,"%8.8x%8.8x%8.8x%8.8x%8.8x\n\r",
                ShaBlock.digest[0],
                ShaBlock.digest[1],
                ShaBlock.digest[2],
                ShaBlock.digest[3],
                ShaBlock.digest[4]);
      fprintf (stderr,"%8.8x%8.8x%8.8x%8.8x%8.8x\n\r",
                ShaBlock.digest[0],
                ShaBlock.digest[1],
                ShaBlock.digest[2],
                ShaBlock.digest[3],
                ShaBlock.digest[4]);
      strcat(pcktBuffer,temp);


      write(socket,pcktBuffer,strlen(pcktBuffer));
      read(socket,authconfirm,6);
      if (authconfirm[0]=='A' && (authconfirm[1] & authconfirm[2]) =='C');
      if (authconfirm[0]=='R' && authconfirm[1] == 'E' && authconfirm == 'J')
          return -1;
      write(socket,"WILL USE VERSION 2\n\r",20);
      read(socket,negotBuff,18);
      write(socket,"WILL USE VERSION 2\n\r",20);
      read(socket,negotBuff,18);

      if (ret <0)
          return ret;
      
      /* send the length of the data 
      sprintf (length, "%10d", strlen(loginnameP));
      if ((ret = write(socket, length, LENSIZE)) == -1) 
         fprintf (stdout, "%s\n", STRERROR); */

      /* send the login name 
      if (ret!=-1 && (ret=write(socket, getlogin(), strlen(getlogin()))) == -1) 
         fprintf (stdout, "%s\n", STRERROR); */

      /* send the length of the data 
      sprintf (length, "%10d", strlen(hostname));
      if (ret!=-1 && (ret = write(socket, length, LENSIZE)) == -1) 
         fprintf (stdout, "%s\n", STRERROR);*/

      /* send the host name 
      if (ret!=-1 && (ret = write(socket, hostname, strlen(hostname))) == -1) 
         fprintf (stdout, "%s\n", STRERROR);
        */
      /*if (ret!=-1) {
         ret = read (socket, errcode, MAX_ERROR_LENGTH);
         errcode[ret] = '\0';
         if (strncasecmp (errcode, "OK", 2))
            ret=-1;
      } */

      if (ret==-1) {
         BSQLDisconnect (ret);
         socket=ret;
      }
   }
   return socket;
}

int BSQLSetPassword(int clientSocket,int version,char *changes[5])
{
    char                 sendbuffer[1024];
    char                 SHAbuffer[65536],*ptr,*endP;
    struct sha_info      ShaBlock;
    time_t               stamp;
    unsigned int         index,length;
    char                 response[1024];
    magic_t magicno=MAKE_MAGIC

      /* salt ..err magic */
    memcpy (SHAbuffer,&magicno,sizeof(magic_t));
    /* stamp */
    memcpy (&SHAbuffer[sizeof(magic_t)],&transmitTime,sizeof(time_t));

    time(&stamp);

    /* copy changee's name */
    strcpy(ptr=&SHAbuffer[sizeof(magic_t)+sizeof(time_t)],changes[0]);

    ptr+=strlen(changes[0]);

    /* copy old password*/
    strcpy(ptr,changes[2]);

    ptr+=strlen(changes[2]);

    /* copy new password*/
    strcpy(ptr,changes[3]);

    ptr+=strlen(changes[3]);
    
    /*copy changer's name */
    endP=strcat(ptr,changes[1]);
    ptr+=strlen(changes[1]);

    /*copy current time stamp*/
    memcpy(ptr,&stamp,sizeof(time_t));
    ptr+=sizeof(time_t);

    sha1Initial(&ShaBlock);
    sha1Update(&ShaBlock,SHAbuffer,65536);
    sha1Final(&ShaBlock);

    sprintf(sendbuffer,
       "p101\n\r%4.4x\n\r%s\r%s\n\r%s\n\r%s\n\r%8.8x%8.8x%8.8x%8.8x%8.8x\n\r",
       length=42+26+strlen(changes[0])+strlen(changes[2])+strlen(changes[3])+7,
              asctime(localtime(&stamp)),changes[0], changes[2],changes[3],
              ShaBlock.digest[0],ShaBlock.digest[1],ShaBlock.digest[2],
              ShaBlock.digest[3],ShaBlock.digest[4]);
    write(clientSocket,sendbuffer,length+10);
    if (read (clientSocket,response,6)>0)
    { 
       if (response[0]=='A' && ((response[1] | response[2]) =='C'))
           return 0;

    }
    return 1;
}

/* Set the current database. Further request to the SQL server will act upon
   this database until another call to BSQLSetCurrentDB is made.
*/
int BSQLSetCurrentDB (int socket, char *dbname)
{
  char length[11], request[256];
  size_t err;
  struct bresult *res;


  sprintf (request, "select * from sys_db where sys_db_name = '%s' ", dbname);
  res = BSQLQueryDB (socket, request);
  if (!BSQLntuples(res)) {
     fprintf (stdout, "Database '%s' doesn't exist\n", dbname);
     return 0;
  }
  BSQLFreeResult(res);

  /* set current database name */
  if ((err = write(socket, MSG_SETDB, (size_t) CMDSIZE)) == -1) { 
     fprintf (stdout, "%s\n", STRERROR);
     return 0;
  }
  sprintf (length, "%10d", strlen(dbname));
  /* send the length of the data */
  if ((err = write(socket, length, LENSIZE)) == -1) {
     fprintf (stdout, "%s\n", STRERROR);
     return 0;
  }

  /* send the name of the database */
  if ((err = write(socket, dbname, strlen(dbname))) == -1) {
     fprintf (stdout, "%s\n", STRERROR);
     return 0;
  }
  return 1;
}


char *BSQLGetCurrentDB (int socket)
{
  static char dbname[MAXIDSIZE];
  int c;

  write(socket, MSG_GETDB, CMDSIZE);   /* send request for the current dbname */
  c = read(socket, dbname, MAXIDSIZE-1);   /* get the current dbname */
  dbname[c] = '\0';
  return dbname;
}


/* Disconnect and cleanup */
void BSQLDisconnect (int socket)
{
   write(socket, MSG_EXIT, CMDSIZE);   /* send exit request */
}


/* Send a Query to the Server.  Must first select a database with 
   BSQLSetCurrentDB().  Returns a pointer to the result structure
   for the query.  NOTE: You must free the memory allocated by this
   function
*/
struct bresult *BSQLQueryDB (int socket, char *query)
{
   char length[11];
   struct bresult *p=NULL;
   int i, c;

   if ((p = (struct bresult *) malloc (sizeof (struct bresult))) == NULL) {
      fprintf (stderr, "\nCan't Allocate Memory for Query Result");
      return NULL;
   } 
   p->fields = NULL;
   p->f_last = NULL;
   p->f = NULL;
   p->values = NULL;
   p->v_last = NULL;
   p->v = NULL;
   p->next = NULL;

   write(socket, MSG_QUERY, CMDSIZE); /* I'm sending a Query string */
   sprintf (length, "%10d", strlen(query));
   write(socket, length, LENSIZE);              /* send the length of the data */
   write(socket, query, strlen(query));       /* send the query string */

   for (i=0; i<NUMCMDS; i++)
      if (!strncasecmp (query, table[i].cmd, strlen(table[i].cmd)))
         break;

   c = read (socket, p->errcode, MAX_ERROR_LENGTH-1);
   p->errcode[c] = '\0';
   if (strncasecmp (p->errcode, "OK", 2))
      p->resultcode=0;  /* an Error occured */
   else
      p->resultcode=1;

   switch (i) {
      case CREATE_TABLE:  break;
      case DROP_TABLE:    break;
      case INSERT_INTO:   break;
      case SELECT:        if (p->resultcode)
                             gettuples (socket, p);
                          break;
   }
   return p;
}


/* Retrieve Tuples from the Server */
void gettuples (int socket, struct bresult *p)
{
   struct bfield *fptr=NULL;
   char temp[LENSIZE+1], *buf=NULL, *s; 
   char fname[MAXIDSIZE], type[LENSIZE];
   int c;
   long i, j,fType;

   write(socket, MSG_GETNTUPLES, CMDSIZE); /* Send me Number of Tuples */
   do {
   c = read (socket, temp, LENSIZE);
   } while (c==-1 && errno==EAGAIN); 
   temp[c] = '\0';
   p->ntuples = atol (temp);

   write(socket, MSG_GETNFIELDS, CMDSIZE); /* Send me Number of Tuples */
   c = read (socket, temp, LENSIZE);
   temp[c] = '\0';
   p->nfields = atol (temp);

   /* Get the Field Name */
   for (i=0L; i<p->nfields; i++) {
      if (i==0L)
         write(socket, MSG_FIRSTFIELD, CMDSIZE);
      else
         write(socket, MSG_NEXTFIELD, CMDSIZE); 

      /* get the field name length */
      c = read (socket, temp, LENSIZE);
      temp[c] = '\0';

      /* get the field name */
      c = read (socket, fname, atol(temp));
      fname[c] = '\0';

      /* get the field type */
      c = read (socket, type, LENSIZE);
      type[c] = '\0';

      /* Allocate Field Pointer */
      fptr = field_node (fname, "", NULL, atoi(type), -1);
      if (fptr == NULL)
         fprintf (stdout, "Memory Allocation Error in Client Process while creating field node\n");
      else {
         if (p->fields == NULL)  /* save the head of the fields list */
            p->fields = fptr;
         p->f_last = store_field_list (fptr, p->f_last);
      }
   }

   for (i=0L; i<p->ntuples; i++) {
      if (i==0L)
         write(socket, MSG_FIRSTTUPLE, CMDSIZE);
      else
         write(socket, MSG_NEXTTUPLE, CMDSIZE); 

      /* Get the Field Values */
      for (j=0L; j<p->nfields; j++) {
         /* get the length of the field to follow */
         int dataSize;
         c = read (socket, temp, LENSIZE);
         fType = BSQLFieldType(p,j);
         temp[c] = '\0';
         buf = (char *) realloc (buf, atol (temp)+1L);
         dataSize = atol(temp);
         if (buf != NULL) {
            /* get the field data */
            c = read (socket, buf, atol(temp));
            buf[c] = '\0';
            if (fType==FTYPE_CHAR) {
                s = buf;
                if (*s == '\'') s++;
                if (s[strlen(s)-1] == '\'') s[strlen(s)-1] = '\0';
                fptr = field_node ("", "", s, 0, -1);
            } else if (fType==FTYPE_INT||fType==FTYPE_OID) {
                unsigned long temp=atol(buf);
                buf = (char *) realloc (buf, sizeof(long));
                memcpy(buf,&temp,sizeof(long));
                fptr = field_node ("", "", buf, 1, -1);
            } else if (fType==FTYPE_TIME||fType==FTYPE_DATE||fType==FTYPE_TIMESTAMP) {
                fptr = field_node ("", "", buf, fType, -1);
            } else lprintf ("gettuples: unknown field type %d",fType);
            /* Allocate Field Pointer */
            if (fptr == NULL)
               fprintf (stdout, "Memory Allocation Error in creating unnamed field in Client Process\n");
            else {
               if (p->values == NULL)  /* save the head of the fields list */
                  p->values = fptr;
               p->v_last = store_field_list (fptr, p->v_last);
            }
         }
         else
            fprintf (stdout, "Memory Allocation Error of  %s %d bytes in Client Process\n",temp,atol(temp)+1L);
      }
   }
 
   if (buf!=NULL)
      free(buf);
}



/* return the number of tuples (records) found
*/
long BSQLntuples (struct bresult *res)
{
   return res->ntuples;
}

/* return the number of fields per tuple returned
*/
long BSQLnfields (struct bresult *res)
{
   return res->nfields;
}

/* return the value of the field at row, col
*/
char *BSQLFieldValue (struct bresult *res, long row, long col)
{
   struct bfield *p;
   long i, j;

   if (row >= res->ntuples) return NULL;
   if (col >= res->nfields) return NULL;

   p = res->values;   
   for (i=0L; i<row; i++)
      for (j=0; j<res->nfields; j++)
         p=p->next;
   for (j=0; j<col; j++) 
      p=p->next;
   return p->value;
}


/* return the field name
*/
char *BSQLFieldName (struct bresult *res, long col)
{
   struct bfield *p;
   long j;

   if (col >= res->nfields) return NULL;

   p = res->fields;   
   for (j=0; j<col; j++) 
      p=p->next;
   return p->fname;
}


/* return the field type
*/
int BSQLFieldType (struct bresult *res, long col)
{
   struct bfield *p;
   long j;

   if (col >= res->nfields) return ERROR;

   p = res->fields;   
   for (j=0L; j<col; j++) 
      p=p->next;
   return p->type;
}


/* return the message that refers to the result of the query
*/
char *BSQLresult (struct bresult *res)
{
   return res->errcode;
}


void BSQLFreeResult (struct bresult *p)
{
   struct bresult *pp;
   struct bfield *q;

   for (pp=p; pp!=NULL;) {
      p = pp->next;
      for (q=pp->fields; q!=NULL;) {
         pp->f = q->next;
         if (q->value != NULL) free (q->value);
         free (q);
         q=pp->f;
      }
      for (q=pp->values; q!=NULL;) {
         pp->f = q->next;
         if (q->value != NULL) free (q->value);
         free (q);
         q=pp->f;
      }
      free (pp);
      pp = p;
   }
}
