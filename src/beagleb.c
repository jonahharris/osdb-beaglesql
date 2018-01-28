static const char  rcsfile []= "$Header: /home/magrasjc/test/src/RCS/beagleb.c,v 0.87.2.1 2000/02/05 06:12:55 magrasjc Exp $";
/*
      
 beagleb.c
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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <sys/errno.h>

#include <termios.h>
#include <time.h>
#include <stddef.h>
#include <unistd.h>
#include <ctype.h>

#include "beagle.h"
#include "store.h"
#include "parse.h"
#include "log.h"
#include "filesys.h"
#include "commands.h"
#include "errexit.h"
#include "linklist.h"
#include "bt.h"
#include "sockio.h"
#include "mymalloc.h"
#include "sha.h"
#include "auth.h"

#ifndef HAVE_GETDATE
#include"getdate.h"
#endif
#include "sr.h"


#define YES 1
#define NO  0

#define	BUFSIZE		2


extern char     syncBuffer[];
extern int	errno;
/* Chagnes in the new GNU headers forced this */
/* #ifndef __FreeBSD__ */
/* #ifndef PORT_LINUX */
/*extern char	*sys_errlist[];*/
/* #endif */
/* #endif */

char *getCurrentDB();
char *querystr=NULL;
size_t querystr_size=0;

/* Acceptable Datatypes */
char *btypes[] = {
   "char",
   "integer",
   "float",
   "blob",
   "time",
   "date",
   "timestamp",
   NULL
};

/* Error Statements can't be greater then MAX_ERROR_LENGTH - 1 */
char *berrors[] = {
   "Syntax Error",
   "Exceeded Maximum Identifier Length",
   "Statement Missing '('",
   "Bad Identifier Name",
   "Statement Missing ')'",
   "Invalid Field Type",
   "Incomplete Query Statement",
   "Can't Drop Table",
   "'VALUES' Clause Expected",
   "Can't Read Table information",
   "Memory Allocation Error",
   "Bad Delimiter Found in List",
   "Table Not Found",
   "Ambiguous Field Name, Can't Resolve Fully Qualified Name",
   "Keyword 'ON' Expected",
   "Keyword 'USING' Expected",
   "Invalid Field Name"
};

int  ssock;         /* slave server socket */
struct bresult search_result = {0,0L,0L,"",NULL,NULL,NULL,NULL,NULL,NULL,NULL};

int beagleb();
void setdb();
void getdb();
void query();
void sendntuples(struct bresult *sr);
void sendnfields(struct bresult *sr);

int SQLcreate (struct clist *tokens); 
int SQLindex (struct clist *tokens); 
int getinttype (char *fs);          
int SQLdrop (struct clist *tokens);   
int SQLdropindex (struct clist *tokens);  
int SQLinsert (struct clist *tokens); 
int SQLselect (struct clist *tokens, struct bresult *sr);
int SQLdelete (struct clist *tokens, struct bresult *sr);
int SQLupdate (struct clist *tokens, struct bresult *sr);
void  setpasswd ();
int strcmpfld (char *fname, struct bfield *fptr);     /* compare field names */
int fldcmpfld (struct bfield *f1, struct bfield *f2); /* compare field names */ 

int SQLsearch (struct clist *tokens, struct btable *ptr, int action, struct bresult *sr); /* execute search */

/* merge two tables into a new one */
struct btable *mergetables (struct btable *outer, struct btable *inner, int free_t1); 

/* build joined table */
int build_joined_table (struct btable *tptr); 

/* send info for the 1st fld to client */
void first_field(struct bresult *sr);        

/* send info for the next fld to client */
void next_field(struct bresult *sr);        

/* send first tuples to client */
void first_tuple(struct bresult *sr);      

/* send next tuple to client */
void next_tuple(struct bresult *sr);

/* Send notice of a Syntax Error in the Query */
int syntax_error (int err);        

/* check for reserved words */
int isres (char *s);

/* check for valid id name */
int checkidentifier (char *s);

/* check to see if the table exists */
int table_exists (char *tname);

int min(char *s1, char *s2);



int main(int argc, char *argv[])
{
   int err;

   tzset();
   if (argc != 2) 
      errexit("usage: beagleb [file descriptor] %d\n", argc);

   ssock = atoi (argv[1]);

   /* Initialize search_result structure */
   sr_initresult(&search_result);

   start_logging();
   lprintf ("File Descriptor Passed %d", ssock);
   err = beagleb();
   lprintf ("Exiting Child Process");
   lprintf ("All Done.");
   stop_logging();
   exit (err);
}
static char databasename[16];
char * getCurrentDB()
{
  return databasename;
}
void setCurrentDB(char *newName)
{
  if (NULL != newName)
  strcpy(databasename,newName);

}
int beagleb()
{
   char buf[CMDSIZE+1],negotMSG[64];
   int cc, msg;

   write(ssock,"BON JOUR. CEST LE BEAGLE\n",25);
   if (auth(ssock)) {  /* user authorization */
      cc = sock_recv (ssock, negotMSG, 20) ;
      if (!cc)
         lprintf ("error while receiving options");
      if (strcmp(negotMSG,"WILL USE VERSION 2\n\r")==0) {
         strcpy (negotMSG,"DO USE VERSION 2\n\r");
         cc = write(ssock,negotMSG,18);
         if (!cc) {
             lprintf ("OOPS, sock send error occured");
           
         } 
      } else {
         lprintf ("bad negotiation message:%s",negotMSG);
      }
      cc = sock_recv (ssock, buf, 20) ;
      if (cc<0) {
         lprintf ("error while receiving options: %s",STRERROR);
         
      }
      if (strcmp(buf,"WILL USE VERSION 2\n\r")==0) {
         strcpy (buf,"DO USE VERSION 2\n\r");
         cc = write(ssock,buf,16);
         if (!cc) {
             lprintf ("OOPS, sock send error occured:%s",STRERROR);
           
         } 
      } else {
         lprintf ("bad negotiation message:%s",negotMSG);
      }
      while ( (cc = sock_recv (ssock, buf, CMDSIZE)) != 0 ) {

         lprintf ("Received %d bytes '%s'", CMDSIZE, buf);

         msg = buf[0];

         /* the following codes are defined in messages.h */
         switch (msg) {
            case 'c': setdb();		        break;
            case 'd': getdb();	 	        break;
            case 'e': sr_initresult(&search_result); 
                      query();		        break;
            case 'j': sendntuples(&search_result);	break;
            case 'k': sendnfields(&search_result);	break;
            case 'f': first_field(&search_result);	break;
            case 'g': next_field(&search_result);	break;
            case 'h': first_tuple(&search_result);	break;
            case 'i': next_tuple(&search_result);	break;
            case 'p': setpasswd();	break;
            case 's': return 1;	break;   
            case 'l': break;
         }
         if (msg == 'l') break;
      }

      if (!cc)
         lprintf ("OOPS, socket read error occured");
   }

   if (getCurrentDB()!=NULL) setCurrentDB(NULL);

   if (querystr!=NULL) myfree (querystr);
   querystr=NULL;

   /* initialize search_result structure */
   sr_initresult(&search_result);

   /* clean up allocated memory from the filesys routines */
   clean_filesys();

   return 0;
}



/* Set Database Name */
void setdb()
{
   char buf[LENSIZE+1];
   int cc;
   long len;

   lprintf ("Set current database command recieved");

   /* Read the length of the data to follow */
   cc = sock_recv(ssock, buf, LENSIZE);
   if (cc < 0) errexit("echo read setdb1: %s\n", STRERROR);

   len = atol (buf);

   /* allocate enough space to store the data */
   setCurrentDB( (char *) myrealloc (getCurrentDB(), (size_t) (len+1L)));

   /* read the name of the database */
   cc = sock_recv(ssock, buf, (size_t) len);
   if (cc < 0) errexit("echo read setdb2: %s\n", STRERROR);
   setCurrentDB(buf);
   lprintf ("Read db name '%s'", getCurrentDB());
}


/* Get Database Name */
void getdb ()
{
   lprintf ("Get current database command recieved");
   write (ssock, getCurrentDB(), strlen (getCurrentDB()));
   lprintf ("Sending current database name '%s'", getCurrentDB());
}

/* change passwd */
void setpasswd()  
{
   extern int getdate_err;
  /*
   name doing the changing of the password
   name whose password is being changed
   old password
   new password

   SHA-1 code of a) name doing the changing, and
   if a == beagle and name being changed is not beagle then
          this field is special marker
     else this field is old password.
   */
   int cc,authMethID,CryptMethID,ProtocolVer,length;
   LONG hash[5];
   char header[16],packet[1024],timestamp[48]; 
   char newpassword[16],oldpassword[16],changee[16];
   char username[16],shaBuff[65536],*ptr;
   struct sha_info      ShaBlock;
   struct tm           *dateP;
   time_t               sendTime;
   magic_t              magicno=MAKE_MAGIC

   cc = sock_recv(ssock,header,(size_t) 11);
   sscanf(header,"%1.1d%1.1d%1.1d\n\r%4.4x\n\r",
              &authMethID,&CryptMethID,&ProtocolVer,&length);

   cc = sock_recv(ssock,packet,(size_t)length-2 );

   memcpy(shaBuff,&magicno,4);
   memcpy(&shaBuff[4],syncBuffer,4);

   sscanf (packet,"%s\r%s\n\r%s\n\r%s\n\r%8.8x%8.8x%8.8x%8.8x%8.8x\n\r",
       timestamp,changee,oldpassword,newpassword,
       hash[0],hash[1],hash[2],hash[3],hash[4]);
   dateP = getdate(timestamp);
   if (!dateP)
      lprintf ("getdate did not work:%d.",getdate_err);
   else 
      lprintf("getdate worked");
   sendTime =  mktime(dateP);

   strcpy(ptr=&shaBuff[sizeof(magic_t)+sizeof(time_t)],changee);
   ptr+=strlen(changee);

   strcpy(ptr,oldpassword);
   ptr += strlen(oldpassword);

   strcpy(ptr,newpassword);
   ptr += strlen(newpassword);

   memcpy(ptr,&sendTime,sizeof(time_t));
   sha1Initial(&ShaBlock);
   sha1Update(&ShaBlock,shaBuff,65536);
   sha1Final(&ShaBlock);

   if (strcmp(BG_user,"beagle")==0 )
   {
            


   } 
   else if (strcmp(changee,BG_user)==0)
     {

     }
}

/* Accept Query */
void query ()
{
   char buf[LENSIZE+1], *p;
   int cc, i, ok;
   long len;
   struct clist *tokens=NULL, *t=NULL;

   lprintf ("Database Query recieved");

   /* Read the length of the data to follow */
   cc = sock_recv(ssock, buf, LENSIZE);
   if (cc < 0) errexit("echo read query1: %s\n", STRERROR);

   len = atol (buf);

   lprintf ("Read data length '%ld'", len);
   
   /* allocate enough space to store the data */
   querystr_size = (size_t) len+1L;
   querystr = (char *) myrealloc (querystr, querystr_size);

   /* read the name of the database */
   cc = sock_recv(ssock, querystr, (size_t) len);
   if (cc < 0) errexit("echo read query2: %s\n", STRERROR);

   lprintf ("Read query '%s'", querystr);

   for (p=NULL, i=0; i<NUMCMDS;i++)
      if (!strncasecmp (querystr, table[i].cmd, strlen(table[i].cmd))) {
         /* position pointer passed the command */
         p = querystr + strlen (table[i].cmd);  
         break;
      }

   if (p != NULL)
      tokens = parse_tokens (p);  /* parse the remaining tokens into a linked list */
   if (tokens == NULL)
      lprintf ("ERROR: Couldn't parse list");
      
   lprintf ("Displaying Parse List");
   for (t=tokens; t!=NULL; t=t->next)
      lprintf ("   Token: %s", t->token);

   switch (i) {
      case CREATE_TABLE:  ok = SQLcreate (tokens);
                          break;
      case CREATE_INDEX:  ok = SQLindex (tokens);
                          break;
      case DROP_TABLE:    ok = SQLdrop (tokens);
                          break;
      case DROP_INDEX:    ok = SQLdropindex (tokens);
                          break;
      case INSERT_INTO:   ok = SQLinsert (tokens);
                          break;
      case SELECT:        ok = SQLselect (tokens, &search_result);
                          break;
      case DELETE:        ok = SQLdelete (tokens, &search_result);
                          break;
      /*case UPDATE:        ok = SQLupdate (tokens, &search_result);
                          break; */
      default:            syntax_error (GENERAL);
                          ok = NO;
   }

   /* if the query executed succesfully notify the client */
   if (ok)  {
      lprintf ("Trying to send OK to client");
      if (write (ssock, "OK", 2) != 2) {
         fprintf (stderr, "\nERROR %s\n", STRERROR);
         lprintf ("Can't send OK to client");
      }
      else
         lprintf ("Sent OK to client");
   }

   /* free nodes in token list */
   free_tokens (tokens);
}



void sendntuples (struct bresult *sr)
{
   char temp[81];

   sprintf (temp, "%10.10ld", sr->ntuples);
   write (ssock, temp, 10);
}


void sendnfields (struct bresult *sr)
{
   char temp[81];

   sprintf (temp, "%10.10ld", sr->nfields);
   write (ssock, temp, 10);
}



int SQLcreate (struct clist *tokens)
{
   struct btable *tptr=NULL;
   struct bfield *fptr=NULL;
   struct clist *t;
   int err=NO;

   lprintf ("Starting to Parse CREATE TABLE");

   t=tokens;

   /* make sure that this is a valid identifier name */
   if (checkidentifier (t->token) == ERROR)
      err = syntax_error (BADID);
   /* verify that a '(' follows the name */
   else if (t->next != NULL && t->next->token[0] != '(')
      err = syntax_error (OPENING_PAREN);
   else {

      if ((tptr=table_node (t->token))==NULL)
         err = syntax_error (MEMORY);
      else {

         lprintf ("Table Name: %s", tptr->name);

         t=t->next;   /* move past the table name */

         if ((t=t->next) == NULL) /* move past the '(' */
            err = syntax_error (INCOMPLETE);

         /*********************************************************************
            BEGIN System field section.  All Tables must include certain system
            fields like OID
         */

         /* Allocate Field Pointer */
         fptr = field_node ("oid", tptr->name, NULL, FTYPE_OID, -1);
         if (fptr != NULL) 
            tptr->fields = fptr; /* This will be the head of the list */
         else 
            err = syntax_error (MEMORY);
         tptr->f_last = store_field_list (fptr, tptr->f_last);

         /* 
            END System field section
         **********************************************************************/
      }

      /* step through the field definitions */
      for (;err==NO && t!=NULL && t->token[0] != ')';) {

         /* check max identifier length for the field name */
         if (strlen (t->token) > MAXIDSIZE-1) {
            err = syntax_error (IDLENGTH);
            break;
         }

         /* Allocate Field Pointer */
         fptr = field_node (t->token, tptr->name, NULL, FTYPE_CHAR, -1);
         if (fptr == NULL) {
            err = syntax_error (MEMORY);
            break;
         }

         lprintf ("Field Name: %s", t->token);

         if ((t=t->next) == NULL) {  /* move past the field name */
            err = syntax_error (INCOMPLETE);
            break;
         }

         lprintf ("Field Type: %s", t->token);

         /* get the enumerated value of the field type ref'd by 'token' */
         fptr->type = getinttype (t->token);  
        
         if (fptr->type == ERROR) {  /* test for valid field type id */
            err = syntax_error (BADFIELDTYPE);
            break;
         }

         if ((t=t->next) == NULL) { /* move past the field type identifier */
            err = syntax_error (INCOMPLETE);
            break;
         }

         /* PLACE ADDITIONAL TYPE IDENTIFICATION HERE ex char (20) */

         tptr->f_last = store_field_list (fptr, tptr->f_last);
         fptr=NULL;

         if (t->token[0] == ',') {
            if ((t=t->next) == NULL)  /* move past the ',' */
               err = syntax_error (INCOMPLETE);
            continue;  /* process the next field */
         }

      }
   }

   lprintf ("Parse Completed, Displaying Results...");
   if (!err) {
      lprintf ("Table Name '%s'", tptr->name);

      if (!puttableinfo (tptr))
         lprintf ("Can't create Table");
   }

   lprintf ("Freeing up Memory...");

   myfree (fptr);

   /* free nodes in table list */
   free_table (tptr);

   if (err) return 0;
   return 1;
}


int SQLindex (struct clist *tokens)
{
   struct btable *tptr=NULL;
   struct bfield *fptr=NULL, *fptr2=NULL;
   struct bindex *iptr=NULL;
   struct clist *t, *tt;
   char path[256], indexstr[512], *p, *q, *r;
   char iname [MAXIDSIZE];
   int err=NO, next=NO, found=NO;
   long rec_offset;
   FILE *fp;
   int match;

   lprintf ("Starting to Parse CREATE INDEX");

   t=tokens;

   /* make sure that this is a valid identifier name */
   if (checkidentifier (t->token) == ERROR)
      err = syntax_error (BADID);
   /* verify that a 'on' follows the name */
   else if (t->next == NULL || (t->next != NULL && strcasecmp (t->next->token, "on")))
      err = syntax_error (KEYWORD_EXPECTED_ON);
   else {

      strcpy (iname, t->token);  /* save the index name */
      lprintf ("Index Name: %s", iname);

      t=t->next;   /* move past the index name */

      if ((t=t->next) == NULL) /* move past the 'ON' keyword */
         err = syntax_error (INCOMPLETE);
      else {
         tptr = gettableinfo (t->token);

         if (tptr == NULL) {
            err = syntax_error (GETTABLE);
            if (err) return 0; 
         }
         else {
            lprintf ("Table Name: %s", tptr->name);

            iptr = index_node (iname, tptr->name);

            if ((t=t->next) == NULL) /* move past the table name */
               err = syntax_error (INCOMPLETE);

            if (strcasecmp (t->token, "using"))
               err = syntax_error (KEYWORD_EXPECTED_USING);

            if ((t=t->next) == NULL) /* move past the 'USING' keyword */
               err = syntax_error (INCOMPLETE);

            /* check for valid field names */
            for (tt=t; tt!=NULL; tt=tt->next) {
               found=NO;
               for (fptr=tptr->fields; fptr!=NULL; fptr=fptr->next) {
                   if (!ispunct(tt->token[0]))
                      lprintf ("ROB: %s %s", tt->token, fptr->fname);
                   if (ispunct(tt->token[0]) || !strcmp (tt->token, fptr->fname)) {
                      found=YES;
                      break;
                   }
               }
               if (!found) {
                  err = syntax_error (INVALID_FIELD);
                  break;
               }
            }

            /* step through the field definitions */
            for (;err==NO && t!=NULL;) {

               /* check max identifier length for the field name */
               if (strlen (t->token) > MAXIDSIZE-1) {
                  err = syntax_error (IDLENGTH);
                  break;
               }

               /* Allocate Field Pointer */
               fptr = field_node (t->token, tptr->name, NULL, FTYPE_CHAR, -1);
               if (fptr == NULL) {
                  err = syntax_error (MEMORY);
                  break;
               }

               if (iptr->fields == NULL)  /* save the head of the fields list */
                  iptr->fields = fptr;

               lprintf ("Field Name: %s", t->token);

               iptr->f_last = store_field_list (fptr, iptr->f_last);

               t=t->next;  /* move past the field name */

               if (t!=NULL && t->token[0] == ',')
                  if ((t=t->next) == NULL)  /* move past the ',' */
                     err = syntax_error (INCOMPLETE);
            }
         }
      }
   }

   if (!err) {
      lprintf ("Adding index to table information...");
      putindexinfo (iptr);     /* create index header file */
      appendindexinfo (iptr);  /* add index to table header file */

      /* Free field list for table */
      /*free_field (tptr->fields);*/

      /* point table field list to the index field list (used when inserting
         existing information into the index */
      /*tptr->fields = iptr->fields;
      tptr->nfields = 0L;
      iptr->fields = NULL; */

      lprintf ("Parse Completed, Displaying Results...");
      lprintf ("Index Name '%s'", iptr->iname);
      lprintf ("   on table '%s'", iptr->tname);
      lprintf ("   using fields");
      for (fptr=iptr->fields; fptr!=NULL; fptr=fptr->next) {
         lprintf ("      %s", fptr->fname);
         /*tptr->nfields++;*/
      }
      sprintf (path, "%s/%s/%s", DBROOT, getCurrentDB(), iptr->iname); 
      bt_driver ('n', path);  /* create index */

      /* Add already existing record to the index file, stepping through
         the Data file sequentially.
      */

      /* open sequential index for the table */
      fp = bg_fopen (getCurrentDB(), tptr->iname, ".seq", "rb"); /* open Index file that will be used for this search */
      if (fp==NULL)
         lprintf ("ERROR: Can't open Index file");
      else {
         bt_driver ('o', path);   /* open empty index file */

         for (;;) {
            if (!next) {
               if ((rec_offset = read_first (fp, tptr, NULL, NONE,&match)) == ERROR)
                  break;
               next = YES;
            } 
            else
               if ((rec_offset = read_next (fp, tptr, NULL, NONE,&match)) == ERROR) {
                  lprintf ("SHOULD BREAK");
                  break;
               }

            lprintf ("Read Successfull");

            memset (indexstr, ' ', 256); /* initialize to spaces */

            /* add existing records to index */
            p = indexstr;
            for (fptr=iptr->fields; fptr != NULL; fptr=fptr->next) {

               /* advance the the field in the tptr field list so to the
                  current field in the iptr list
               */         
               for (fptr2=tptr->fields; fptr2 != NULL; fptr2=fptr2->next)
                   if (!strcmp (fptr2->fname, fptr->fname))
                      break;

               /* this should never be NULL, but just in case... */
               if (fptr2!=NULL) q = (char *) fptr2->value;

               /* only allow INDEX_TOKEN_LEN characters per field in the index,
                  a bit brute force but oh well
               */
               if (*q == '\'') {  /* skip quote if there */
                  q++;
                  r = (char *) memccpy (p, q, (int) '\'', (size_t) INDEX_TOKEN_LEN); /* copy until a quote */
               }
               else
                  r = (char *) memccpy (p, q, 0, (size_t) INDEX_TOKEN_LEN);  /* copy until a NULL */

              /* if memccpy reached the 'stop' character during the operation
                  then replace that character in the destination string with a
                  space.
               */
               if (r != NULL && r != indexstr)
                  *(r-1) = ' ';

               p+=INDEX_TOKEN_LEN;  /* goto the next postion for the next index attribute */
               lprintf ("(%ld) field = '%s' value = '%s'", (long)strlen(fptr2->value)+1L, fptr2->fname, (char *)fptr2->value);
            }
            *p = '\0';
            sprintf (indexstr, "%s;%ld", indexstr, rec_offset);
            lprintf ("Index String: '%s'", indexstr);
            bt_driver ('a', indexstr); /* add to index */
         }

         bt_driver ('q', "");  /* close index */

         /* close sequential index for the table */
         bg_fclose (fp); /* close Index file used for this search */
      }
   }

   lprintf ("Freeing up Memory...");

   myfree (fptr);
   free_index (iptr);
   free_table (tptr);

   if (err) return 0;
   return 1;
}



/* get the token referenced by 'fs' */
int getinttype (char *fs)
{
   int i;
 
   for (i=0; btypes[i] != NULL; i++) 
      if (!strcasecmp (fs, btypes[i]))
         return i;
   return ERROR;
}


int SQLdrop (struct clist *tokens)
{
   struct clist *t;
   int err=NO;
   struct btable *tptr;

   lprintf ("Starting to Parse DROP TABLE");

   t = tokens;

   /* make sure that this is a valid identifier name */
   if (checkidentifier (t->token) == ERROR)
      err = syntax_error (BADID);

   if (!err) {
      tptr = gettableinfo (t->token);
      delete_table_files (tptr);  /* delete the files */
   }

   if (err)
      return 0;

   lprintf ("Freeing up Memory...");

   /* free nodes in table list */
   free_table (tptr);

   return 1;
}


int SQLdropindex (struct clist *tokens)
{
   struct clist *t;
   int err=NO;
   char path[256];

   lprintf ("Starting to Parse DROP INDEX");

   t = tokens;

   /* make sure that this is a valid identifier name */
   if (checkidentifier (t->token) == ERROR)
      err = syntax_error (BADID);

   if (!err) {
      lprintf ("Index Name '%s'", t->token);

      /* contruct file name for index header */
      sprintf (path, "%s/%s/%s", DBROOT, getCurrentDB(), t->token);
      lprintf ("Index Header Path '%s'", path);

      if (unlink ((const char *)path))
         err = syntax_error (CANTDROP);
      else {
         lprintf ("Index dropped '%s'", t->token);

         /* also drop the legacy .dat file */
         sprintf (path, "%s/%s/%s.dat", DBROOT, getCurrentDB(), t->token);
         lprintf ("Legacy DAT Path '%s'", path);
         unlink ((const char *)path);

         /* also drop tree file */
         sprintf (path, "%s/%s/%s.ndx", DBROOT, getCurrentDB(), t->token);
         lprintf ("B-Tree Path '%s'", path);
         unlink ((const char *)path);
      }
   }

   if (err)
      return 0;

   return 1;
}


int SQLinsert (struct clist *tokens)
{
   struct btable *tptr=NULL;
   struct bfield *fptr=NULL, *fptr2=NULL;
   struct bindex *iptr=NULL;
   struct clist *t;
   int err=NO;
   char tname[MAXIDSIZE];
   char path[256];
   char indexstr[512], *p, *q, *r;
   long recid;

   lprintf ("Starting to Parse INSERT INTO");

   t = tokens;

   /* make sure that this is a valid identifier name */
   if (checkidentifier (t->token) == ERROR)
      err = syntax_error (BADID);

   if (!err) {
      strcpy (tname, t->token);
      lprintf ("Table Name '%s'", tname);

      tptr = gettableinfo (tname);

      if (tptr == NULL)
         err = syntax_error (GETTABLE);
      else if ((t=t->next) == NULL)  /* move past the field type identifier */
         err = syntax_error (INCOMPLETE);
      else if (strcasecmp (t->token, "values"))
         err = syntax_error (VALUES_EXPECTED);
      else if ((t=t->next) == NULL)  /* move past the field type identifier */
         err = syntax_error (INCOMPLETE);
      else if (t->token[0] != '(') 
         err = syntax_error (OPENING_PAREN);
      else if ((t=t->next) == NULL)  /* move past the field type identifier */
         err = syntax_error (INCOMPLETE);
      else {

         /* Traverse the token list. The first item in the list should be 
            a value followed by a delimiter. Here delimiters can be a ','
            that signifies the continuation of the list or a ')' that 
            signifies the end of the list.
         */

         /* skip past the system fields */
         fptr = tptr->fields->next;

         /* Allocate space to store the recid.  This value is actually
            set in write_record() as the recid is the file position that
            the record will be inserted into.
         */
         tptr->fields->value = (long *) mymalloc (fptr->value, sizeof(long));

         while (t!=NULL && !err) {
            if (fptr->type==FTYPE_OID||fptr->type==FTYPE_INT) {
               fptr->value = (long *) mymalloc (fptr->value, sizeof(long));
               *((long *) fptr->value) = atol (t->token);
            }
            else if (fptr->type==FTYPE_CHAR) {
               fptr->value = (char *) mymalloc(fptr->value,strlen(t->token)+1L);
               memcpy (fptr->value, t->token, strlen(t->token)+1L); 
            }  else if (fptr->type==FTYPE_TIME||fptr->type==FTYPE_DATE||fptr->type==FTYPE_TIMESTAMP) {/* __NEEDDATETIMESTAMP */
               struct tm * thisDateP;struct tm aDate;
               time_t      thisTime;
               char        timeBuf[32];

               fptr->value = (char *) mymalloc(fptr->value,sizeof(time_t)+sizeof(struct tm))+BEAGLETIME_;
               lprintf ("importing time value");
               if (!strcmp(t->token,"CURRENT_TIME") ||
                      !strcmp(t->token,"CURRENT_DATE") ||
                      !strcmp(t->token,"CURRENT_TIMESTAMP")) {
                   thisTime=time(NULL);
                   lprintf ("current time from epoch: %ld",thisTime);
                   thisDateP=localtime(&thisTime),
                   memcpy(fptr->value,&thisTime,sizeof(time_t));
                   memcpy (fptr->value+sizeof(time_t),
                           thisDateP, 
                           sizeof(struct tm));
                   strftime(timeBuf,32,"%H:%M:%S",(struct tm*)thisDateP);
                   lprintf ("current date: %s",timeBuf);
               } else if (!strcmp(t->token,"DATE") ||
                          !strcmp(t->token,"TIME") ||
                          !strcmp(t->token,"TIMESTAMP")) { 
                    char *searchP;
                    t=t->next;

                   if (t->token[0]=='\'') 
                      t->token[0]=' ';
                   if ((searchP=strchr(t->token,'\''))!=NULL)
                      *searchP=' ';

                   thisDateP= getdate(t->token);
                   if (thisDateP==NULL) {
                      lprintf ("getdate_err = %d",getdate_err);
                      err = syntax_error (VALUES_EXPECTED);
                      return err;
                   }
                   thisTime  = mktime(thisDateP);  
                   memcpy (fptr->value,&thisTime,sizeof(time_t));
                   memcpy (fptr->value+sizeof(time_t), thisDateP,sizeof(struct tm));
               }
            } else if (fptr->type==FTYPE_BLOB){

            }
            fptr = fptr->next;
 
            if ((t=t->next) == NULL)  /* move past the value */
               err = syntax_error (INCOMPLETE);
            else {  /* check the delimiter */

               /* check for end of list */
               if (!strcmp (t->token, ")"))
                  break;

               /* check for a continuation of the list */
               else if (!strcmp (t->token, ",")) {

                  /* make sure there is more in the list */
                  if ((t=t->next) == NULL)  /* move past the value */
                     err = syntax_error (INCOMPLETE);

               }
               else
                  err = syntax_error (BAD_DELIMITER);
            }
         }
         /* write data to the table */
         recid = write_record (getCurrentDB(), tname, tptr->fields, NULL, NEW,0L);

         /* write record to any indexes attached to this table */
         for (iptr=tptr->indexes; iptr!=NULL; iptr=iptr->next) {
            sprintf (path, "%s/%s/%s", DBROOT, getCurrentDB(), iptr->iname); 
            bt_driver ('o', path);  /* open index */
            lprintf ("INSERT-INDEX %s", iptr->iname);

            memset (indexstr, ' ', 256); /* initialize to spaces */
            /* add existing records to index */
            p = indexstr;

            /* make the value pointers in the bindex field list point 
               to the values already malloc()'d and stored in the btable
               field list.  Needs to make sure that these values aren't
               free()'d twice BTW.
            */
            for (fptr=tptr->fields; fptr!=NULL; fptr=fptr->next) {
               for (fptr2=iptr->fields; fptr2!=NULL; fptr2=fptr2->next) {
                   lprintf ("Testing '%s' vs '%s'", fptr->fname, fptr2->fname);
                   if (!strcmp (fptr->fname, fptr2->fname))
                      fptr2->value = fptr->value;
               }
            }

            for (fptr=iptr->fields; fptr!=NULL; fptr=fptr->next) {
               /* TODO:  Need to make alowances for non string data here */
               if (fptr->type==FTYPE_CHAR) {
                    lprintf ("value = '%s'", (char *) fptr->value);
                    lprintf ("(%ld) field = '%s' value = '%s'", (long)strlen(fptr->value)+1L, fptr->fname, fptr->value);
               } else if (fptr->type==FTYPE_INT) {
                    lprintf ("value = %ld", *(long *)fptr->value);
               } else if (fptr->type==FTYPE_TIME) {
                   char timebuf[32];
                   strftime(timebuf,32,"%T",(struct tm*)TIME_ACCESS_TM( fptr));
                   lprintf ("value = %s", timebuf);

               } else if ( fptr->type == FTYPE_DATE) {
                   char timebuf[32];
                   strftime(timebuf,32,"%x",(struct tm*)TIME_ACCESS_TM( fptr));
                   lprintf ("value = %s", timebuf);

               } else if ( fptr->type == FTYPE_TIMESTAMP) {
                   char timebuf[32];
                   strftime(timebuf,32,"%C",(struct tm*) TIME_ACCESS_TM(fptr));
                   lprintf ("value = %s", timebuf);

               }else if ( fptr->type == FTYPE_BLOB) {
               } else
                   lprintf ("unknow type %ld", fptr->type);


               /* only allow INDEX_TOKEN_LEN chars per field in the index */
               if (fptr->type ==  FTYPE_CHAR) { 
               q = fptr->value;
               fptr->value = NULL;
               if (*q == '\'') {  /* skip quote if there */
                  q++;
                  /* copy until a quote */
                  r = (char *) memccpy (p, q, (int) '\'', (size_t) INDEX_TOKEN_LEN);
               }
               else {
                  /* copy until a NULL */
                  r = (char *) memccpy (p, q, 0, (size_t) INDEX_TOKEN_LEN);  
               }


              /* if memccpy reached the 'stop' character during the operation
                  then replace that character in the destination string with a
                  space.
               */
               if (r != NULL && r != indexstr)
                  *(r-1) = ' ';
               } /* end of special string de-quoting */
               p+=INDEX_TOKEN_LEN;  /* goto the next postion for the next index attribute */
            }
            *p = '\0';
            sprintf (indexstr, "%s;%ld", indexstr, recid);
            lprintf ("Index String: '%s'", indexstr);
            bt_driver ('a', indexstr); /* add to index */
            bt_driver ('q', "");    /* close index */
         }
      }

      /* free nodes that where already read in */
      free_table (tptr);
   }

   return !err;
}



int SQLselect (struct clist *tokens, struct bresult *sr)
{
   struct btable *tptr=NULL, *tp=NULL, *mtp=NULL;
   struct bfield *fptr=NULL;
   struct bindex *iptr=NULL;
   struct clist *t, *u;
   int err=NO, all, found, i;
   char temp[512], *p;

   lprintf ("Starting to Parse SELECT");

   t = tokens;

   /* skip forward to the list of tables */
   while (t!=NULL && strcasecmp (t->token, "FROM"))
      t=t->next;

   if (t==NULL) 
      err = syntax_error (INCOMPLETE);
   else {
      /* 
         Step through the list of tables doing the following:  
         1) Make sure the table exists.
         2) Create a btable structure for it.
         3) Add it to a list of tables.
      */
      while (!err && t!=NULL && strcasecmp (t->token, "WHERE")) {
         if ((t=t->next) == NULL)  /* move past the delimiter or FROM */
            err = syntax_error (INCOMPLETE);
         else {
            /* 
               I'm not checking for MAXIDSIZE or if it's a valid
               identifier.  If the table exists, I'm assuming all these 
               checks were made when it was created
            */
            tp = gettableinfo (t->token);

            if (tp == NULL) {
               err = syntax_error (GETTABLE);
               return !err;
            }
            else {

               if (tptr == NULL)  /* save the head of the fields list */
                  tptr = tp;

               tptr->last = store_table_list (tp, tptr->last);  /* add node to the list of tables */
               t=t->next;  /* advance to next token */
  
               /* next token should be "WHERE", ",", or NULL */
               if (t!=NULL && strcasecmp (t->token, "WHERE") && strcasecmp (t->token, ","))
                  err = syntax_error (BAD_DELIMITER);
            }
         }
      }

      /* test for ambiguous field names in the select statement.  It's OK
         just to test the entire select statement because field names
         cannot be reserved words, delimiters, and must start with an
         alphabetic character.
      */
      for (u=tokens; u!=NULL; u=u->next) {
         found = NO;
         for (tp=tptr; tp!=NULL; tp=tp->next)
            for (fptr=tp->fields; fptr!=NULL; fptr=fptr->next) {
               if (!strcmp (u->token, fptr->fname)) {
                  if (found)
                     err = syntax_error (AMBIGUOUS_FIELD);
                  found=YES;
                  break;
               }
            }
      }

      /* fully qualify all field names in the select statment if not already
         done.
      */
      for (u=tokens; u!=NULL; u=u->next) {
         lprintf ("checking token %s",u->token);
         for (tp=tptr; tp!=NULL; tp=tp->next)
            for (fptr=tp->fields; fptr!=NULL; fptr=fptr->next) {
               if (!strcmp (u->token, fptr->fname)) {
                  /* Fully Qualify all field names */
                  sprintf (temp, "%s.%s", fptr->tname, fptr->fname);
                  strcpy (u->token, temp);
                  break;
               }
            }
      }

      sr->f_last = NULL;
      all=NO;
      for (u=tokens; !err && strcasecmp (u->token, "FROM"); u=u->next) {
         
         for (tp=tptr; !err && tp!=NULL; tp=tp->next) {

            /* test for wild cards */
            sprintf (temp, "%s.*", tp->name);
            if (!strcmp (u->token, "*") || !strcmp (u->token, temp)) 
               all=YES;

            for (tp->f=tp->fields; !err && tp->f != NULL; tp->f=tp->f->next) {
               sprintf (temp, "%s.%s", tp->name, tp->f->fname);
               lprintf ("matching %s and %s",temp,u->token);
               if ((all && !is_sysfld(tp->f->fname)) || !strcmp(u->token,temp) || !strcmp(u->token,"oid")) {
                  fptr = field_node (tp->f->fname, tp->name, NULL, tp->f->type, tp->f->recid);
                  lprintf ("FLD #%ld '%s' all=%d", all ? sr->nfields : 0, u->token, all);
                  if (fptr != NULL) {
                     /* save the head of the fields list */
                     if (sr->fields == NULL)  
                        sr->fields = fptr;

                     /* add node to the list of tables */
                     sr->f_last = store_field_list (fptr, sr->f_last);  
                     sr->nfields++;

                  } /* if */
                  else 
                     err = syntax_error (MEMORY);
               } /* if */
            } /* for */
            all=NO;
         } /* for */
      } /* for */

      lprintf ("Search Result Structure has been built");
      lprintf ("   %ld Fields", sr->nfields);
      for (fptr=sr->fields; fptr!=NULL; fptr=fptr->next)
         lprintf ("   Field Name From Select: '%s.%s'", fptr->tname, fptr->fname);

      /* advance to the WHERE clause */
      while (t!=NULL && strcasecmp (t->token, "WHERE"))
         t=t->next;

      /* advance past the WHERE keyword */
      if (t!=NULL) t=t->next;

      /* advance to the USING-INDEX clause */
      u=t;
      while (u!= NULL && strcasecmp (u->token, "USING-INDEX"))
         u=u->next;
      
      if (u != NULL) {
         /* advance past the USING-INDEX keyword */
         if (u!=NULL) u=u->next;

         /* match the index up with the appropriate table */
         found = NO;
         for (tp=tptr; tp!=NULL && !found; tp=tp->next) {
            for (iptr=tp->indexes; iptr!=NULL; iptr=iptr->next) {
               if (!strcmp (u->token, iptr->iname)) {
                  lprintf ("Matched index %s to table %s", u->token, tp->name);
                  strcpy (tp->iname, u->token);
                  tp->search_type = BTREE;
                  found=YES;
                  break;
               }
            }
         }
      }

      /* execute the searches for each tables */
      err = SQLsearch (t, tptr, NONE, sr);

      /* Join all tables into a single table */

      if (!tptr->next) {
         lprintf ("No need to Join tables:%ld tuples",sr->ntuples);
         {
           struct bfield *x=tptr->fields;
           for (;x!=tptr->f_last;x=x->next)
             lprintf ("SQLsearch returned this token:%s",x->fname);
         }
         err = sr_values (tptr, sr);  /* store sr (search result) values into search_result structure */
      }
      else {  /* Lets start the join operation! */
         lprintf ("Begin the Join");
         for (i=0,tp=tptr->next; tp!=NULL; tp=tp->next,i++) {
            if (mtp==NULL) mtp=tptr;
            mtp = mergetables (mtp, tp, i);
            if (mtp==NULL) {
               lprintf ("   didn't work");
               break;
            }
         }

         if (mtp) {
            build_joined_table (mtp);
            free_field (mtp->values);
            mtp->values=NULL; 
            /* execute the search for the joined table */
            err = SQLsearch (t, mtp, NONE, sr);
            err = sr_values (mtp, sr);  /* store search result values into search_result structure */
            delete_table_files (mtp);
            free_table (mtp);     /* free merged table information */
            mtp=NULL;
         }
      }

   }

   /*   free_table (tptr);*/
   return !err;
}



int SQLdelete (struct clist *tokens, struct bresult *sr)
{
   struct btable *tptr=NULL;
   struct bindex *iptr=NULL;
   struct clist *t, *u;
   int err=NO, found;

   lprintf ("Starting to Parse DELETE");

   t = tokens;

   if (t==NULL) 
      err = syntax_error (INCOMPLETE);
   else {
      /* 
         1) Make sure the table exists.
         2) Create a btable structure for it.
         3) Add it to a list of tables.
      */
      /* 
         I'm not checking for MAXIDSIZE or if it's a valid
         identifier.  If the table exists, I'm assuming all these 
         checks were made when it was created
      */
      tptr = gettableinfo (t->token);

      if (tptr == NULL) {
         err = syntax_error (GETTABLE);
         return !err;
      } 

      t=t->next;  /* advance to next token */
  
      /* next token should be "WHERE", ",", or NULL */
      if (t!=NULL && strcasecmp (t->token, "WHERE")) 
         err = syntax_error (BAD_DELIMITER);


      /* fully qualify all field names in the select statment if not already
         done.
      */
/*   NOT NEEDED FOR DELETE 
      for (u=tokens; u!=NULL; u=u->next) {
         for (fptr=tptr->fields; fptr!=NULL; fptr=fptr->next) {
            if (!strcmp (u->token, fptr->fname)) {
               sprintf (temp, "%s.%s", fptr->tname, fptr->fname);
               strcpy (u->token, temp);
               break;
            }
         }
      }
*/

      /* advance to the WHERE clause */
      while (t!=NULL && strcasecmp (t->token, "WHERE"))
         t=t->next;

      /* advance past the WHERE keyword */
      if (t!=NULL) t=t->next;

      /* advance to the USING-INDEX clause */
      u=t;
      while (u != NULL && strcasecmp (u->token, "USING-INDEX"))
         u=u->next;
      
      if (u != NULL) {
         /* advance past the USING-INDEX keyword */
         if (u!=NULL) u=u->next;

         /* match the index up with the appropriate table */
         found = NO;
         for (iptr=tptr->indexes; iptr!=NULL; iptr=iptr->next) {
            if (!strcmp (u->token, iptr->iname)) {
               lprintf ("Matched index %s to table %s", u->token, tptr->name);
               strcpy (tptr->iname, u->token);
               tptr->search_type = BTREE;
               found=YES;
               break;
            }
         }
      }

      /* execute the searches for each tables */
      err = SQLsearch (t, tptr, DELETE_RECORD, sr);

   }

   free_table (tptr);
   return !err;
}




int SQLupdate (struct clist *tokens, struct bresult *sr)
{
   struct btable *tptr=NULL;
   struct bfield *fptr=NULL;
   struct clist *select_tokens=NULL, *t, *u;
   int err=NO;
   long i, j;
   char temp[512];
   char *select_stmt=NULL;

   lprintf ("Starting to Parse UPDATE");

   t = tokens;

   if (t==NULL) 
      err = syntax_error (INCOMPLETE);
   else {
      /* 
         1) Make sure the table exists.
         2) Create a btable structure for it.
         3) Add it to a list of tables.
      */
      /* 
         I'm not checking for MAXIDSIZE or if it's a valid
         identifier.  If the table exists, I'm assuming all these 
         checks were made when it was created
      */
      tptr = gettableinfo (t->token);

      if (tptr == NULL) {
         err = syntax_error (GETTABLE);
         return !err;
      }
      else {

         t=t->next;  /* advance to next token */
         if (t==NULL || (t!=NULL && strcasecmp (t->token, "SET")))
            err = syntax_error (GENERAL);
         t=t->next;
         if (t==NULL)
            err = syntax_error (GENERAL);
      }

      if (!err) {

         /* I'll build a select statement from the update statement so that
            I can retrieve the data & OIDs needed to evaluate expressions
            etc.
         */
         select_stmt = (char *) mymalloc (select_stmt, querystr_size);
         sprintf (select_stmt, "%s.oid", tptr->name);

         /* store the list of field names */
         for (u=t; u!=NULL; u=u->next) {
            /* exit the loop if we reach a FROM or a WHERE */
            if (!strcasecmp (u->token,"FROM") || !strcasecmp (u->token,"WHERE"))
               break;
            /* make sure it's a field name */ 
            if (isalpha(u->token[0]) && !isres(u->token))
               sprintf (select_stmt, "%s, %s", select_stmt, u->token);
         }

         /* add the table names to the select statement */
         sprintf (select_stmt, "%s FROM %s", select_stmt, tptr->name);

         /* advance to the FROM clause */ 
         for (u=t; u!=NULL && strcasecmp (u->token, "FROM"); u=u->next);

         /* add table names until hitting the WHERE clause */
         for (;u!=NULL && strcasecmp (u->token, "WHERE"); u=u->next) {
             if (isalpha (u->token[0]) && !isres (u->token) && 
                 strcasecmp (u->token, tptr->name))
                sprintf (select_stmt, "%s, %s", select_stmt, u->token);
         } 
         /* tack on the where clause */
         for (;u!=NULL; u=u->next)
            sprintf (select_stmt, "%s %s", select_stmt, u->token);

         lprintf ("CREATED SELECT: %s", select_stmt);
         select_tokens = parse_tokens (select_stmt);

         /* perform a search using the created select statement */
         err = !SQLselect (select_tokens, sr);
         if (err) 
            lprintf ("An Error occured processing the SELECT or the UPDATE");

         lprintf ("UPDATE: Done selecting\n");

         /* fully qualify all field names in the select statment if not already
            done.  Note this will qualify field names only for the table being
            updated.
         */
         for (u=tokens; !err && u!=NULL; u=u->next) 
            for (fptr=tptr->fields; fptr!=NULL; fptr=fptr->next) {
               if (!strcmp (u->token, fptr->fname)) {
                  /* Fully Qualify all field names */
                  sprintf (temp, "%s.%s", fptr->tname, fptr->fname);
                  strcpy (u->token, temp);
                  break;
               }
            } 

         sr->v = sr->values;
         for (j=0L; j<sr->ntuples; j++) {
            for (i=0L; i<sr->nfields && sr->v!=NULL; i++, sr->v=sr->v->next) {
               if (sr->v->type == FTYPE_CHAR)
                  lprintf ("CHAR DATA: %s", (char *) sr->v->value);
               else if (sr->v->type == FTYPE_OID)
                  lprintf ("OID DATA: %ld", *((long *) sr->v->value));
               else if (sr->v->type == FTYPE_INT)
                  lprintf ("INTEGER DATA: %ld", *((long *) sr->v->value));
               else if (sr->v->type == FTYPE_TIME)
                  lprintf ("TIME DATA: %s", ((char *) sr->v->value));

               else if (sr->v->type == FTYPE_DATE)
                  lprintf ("DATE DATA: %s", ((char *) sr->v->value));

               else if (sr->v->type == FTYPE_TIMESTAMP)
                  lprintf ("TIMESTAMP DATA: %s", ((char *) sr->v->value));
               else if (sr->v->type == FTYPE_BLOB)
                  lprintf ("TIMESTAMP DATA: %s", ((char *) sr->v->value));
            }
         }


      }
   }

   free_table (tptr);
   if (select_stmt!=NULL) myfree (select_stmt);

   /* free nodes in select_token list */
   free_tokens (select_tokens);

   return !err;
}



/* check to see if the fully qualified field name in the string 'fname' 
   matches the field structure pointed to by 'fptr'
*/
int strcmpfld (char *fname, struct bfield *fptr)
{
   char temp[MAXIDSIZE];

   sprintf (temp, "%s.%s", fptr->tname, fptr->fname);
   return strcmp (fname, temp);
}


/* check to see if the field in the field structure pointed to by 'fname' 
   matches the field in the field structure pointed to by 'fptr'
*/
int fldcmpfld (struct bfield *f1, struct bfield *f2)
{
  /* int  temp,temp2;

    temp=strcmp (f1->tname,f1->fname);
    temp2=strcmp(f2->tname,f2->fname);
    if (temp)
       return temp;
       else return (temp2);*/
   char temp1[MAXIDSIZE];
   char temp2[MAXIDSIZE];

   sprintf (temp1, "%s.%s", f1->tname, f1->fname);
   sprintf (temp2, "%s.%s", f2->tname, f2->fname);

   return strcmp (temp1, temp2);

}



int SQLsearch (struct clist *tokens, struct btable *tptr, int action, struct bresult *sr)
{
   int err=NO, next, c, len,read_match;
   struct clist *t;
   struct clist *w;
   struct btable *tp=NULL;
   struct bfield *fptr=NULL;
   struct bindex *iptr=NULL;
   struct offset_list *offsets=NULL;
   char indexstr[512], temp[256], *p, path[256];
   FILE *fp;
   int match;

   lprintf ("Starting to Execute the Search");

   t = tokens;
   sr->ntuples=0L;
   for (tp=tptr; tp!=NULL; tp=tp->next) {
      next=NO;

      if (tp->search_type == SEQ) {
         lprintf ("Processing SEQUENTIAL search on table '%s'", tp->name);
         fp = bg_fopen (getCurrentDB(), tp->name, ".seq", "rb"); /* open Index */
         if (fp==NULL) {
            lprintf ("ERROR: Can't open Index file");
            continue;
         }

         for (;;) {
            if (!next) {
               if (read_first (fp, tp, t, action,&match) == ERROR)
                  break;
               next = YES;
            } 
            else
               if (read_next (fp, tp, t, action,&match) == ERROR)
                  break;

            if (!match) 
               lprintf ("RECORD DOESN'T MATCH WHERE CLAUSE");
            else {
               lprintf ("RECORD MATCHES WHERE CLAUSE: %d more",sr->ntuples);
               sr->ntuples++;

               lprintf ("Read Successfull");

               for (tp->f = tp->fields; tp->f != NULL; tp->f=tp->f->next)
                  if (tp->f->type==FTYPE_OID||tp->f->type==FTYPE_INT)
                     lprintf ("field='%s' value=%ld", tp->f->fname, *((long *) tp->f->value));
                  else if (tp->f->type==FTYPE_TIME) {
                     char dateBuf[32];
                     struct tm *workP=(struct tm*) TIME_ACCESS_TM(tp->f);

                     strftime(dateBuf,32,"%H:%M:%S",workP);
                     lprintf ("field='%s' value=%s", tp->f->fname, dateBuf);
                  } else if (tp->f->type==FTYPE_DATE) {
                     char dateBuf[32];
                     struct tm *workP=(struct tm*) TIME_ACCESS_TM(tp->f);

                     strftime(dateBuf,32,"%x",workP);
                     lprintf ("field='%s' value=%s", tp->f->fname, dateBuf);
                  } else if (tp->f->type==FTYPE_TIMESTAMP) {
                     char dateBuf[32];
                     struct tm *workP=(struct tm*) TIME_ACCESS_TM(tp->f);
                     memcpy(workP,localtime((time_t*)TIME_ACCESS_TIME_T(tp->f)),sizeof(struct tm));
                     strftime(dateBuf,32,"%C",workP);
                     lprintf ("field='%s' value=%s (%u)", tp->f->fname, dateBuf,*(time_t*)TIME_ACCESS_TIME_T(tp->f));
               
                  } else if (tp->f->type==FTYPE_CHAR)
                     lprintf ("field='%s' value='%s'", tp->f->fname, (char *) tp->f->value);
                   else if (tp->f->type==FTYPE_BLOB) {
                  }
            }
         }
         bg_fclose (fp); /* close Index file used for this search */
      }
      else {
         lprintf ("Processing BTREE search on table '%s'", tp->name);

         /* point to the index structure to be used in this search */
         for (iptr=tp->indexes; iptr!=NULL; iptr=iptr->next)
             if (!strcmp (iptr->iname, tp->iname))
                break;

         if (iptr!=NULL)
            lprintf ("Pointing to index %s", iptr->iname);
         else {
            lprintf ("ERROR - Can't point to index %s!", iptr->iname);
            continue;
         }

         memset (indexstr, '\0', 256); /* initialize to NULL's */

         lprintf ("Building Key");

         /* build the key from the data provided in the WHERE clause */
         for (c=0, fptr=iptr->fields; fptr!=NULL; c++, fptr=fptr->next) {
            for (w=tokens; w!=NULL; w=w->next) {

               /* strip THIS table name prefix from field name if there */
               p = w->token;
               sprintf (temp, "%s.", fptr->tname);
               if (!strncmp (w->token, temp, strlen (temp)))
                  p += strlen (temp);

               if (!strcmp (p, fptr->fname)) {
                  /* OK, this index field was found in the where clause */

                  /* advance the token pointer */
                  if (w->next==NULL) break;
                  w=w->next;

                  /* The next token should be one of the equality operators */
                  if (!strcasecmp (w->token, "eq") ||
                      !strcasecmp (w->token, "=")  ||
                      !strcasecmp (w->token, "begins")) {

                     /* advance the token pointer */
                     if (w->next==NULL) break;
                     w=w->next;
              
                     if (!strcasecmp(w->token, "TIME") ||
                         !strcasecmp(w->token, "DATE") ||
                         !strcasecmp(w->token, "TIMESTAMP")) 
                          w=w->next;

                     /* Check to see if it is compared to a constant string */
                     if (*(w->token) == '\'' || isdigit (*(w->token))) {
                        /* now, insert it into it's appropriate place in the */
                        /* key string 'indexstr'.                            */
                        len = strlen (w->token)-2;
                        if (len > INDEX_TOKEN_LEN) len = INDEX_TOKEN_LEN;
                        memcpy (indexstr+(INDEX_TOKEN_LEN*c), w->token+1, len);
                     }
                  }
               }

            }
         }

         lprintf ("Index String: '%s'", indexstr);

         sprintf (path, "%s/%s/%s", DBROOT, getCurrentDB(), tp->iname); 
         lprintf ("opening index %s", path);
         bt_driver ('o', path);  /* open index */
         bt_driver ('f', indexstr);   /* find offsets */

         /* read data from resulting offsets */
         for (offsets=index_res; offsets!=NULL; offsets=offsets->next) {
            read_record (tp, offsets->offset, t, action,&read_match);

            if (!read_match) 
               lprintf ("RECORD DOESN'T MATCH WHERE CLAUSE");
            else {
               lprintf ("RECORD MATCHES WHERE CLAUSE");
               sr->ntuples++;

               lprintf ("Read Successfull");

               for (tp->f = tp->fields; tp->f != NULL; tp->f=tp->f->next)
                  if (tp->f->type==FTYPE_OID||tp->f->type==FTYPE_INT)
                     lprintf ("field='%s' value=%ld", tp->f->fname, *((long *) tp->f->value));
                  else if (tp->f->type==FTYPE_TIME) {
                      char timeBuf [32];
                      struct tm *workP=(struct tm*) TIME_ACCESS_TM(tp->f);

                      strftime(timeBuf,32,"%H:%M:%S",workP);
                     lprintf ("field='%s' value=%s", tp->f->fname, timeBuf);
                  }else if (tp->f->type==FTYPE_DATE) {
                      char timeBuf [32];
                      struct tm *workP=(struct tm*) TIME_ACCESS_TM(tp->f);

                      strftime(timeBuf,32,"%x",workP);
                     lprintf ("field='%s' value=%s", tp->f->fname, timeBuf);
                  }else if (tp->f->type==FTYPE_TIMESTAMP) {
                      char timeBuf [32];
                      struct tm *workP=(struct tm*) TIME_ACCESS_TM(tp->f);

                      strftime(timeBuf,32,"%C",workP);
                     lprintf ("field='%s' value=%s (%u)", tp->f->fname, timeBuf,TIME_ACCESS_TIME_T(tp->f));
                  } else if (tp->f->type==FTYPE_CHAR)
                     lprintf ("field='%s' value='%s'", tp->f->fname, (char *) tp->f->value);
                  else if (tp->f->type==FTYPE_BLOB) {
                  }
            }
         }

         /* free offset list */
         free_offsets(); 

         /* quit btree routines closing indexes */
         bt_driver ('q', "");
      }
   }
   lprintf ("read %d tuples",sr->ntuples);
   return err;
}


struct btable *mergetables (struct btable *t1, struct btable *t2, int free_t1)
{
   struct btable *tnew=NULL;
   struct bfield *fnew, *f, *p, *v;
   long i;

   lprintf ("Trying to merge two tables");

   if ((tnew=table_node ("")) == NULL)
      return NULL;  /* check for failed malloc */
  
   sprintf (tnew->name, "tmp%ld", (long) getpid()); 
   strcpy (tnew->iname, tnew->name); 
   tnew->nfields = t1->nfields + t2->nfields;

   lprintf ("   Table Name: '%s', # fields %ld", tnew->name, tnew->nfields);

   /* merge field list */
   tnew->fields = copy_field_list (t1->fields);
   if (tnew->fields==NULL) {
      free_table (tnew);
      return NULL;
   }

   f = copy_field_list (t2->fields);
   if (f==NULL) {
      free_table (tnew);
      return NULL;
   }

   for (p=tnew->fields; p!=NULL; p=p->next)
      if (p->next == NULL) {
         p->next = f;
         break;
      }

   /* merge values */
   lprintf ("Trying to merge values");
   p = t1->values;

   while (p!=NULL) {
      f = t2->values;
      while (f!=NULL) {
         lprintf ("New Record");
         lprintf ("   First Table %ld fields", t1->nfields);
         for (i=0, v=p; i<t1->nfields; i++, v=v->next) {
            fnew = field_node(v->fname, v->tname, v->value, v->type, v->recid);
            if (fnew==NULL) {
               lprintf ("   MERGE ERROR: MEMORY ALLOCATION");
               free_field (tnew->values);
               return NULL;
            }
            if (tnew->values == NULL)
               tnew->values = fnew;
            tnew->f_last = store_field_list (fnew, tnew->f_last);
         }
         lprintf ("   Second Table %ld fields", t2->nfields);
         for (i=0, v=f; i<t2->nfields; i++, v=v->next) {
            fnew = field_node(v->fname, v->tname, v->value, v->type, v->recid);
            if (fnew==NULL) {
               lprintf ("   MERGE ERROR: MEMORY ALLOCATION");
               free_table (tnew);
               return NULL;
            }
            tnew->f_last = store_field_list (fnew, tnew->f_last);
         }

         for (i=0; i<t2->nfields && f!=NULL; i++, f=f->next);
         if (i < t2->nfields) {
            lprintf ("   MERGE ERROR: Insufficent Number of fields in inner table (%ld,%ld)",i,t2->nfields);
            free_table (tnew);
            return NULL;
         }
         if (f==NULL) lprintf ("  No More Data In Inner Table");
      }

      for (i=0; i<t1->nfields && p!=NULL; i++, p=p->next);
      if (i < t1->nfields) {
         lprintf ("   MERGE ERROR: Insufficent Number of fields in outer table (%ld,%ld)", i, t1->nfields);
         free_table (tnew);
         return NULL;
      }
      if (p==NULL) lprintf ("  No More Data In Outer Table");
   }

   for (v=tnew->values; v!=NULL; v=v->next)
      if (v->type==FTYPE_OID || v->type==FTYPE_INT)
         lprintf ("   %s.%s = %ld", v->tname, v->fname, *((long *) v->value));
      else if (v->type==FTYPE_CHAR)
         lprintf ("   %s.%s = %s", v->tname, v->fname, (char *) v->value);

   if (free_t1) free_table (t1);
   return tnew;
}


int build_joined_table (struct btable *tptr)
{
   struct bfield *v, *vv;
   long i;

   lprintf ("Building Joined Table");

   if (!puttableinfo (tptr))
      lprintf ("can't create table");

   /* write data to the table */
   v = tptr->values;
   while (v!=NULL) {
      vv = v;

      /* advance to the next record */
      for (i=0L; i<tptr->nfields && v!=NULL; i++, v=v->next);

      write_record (getCurrentDB(), tptr->name, vv, v, NEW,0L);

      /* check to be sure that there isn't an early termination of fields */  
      if (i < tptr->nfields) {
         lprintf ("   BUILD ERROR: Insufficent Number of fields");
         return 0;
      }
   }
   return 1;
}


/* send the first field's info a previous select to the client */
void first_field (struct bresult *sr)
{
   char temp [LENSIZE+1];

   lprintf ("Sending First Field");

   sr->f = sr->fields;  /* reset the pointer */
   lprintf ("SENDING: %s    LENGTH=%ld", sr->f->fname, strlen (sr->f->fname));

   /* send the length of the field name to the client */
   sprintf (temp, "%10d", strlen(sr->f->fname));
   write (ssock, temp, (size_t) LENSIZE);

   /* send the field name to the client */
   write (ssock, sr->f->fname, (size_t) atol (temp));

   /* send the field type to the client */
   sprintf (temp, "%10d", sr->f->type);
   write (ssock, temp, (size_t) LENSIZE); 

   sr->f=sr->f->next; /* advance ptr to the next field */
}


void next_field (struct bresult *sr)
{
   char temp [LENSIZE+1];

   lprintf ("Sending Next Field");

   lprintf ("SENDING: %s    LENGTH=%ld", sr->f->fname, strlen (sr->f->fname));

   /* send the length of the field name to the client */
   sprintf (temp, "%10d", strlen(sr->f->fname));
   write (ssock, temp, (size_t) LENSIZE);

   /* send the field name to the client */
   write (ssock, sr->f->fname, (size_t) atol (temp));

   /* send the field type to the client */
   sprintf (temp, "%10d", sr->f->type);
   write (ssock, temp, (size_t) LENSIZE); 

   sr->f=sr->f->next; /* advance ptr to the next field */
}


/* send the first tuple from a previous select to the client */
void first_tuple (struct bresult *sr)
{
   long i;
   char length [LENSIZE+1], val[21];

   lprintf ("Sending First Tuple");

   for (i=0L, sr->v = sr->values; i<sr->nfields && sr->v!=NULL; i++, sr->v=sr->v->next) {
      if (sr->v->type == FTYPE_CHAR) {
         sprintf (length, "%10d", strlen(sr->v->value));
         lprintf ("SENDING: %s    LENGTH=%s", (char *) sr->v->value, length);
         write (ssock, length, (size_t) LENSIZE); 
         write (ssock, sr->v->value, (size_t) atol (length));
      }
      else if (sr->v->type == FTYPE_OID ||
           sr->v->type == FTYPE_INT) {
         sprintf (val, "%10ld", *((long *) sr->v->value));
         sprintf (length, "%10d", strlen(val));
         lprintf ("SENDING: %ld    LENGTH=%s", *((long *) sr->v->value), length);
         write (ssock, length, (size_t) LENSIZE); 
         write (ssock, val, (size_t) atol (length));
      } else if (sr->v->type == FTYPE_TIME) {
         char timeBuf [32];
         struct tm *workP=sr->v->value+sizeof(time_t);
         strftime(timeBuf,32,"%H:%M:%S",(struct tm*) sr->v->value+sizeof(time_t));
         sprintf (length, "%10d", 8);
         sprintf (val,"%2.2d:%2.2d:%2.2d",workP->tm_hour,workP->tm_min,workP->tm_sec);
         lprintf ("SENDING: %s    LENGTH=%s", val, length);
         write (ssock, length, (size_t) LENSIZE); 
         write (ssock, val, (size_t) atol (length));
      } else if (sr->v->type == FTYPE_DATE) {
         char timeBuf [32];
         struct tm *workP=TIME_ACCESS_TM(sr->v);

         strftime(timeBuf,32,"%x",workP );
         sprintf (length, "%10d", strlen(timeBuf));
         lprintf ("SENDING: %s    LENGTH=%s", timeBuf, length);
         write (ssock, length, (size_t) LENSIZE); 
         write (ssock, timeBuf, (size_t) atol (length));
      } else if (sr->v->type == FTYPE_TIMESTAMP) {
         char timeBuf [32];
         struct tm *workP=(struct tm*)TIME_ACCESS_TM(sr->v);

	 strftime(timeBuf,32,"%C",localtime((time_t*)TIME_ACCESS_TIME_T(sr->v)));
         sprintf (length, "%10d", strlen(timeBuf));
         lprintf ("SENDING: %s    LENGTH=%s", timeBuf, length);
         write (ssock, length, (size_t) LENSIZE); 
         write (ssock, timeBuf, (size_t) atol (length));
      } else if (sr->v->type == FTYPE_BLOB) {
      }
      else {
         lprintf ("SENDING: failed invalid field type %d",sr->v->type);
      }
   
   }

}


/* send the next tuple from a previous select to the client */
void next_tuple(struct bresult *sr)
{
   long i;
   char length [LENSIZE+1], val[21];

   lprintf ("Sending Next Tuple");

   for (i=0L; i<sr->nfields && sr->v!=NULL; i++, sr->v=sr->v->next) {

      if (sr->v->type == FTYPE_CHAR) {
         sprintf (length, "%10d", strlen(sr->v->value));
         lprintf ("SENDING: %s    LENGTH=%s", (char *) sr->v->value, length);
         write (ssock, length, (size_t) LENSIZE); 
         write (ssock, sr->v->value, (size_t) atol (length));
      }
      else if (sr->v->type == FTYPE_OID || sr->v->type == FTYPE_INT) {
         sprintf (val, "%ld", *((long *) sr->v->value));
         sprintf (length, "%10d", strlen(val));
         lprintf ("SENDING: %ld    LENGTH=%s", *((long *) sr->v->value), length);
         write (ssock, length, (size_t) LENSIZE); 
         write (ssock, val, (size_t) atol (length));
      } else if (sr->v->type == FTYPE_TIME) {
         char timeBuf [32];
         struct tm *workP=TIME_ACCESS_TM(sr->v)/*->value+sizeof(time_t)*/;
         strftime(timeBuf,32,"%H:%M:%S",(struct tm*) workP);
         sprintf (length, "%10d", strlen(timeBuf));
         sprintf (val, "%2.2d:%2.2d:%2.2d", workP->tm_hour,workP->tm_min,workP->tm_sec);
         lprintf ("SENDING: %s    LENGTH=%s", val, length);
         write (ssock, length, (size_t) LENSIZE); 
         write (ssock, val, (size_t) atol (length));
      } else if (sr->v->type == FTYPE_DATE) {
         char timeBuf [32];
         struct tm *workP=TIME_ACCESS_TM(sr->v)/*->value+sizeof(time_t)*/;
         strftime(timeBuf,32,"%x",workP/*(struct tm*) sr->v->value+sizeof(time_t)*/);
         sprintf (length, "%10d", strlen(timeBuf));

         lprintf ("SENDING: %s    LENGTH=%s", timeBuf, length);
         write (ssock, length, (size_t) LENSIZE); 
         write (ssock, timeBuf, (size_t) atol (length));
      } else if (sr->v->type == FTYPE_TIMESTAMP) {
         char timeBuf [32];

	 strftime(timeBuf,32,"%C",localtime((time_t*)TIME_ACCESS_TIME_T(sr->v)));

         sprintf (length, "%10d", strlen(timeBuf));

         lprintf ("SENDING: %s    LENGTH=%s", timeBuf, length);
         write (ssock, length, (size_t) LENSIZE); 
         write (ssock, timeBuf, (size_t) atol (length));
      } else if (sr->v->type == FTYPE_TIMESTAMP) {
      }
      else {
         lprintf ("SENDING: failed invalid field type %d",sr->v->type); 
      }
   }
}


/* check to make sure 's' is a valid itentifier */
int checkidentifier (char *s)
{
   int i;
   for (i=0; i<strlen(s); i++)
      if (!isalnum (s[i]) && s[i] != '_') return ERROR;
   return 1;
}

/* check to see if the table exists */
int table_exists (char *tname) {
   return 1;
}


int syntax_error (int err)
{
   lprintf ("ERROR: %s", berrors[err]);
   /* send error message to the client */
   write (ssock, berrors[err], strlen(berrors[err])); 
   return YES;
}


/* check to see if 's' is a reserved word. 'reserved_words' is defined in 
   commands.h 
*/
int isres (char *s)
{
   int i;
   for (i=0; reserved_words[i]!=NULL; i++)
      if (!strcasecmp (reserved_words[i], s))
         return 1;
   return 0;
}


int min(char *s1, char *s2)
{
   int i, j;
   i = strlen (s1);
   j = strlen (s2);
   return ( (i<j) ? i : j );
}

