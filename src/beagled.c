static const char  rcsfile []= "$Header: /home/magrasjc/test/src/RCS/beagled.c,v 0.87.2.1 2000/02/05 06:12:57 magrasjc Exp $";
#include "config.h"
/*

beagled.c
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
#include <sys/signal.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <sys/errno.h>
#include <netinet/in.h>

#include <termios.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>

#include "beagle.h"
#include "errexit.h"

#define YES 1
#define NO  0

#define	QLEN	        5   /* maximum connection queue length	*/

extern int	errno;
/* Changes in the new GNU headers forced this */
/* #ifndef __FreeBSD__ */
/* #ifndef PORT_LINUX */
#if !(PORT_SOLARIS|PORT_DECUNIX32)
extern char	*sys_errlist[];
#endif
/* #endif */
/* #endif */

char *currentDB=NULL;
char *querystr=NULL;
char *service=SERVICE;

static void reaper();

int main(int argc, char *argv[])
{
   struct sockaddr_in fsin;   /* the address of a client    */
   int alen;                  /* length of client's address */
   int msock;                 /* master server socket       */
   int ssock;                 /* slave server socket        */
   char str_ssock[5];

   if (getenv ("BG_DATA")==NULL) {
      fprintf (stderr, "Environment BG_DATA not set\n");
      exit (0);
   }

   switch (argc) {
      case 1:  break;
      case 2:  service = argv[1];
	       break;
      default: errexit("usage: beagled [port]\n");
     
   }

   msock = passiveTCP(service, QLEN);

#ifdef SIGTSTP  /* BSD */
   (void) signal(SIGCHLD, reaper);
#else
   (void) signal(SIGCHLD, SIG_IGN); /* for SYS V type systems */
#endif

#if PORT_LINUX
   (void) signal(SIGCHLD, SIG_IGN); /* for SYS V type systems */
#endif

   (void) signal(SIGPIPE, SIG_IGN);

   while (1) {
      alen = sizeof(fsin);
      ssock = accept(msock, (struct sockaddr *)&fsin, &alen);
      if (ssock < 0) {
         if (errno == EINTR)
            continue;
         errexit("accept: %s\n", STRERROR);
      }
      sprintf (str_ssock, "%d", ssock);
      switch (fork()) {
         case 0:  /* child */
	          (void) close(msock);
	          execlp ("beagleb", "beagleb", str_ssock, NULL);
	          exit(1);
         case -1: /* error */
	          errexit("fork: %s\n", STRERROR);
                  break;
         default: /* parent */
	          (void) close(ssock);
      }
   }
}


/*------------------------------------------------------------------------
* reaper - clean up zombie children
*------------------------------------------------------------------------
*/
void reaper()
{
#ifdef HAVE_WAITPID
   int status;
#else
   union wait statusp;
#endif
   int pid;

#ifdef HAVE_WAITPID
        while ((pid = waitpid(-1, &status, WNOHANG)) > 0) ;
#else
        while ((pid = wait3(&statusp, WNOHANG, NULL)) > 0);
#endif
}
