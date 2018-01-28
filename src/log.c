static const char  rcsfile []= "$Header: /home/magrasjc/test/src/RCS/log.c,v 0.87.2.1 2000/02/05 06:13:27 magrasjc Exp $";
/*
      
 log.c
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

#ifdef PORT_NEXT
   #include <stdarg.h>
#else
   #include <varargs.h>
#endif
#include <stdio.h>
#include <time.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>

#define YES 1
#define NO  0

int lprintf();
void start_logging();
void stop_logging();
char *curtime ();

FILE *logfp=NULL;
int debug=YES;


void start_logging()
{
   if (debug) {
      logfp = fopen ("beagled.log", "a"); 
      if (logfp!=NULL)
         fseek (logfp, 0L, SEEK_END);
   }
}

void stop_logging()
{  
   if (logfp!=NULL) fclose (logfp);
}

int lprintf(format, va_alist)
char *format;
va_dcl
{
   va_list args;

   if (logfp!=NULL) {
      va_start(args);
      fprintf (logfp, "\n%s (pid %ld): ", curtime(), (long) getpid());
      vfprintf (logfp, format, args);
      va_end(args);
      fflush(logfp);
   }
}


char *curtime ()
{
   struct tm *ptr;
   time_t lt;
   char *p;

   lt = time(NULL);
   ptr=localtime(&lt);
   p = asctime(ptr);
   *(strchr (p, '\n')) = '\0';
   return p;
}
