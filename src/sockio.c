static const char  rcsfile []= "$Header: /home/magrasjc/test/src/RCS/sockio.c,v 0.87.2.1 2000/02/05 06:13:45 magrasjc Exp $";
/*
      
 sockio.c 

 Copyright (c) 1996 Robert Klein

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
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
  

#include "berror.h"

int sock_rev (int ssock, char *buf, size_t size);


int sock_recv (int ssock, char *buf, size_t size)
{
   int c=0, i;

   /* ten second timeout */
   for (i=0; i<10 && c < (int) size; i++) {
      c = recv( ssock, buf, size, MSG_PEEK ); /* how many bytes available? */
      if (c < (int) size)
         sleep (1);
   }

   c = (int) read(ssock, buf, size);

   if (c == (int) size)
      buf[c] = '\0';  /* null terminate the buffer */
   else
      buf[0] = '\0';  /* if read fails, make buf empty */

   return c;
}
