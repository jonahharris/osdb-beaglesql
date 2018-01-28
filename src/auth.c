static const char  rcsfile []= "$Header: /home/magrasjc/test/src/RCS/auth.c,v 0.87.2.1 2000/02/05 06:12:52 magrasjc Exp $";
#include "config.h"
#include <errno.h>
#include <time.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <fcntl.h>
#include "beagle.h"
#include "sha.h"
/*
      
 auth.c
 
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
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "beagle.h"
#include "sockio.h"
#include "errexit.h"
#include "mymalloc.h"
#include "parse.h"
#include "beagleb.h"
#include "sr.h"

#define YES 1
#define NO 0

int auth (int ssock);
char BG_user[MAX_USER_NAME_LEN+1];
char syncBuffer[3048];
/* get and verify user authorzation 
*/
int auth (int ssock)
{
   int ok=YES, err=NO;
   long len;
   char buf[LENSIZE+1];
   char local_host[MAX_HOST_NAME_LEN+1];
   char remote_host[MAX_HOST_NAME_LEN+1];
   char remote_user[MAX_USER_NAME_LEN+1];
   char request[1000],*checkP;
   struct bresult sr;
   struct clist *tokens;
   extern int getdate_err;
   unsigned long  magicNumber=0x34b786e4,incomingSHA[5];
   unsigned int   packetLength,shaIndex;
   time_t         recvTime,sendTime;
   size_t         peerAddrLength=sizeof(struct sockaddr_in);
   int            digestIndex,df;
   
   char header[8],      lengthBuffer[10]="0x",username[16];
   char dateBuffer[35], addrCHECK[48],  userCHECK[48],shaBuff[65536];
   char password[16]="xxxxxxxxx", *memPtr;
   struct tm           *dateP;
   struct sockaddr   clientAddr;
   struct sha_info      ShaBlock,ShaUserBlk;

   GETPASSWD

   time       (&recvTime);
   lprintf ("AUTH: Authorization In Progress");
   /*
   version 2 plan:
    SHA will be the minimum for auth.
    no-privacy/no-auth
    no-privacy/auth
    privacy/auth
    
    no-privacy/auth
    obtain usersaltvalue
    increment usersaltvalue

    single byte of value 1 -- auth mech #1 (0 = no auth)
    single byte of value 0 -- priv mech #0 (0 = no priv)
    single byte of 1 representing version
    single byte  giving end-of-field seperator (typically newline)
    4 bytes length (hex digits)data not including the previous 3 header bytes.
    loginname
    text string date in UTC
    sha-1 of  usersaltvalue(16 bytes) and then address repeated
        until 65536 bytes are filled.padding is 0xea.
    sha-1 of  usersaltvalue(16 bytes) and then pattern of 
        alternating loginname and password until all elements 
        total 65536 bytes.padding is 0x5c.

    example:
    101
    0067              <- hex number counts all that follows, including nl 
    magras            <-  login name contributes 7 to length
    Thu Aug 27 04:20:50 GMT 1998          <- contributes 0x1d to length
    56B7493A90BB6D938B3F403B89A78CEF      <- contributes 0x21 to length


101
0067
magras
Thu Aug 27 04:20:50 GMT 1998
56B7493A90BB6D938B3F403B89A78CEF

    */

   lprintf("getpeername returns: %d",getpeername(ssock,&clientAddr,&peerAddrLength));
   for (shaIndex=0 ; shaIndex< 14;shaIndex++)
     {
        unsigned int digit=(unsigned char)clientAddr.sa_data[shaIndex];
      lprintf ("data:%x",digit);
     }
   
   err = sock_recv(ssock,header,5); 
   if (err<0)
      return NO;

   err = sock_recv(ssock,&lengthBuffer[2],6);
   if (err<0)
       return NO;
   else 
       sscanf(lengthBuffer,"%x",&packetLength);
   lprintf ("packetlength is %d",packetLength);
   err = sock_recv(ssock,username,packetLength-(42+27+2));    
   if (err>=0)
       username[packetLength-(42+27+2+1)]=0;
   else
       return NO;
   
  err = sock_recv(ssock,dateBuffer,27);
   if (err<0)
     return NO; 
   checkP=strchr(username,'\012');
   if (checkP)
      *checkP=0;

   if (checkP-username < packetLength-(42+27+2+1))
       
   checkP=strchr(dateBuffer,'\012');
   if (checkP)
      *checkP=0;
   lprintf ("timestamp:%s:username=<%s>",dateBuffer,username);
   checkP=dateBuffer;
   while (*checkP == ' ') checkP++;
   dateP = getdate(checkP);
   if (!dateP)
      lprintf ("getdate did not work:%d.",getdate_err);
   else 
      lprintf("getdate worked");
   sendTime =  mktime(dateP);
   memcpy (syncBuffer,&sendTime,sizeof(sendTime));
   lprintf ("we have the time in %d seconds",sendTime);
   err = sock_recv(ssock,userCHECK,42); 
   if (err <0)
      return NO;


   shaBuff[4]=shaBuff[5]=shaBuff[6]=shaBuff[7]=0x5c;
   shaBuff[12]=shaBuff[13]=shaBuff[14]=shaBuff[15]=0x5c;
   memcpy(shaBuff,&magicNumber,4);
   memcpy(&shaBuff[8],&sendTime,4);

   for (memPtr=shaBuff+65514;memPtr<shaBuff+65536;*(memPtr++)=0x5c);
  
   for (memPtr=shaBuff+16;
        memPtr < shaBuff+65536-strlen(username)-strlen(passwd)-6/*-sizeof((struct sockaddr_in)clientAddr.sin_port)-sizeof((struct sockaddr_in)clientAddr.sin_addr.s_addr)*/;
	) {
     memcpy(memPtr,username,strlen(username));
     memPtr += strlen(username);
     memcpy(memPtr,passwd,strlen(passwd));
     memPtr += strlen(passwd);
     memcpy(memPtr,&clientAddr.sa_data[2],4);
            
     memPtr += 4; /* sizeof((struct sockaddr_in)clientAddr.sin_addr.s_addr);*/
     memcpy(memPtr,&clientAddr.sa_data[0]/*sin_port,sizeof((struct sockaddr_in)clientAddr.sin_port)*/,2);
     memPtr +=2;
   }
   df=open("serverdebug",O_CREAT|O_RDWR);
   write(df,shaBuff,65536);
   close(df);
   for (shaIndex=0;shaIndex<40;shaIndex+=2) {
      unsigned int aByte=0,digit=userCHECK[shaIndex];
      if (islower(digit)) {
         digit-='a'-10;
      }
      else {
      digit -= '0';
      }
      aByte=digit;
      aByte <<=4;

      digit=userCHECK[shaIndex+1];
      if (islower(digit)) {
         digit -= 'a' -10;
      } else {
      digit -= '0';
      }
      aByte|=digit;
      lprintf ("final result:%2.2x",aByte);

      if (shaIndex%(2*sizeof(unsigned long))==0) {

       incomingSHA[shaIndex/(2*sizeof(unsigned long))] =aByte;
      } else {
       incomingSHA[shaIndex/(2*sizeof(unsigned long))] <<=8;
       incomingSHA[shaIndex/(2*sizeof(unsigned long))]|=aByte;

	}
   }
   sha1Initial(&ShaBlock);
   sha1Update(&ShaBlock,shaBuff,65536);
   sha1Final(&ShaBlock);
   for (digestIndex=0;digestIndex<5;digestIndex++)
   {
      lprintf("Digest %#X,received %#X",ShaBlock.digest[digestIndex],incomingSHA[digestIndex]);
      ok |= (ShaBlock.digest[digestIndex] == incomingSHA[digestIndex]); 
   }
   if (!ok)
   {
      write (ssock,"REJECT",6);
   } else
   {
      write (ssock,"ACCEPT",6);
      strcpy (BG_user, username);
   }
   return ok;

   /* Read the length of the data to follow */
   err = sock_recv(ssock, buf, LENSIZE);
   if (err < 0) 
      ok=NO;
   else {

      len = atol (buf);
      if (len > MAX_USER_NAME_LEN) 
         ok=NO;
      else {

         /* read the user name */
         err = sock_recv(ssock, remote_user, (size_t) len);
         if (err < 0) 
            ok=NO;
         else {

            /* Read the length of the data to follow */
            err = sock_recv(ssock, buf, LENSIZE);
            if (err < 0) 
               ok=NO;
            else {

               len = atol (buf);
               if (len > MAX_USER_NAME_LEN) 
                  ok=NO;
               else {

                  /* read the host name */
                  err = sock_recv(ssock, remote_host, (size_t) len);
                  if (err < 0) 
                     ok=NO;
                  else {

                     lprintf ("AUTH: remote_user: %s remote_host: %s", remote_user, remote_host);


                     if (gethostname (local_host, MAX_HOST_NAME_LEN))
                        local_host[0]='\0';

                     /* if it's not the beagle user on the local host, then
                        check the sys_user table 
                     */
                     if (strcmp (local_host, remote_host) && 
                         (strcmp ("beagle", remote_user) && strcmp("magras",remote_user))) {

                         /* needed for first time initialization */
                         sr.fields=NULL;
                         sr.values=NULL;

                         /* Initialize search_result structure */
                         sr_initresult(&sr);

                        /* checking sys_user system table */
                        sprintf (request, "select * from sys_user where sys_user_name = '%s' and sys_user_host = '%s'", remote_user, remote_host);
                        int_SQLselect (request, &sr);
                        if (sr.ntuples)
                           lprintf ("AUTH: found user\n");
                        else {
                           lprintf ("AUTH: user does not exist\n");
                           ok=NO;
                        }
                        sr_initresult (&sr);
                     }
                     else
                        lprintf ("AUTH: It's the beagle user this host!");
                  }
               }
            }
         }
      }
   }

   /* if authorization was successfull, send OK to client */
   if (ok)  {
      lprintf ("AUTH: Trying to send OK to client");
      if (write (ssock, "OK", 2) != 2) {
         fprintf (stderr, "\nERROR %s\n", STRERROR);
         lprintf ("AUTH: Can't send OK to client");
      }
      else
         lprintf ("AUTH: Sent OK to client");
     strcpy (BG_user, remote_user);
     lprintf ("BGUSER: %s", BG_user);
   }
   return ok;
}
