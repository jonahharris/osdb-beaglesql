static const char  rcsfile []= "$Header: /home/magrasjc/test/src/RCS/int_sql.c,v 0.87.2.1 2000/02/05 06:13:20 magrasjc Exp $";
#include "config.h"
/*

   int_sql.c - functions used for SQL calls within the backend

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

#include "beagle.h"
#include "parse.h"
#include "beagleb.h"


int int_SQLselect (char *command, struct bresult *sr);
int int_SQLinsert (char *command);
int int_SQLdelete (char *command, struct bresult *sr);

int int_SQLselect (char *command, struct bresult *sr)
{
   struct clist *tokens;
   int ret;

   lprintf ("Internal SQL SELECT command");
   tokens = parse_tokens (command);
   ret = SQLselect (tokens, sr);
   /*   lprintf ("internal select returns %d tuples",sr->ntuples); */
    free_tokens (tokens);
   return ret;
}


int int_SQLinsert (char *command)
{
   struct clist *tokens;
   int ret;

   lprintf ("Internal SQL INSERT command");
   tokens = parse_tokens (command);
   ret = SQLinsert (tokens);
   free_tokens (tokens);
   return ret;
}


int int_SQLdelete (char *command, struct bresult *sr)
{
   struct clist *tokens;
   int ret;

   lprintf ("Internal SQL DELETE command");
   tokens = parse_tokens (command);
   ret = SQLdelete (tokens, sr);
   free_tokens (tokens);
   return ret;
}
