static const char  rcsfile []= "$Header: /home/magrasjc/test/src/RCS/connectTCP.c,v 0.87.2.1 2000/02/05 06:13:11 magrasjc Exp $";
#include "config.h"
/*
      
 connectTCP.c 

 Original Source by Douglas E. Comer & David L. Stevens

 Modifications & usage with the Beagle SQL product
 is Copyright (c) 1996 Robert Klein

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
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "beagle.h"

#ifndef	INADDR_NONE
#define	INADDR_NONE	0xffffffff
#endif	/* INADDR_NONE */

extern int	errno;
/* Changes in the new GNU headers forced this */
/* #if (__FreeBSD__|PORT_LINUX) */
/* #include <stdio.h> */
/* #else */
/*extern char	*sys_errlist[];*/
/* #endif */

/*#if (PORT_LINUX|PORT_BSD|PORT_IRIX|PORT_HPUX|PORT_DECUNIX32)*/
#if (VALID_ARPA_INET_H)
#else
u_short	htons();
u_long	inet_addr();
#endif

int connectTCP(char *host, char *service);

int connectTCP (char *host, char *service)
{
   struct hostent  *phe;   /* pointer to host information entry*/
   struct servent  *pse;   /* pointer to service information entry*/
   struct protoent *ppe;   /* pointer to protocol information entry*/
   struct sockaddr_in sin; /* an Internet endpoint address*/
   int s; /* socket descriptor*/

   memset ((char *)&sin, 0, sizeof (sin));
   sin.sin_family = AF_INET;

   /* Map service name to port number */
   if ( (pse = getservbyname(service, "tcp")) )
      sin.sin_port = pse->s_port;
   else if ( (sin.sin_port = htons((u_short)atoi(service))) == 0 ) {
      fprintf(stderr, "can't get \"%s\" service entry\n", service);
      return -1;
   }

   /* Map host name to IP address, allowing for dotted decimal */
   if ( (phe = gethostbyname(host)) )
      memcpy((char *)&sin.sin_addr, phe->h_addr, phe->h_length);
   else if ( (sin.sin_addr.s_addr = inet_addr(host)) == INADDR_NONE ) {
      fprintf (stderr, "can't get \"%s\" host entry\n", host);
      return -1;
   }

   /* Map protocol name to protocol number */
   if ( (ppe = getprotobyname("tcp")) == 0) {
      fprintf (stderr, "can't get \"tcp\" protocol entry\n");
      return -1;
   }

   /* Allocate a socket */
   s = socket(PF_INET, SOCK_STREAM, ppe->p_proto);
   if (s < 0) {
      fprintf (stderr, "can't create socket: %s\n", STRERROR);
      return -1;
   }

   /* Connect the socket */
   if (connect(s, (struct sockaddr *)&sin, sizeof(sin)) < 0) {
      fprintf (stderr, "can't connect to %s.%s: %s\n", host, service, STRERROR);
      return -1;
   }

   return s;
}
