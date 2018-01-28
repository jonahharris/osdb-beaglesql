static const char  rcsfile []= "$Header: /home/magrasjc/test/src/RCS/is.c,v 0.87.2.1 2000/02/05 06:13:22 magrasjc Exp $";
/*

   is.c -  is...() type functions for BeagleSQL


Copyright 1996 Robert Klein   All Rights Reserved

Permission to use, copy, modify and distribute this software and its
documentation, is hereby granted to educational institutions, their
faculty, and full-time students, non-commercial research organizations,
registered charities, and registered not-for-profit and non-profit
organizations without fee provided that this license agreement and
copyright information appears in all copies.

Permission to use of this software by any other person or organization 
if hereby granted for the current version of the software and it's
documentation provided that this license agreement and copyright
information appears in all copies.

Commercial redistribution of this software, by itself or as part of
another application is allowed only under express written permission of
Robert Klein and may entail licensing fees.

ROBERT KLEIN DISCLAIM ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, 
INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO 
EVENT SHALL ROBERT KLEIN BE LIABLE FOR ANY SPECIAL, INDIRECT OR 
CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF 
USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR 
OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR 
PERFORMANCE OF THIS SOFTWARE.
*/

#include <stdio.h>
#include <stdlib.h>

#define YES 1
#define NO !YES

int is_sysfld(char *s);

/* 
   test of to see is the string pointed to by 's' is a system defined field name
*/
int is_sysfld(char *s)
{
   if (strcmp (s, "oid"))
      return NO;
   return YES;
}
