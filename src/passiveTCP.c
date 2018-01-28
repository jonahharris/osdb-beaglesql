static const char  rcsfile []= "$Header: /home/magrasjc/test/src/RCS/passiveTCP.c,v 0.87.2.1 2000/02/05 06:13:38 magrasjc Exp $";
#include "config.h"
/*
      
 passiveTCP.c 

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
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include "beagle.h"

/*#if (PORT_LINUX|PORT_BSD|PORT_IRIX|PORT_HPUX)*/
#if (VALID_ARPA_INET_H)
#else
u_short	htons(u_short), ntohs(u_short);
#endif

u_short	portbase = 0;		/* port base, for non-root servers	*/

/*------------------------------------------------------------------------
 * passivesock - allocate & bind a server socket using TCP or UDP
 *------------------------------------------------------------------------
 */
int passiveTCP (char *service, int qlen)
{
   struct servent  *pse;   /* pointer to service information entry*/
   struct protoent *ppe;   /* pointer to protocol information entry*/
   struct sockaddr_in sin; /* an Internet endpoint address*/
   int s;                 /* socket descripto */

   bzero((char *)&sin, sizeof(sin));
   sin.sin_family = AF_INET;
   sin.sin_addr.s_addr = INADDR_ANY;

   /* Map service name to port number */
   if ( (pse = getservbyname(service, "tcp")) )
      sin.sin_port = htons(ntohs((u_short)pse->s_port) + portbase);
   else if ( (sin.sin_port = htons((u_short)atoi(service))) == 0 ) {
      fprintf (stderr, "can't get \"%s\" service entry\n", service);
      exit (0);
   }

   /* Map protocol name to protocol number */
   if ( (ppe = getprotobyname("tcp")) == 0) {
      fprintf (stderr, "can't get \"tcp\" protocol entry\n");
      exit (0);
   }

   /* Allocate a socket */
   s = socket(PF_INET, SOCK_STREAM, ppe->p_proto);
   if (s < 0) {
      fprintf (stderr, "can't create socket: %s\n", STRERROR);
      exit (0);
   }

   /* Bind the socket */
   if (bind(s, (struct sockaddr *)&sin, sizeof(sin)) < 0) {
      fprintf (stderr, "can't bind to %s port: %s\n", service, STRERROR);
      exit (0);
   }

   if (listen(s, qlen) < 0) {
      fprintf (stderr, "can't listen on %s port: %s\n", service, STRERROR);
      exit (0);
   }

   return s;
}
