static const char  rcsfile []= "$Header: /home/magrasjc/test/src/RCS/store.c,v 0.87.2.1 2000/02/05 06:13:53 magrasjc Exp $";
/*
 
 store.c
     
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
#include <stddef.h>
#include "bt_2bsql.h"

struct offset_list {
   long offset;
   struct offset_list *next;
};

struct offset_list *index_res=NULL;
  

void store_offset (void *r);          /* add offset onto list */
void append (struct offset_list *p);  /* append node onto list */
void free_offsets ();                 /* free offset list */

void store_offset (void *r)
{
   struct offset_list *new=NULL;

   new = (struct offset_list *) malloc (sizeof (struct offset_list));
   if (new == NULL)
      return;

   new->offset = ((UR *) r)->offset;
   new->next=NULL;
   if (index_res==NULL)
      index_res=new;
   append (new);
}

void append (struct offset_list *p)
{
   static struct offset_list *last=NULL;

   /* initialize last pointer for the start of a new list */
   if (p==NULL) {
      last=NULL;
      return;
   }

   if (!last) last=p;
   else last->next=p;
   p->next=NULL;
   last=p;
}


void free_offsets ()
{
   struct offset_list *q;

   while (index_res!=NULL) {
      q = index_res->next;
      free (index_res);
      index_res=q;
   }
   index_res=NULL;
   append (NULL);
}
