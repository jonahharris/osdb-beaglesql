/*

   sr.h - routines that manipulate the search result information

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
extern void sr_initresult (struct bresult *sr);
extern void *sr_getfieldbyname (struct bresult *sr, int instance, char *fname);
extern void *sr_getvalue (struct bresult *sr, int instance, int attribute);
extern int sr_values (struct btable *tptr, struct bresult *sr);
