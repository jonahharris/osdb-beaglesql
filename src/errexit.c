static const char  rcsfile []= "$Header: /home/magrasjc/test/src/RCS/errexit.c,v 0.87.2.1 2000/02/05 06:13:14 magrasjc Exp $";
#include "config.h"
/*
      
 errexit.c 

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
/*#ifdef PORT_NEXT*/
#if ( HAVE_STDARG_H )
   #include <stdarg.h>
#else
   #include <varargs.h>
#endif
#include <stdio.h>

/*VARARGS1*/
int
errexit(format, va_alist)
char	*format;
va_dcl
{
	va_list	args;

	va_start(args);
	vfprintf (stderr, format, args);
        /* _doprnt(format, args, stderr); */
	va_end(args);
	exit(1);
}
