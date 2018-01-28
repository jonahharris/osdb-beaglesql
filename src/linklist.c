static const char  rcsfile []= "$Header: /home/magrasjc/test/src/RCS/linklist.c,v 0.87.2.1 2000/02/05 06:13:25 magrasjc Exp $";
#include "config.h"
/*
 
 linklist.c
     
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
#include <string.h>
#ifndef TM_IN_SYS_TIME
#include <time.h>
#else
#include <sys/time.h>
#endif

#include "beagle.h"
#include "log.h"
#include "mymalloc.h"


/* add table onto list */
struct btable *store_table_list (struct btable *p, struct btable *last);

 /* add field onto list */
struct bfield *store_field_list (struct bfield *p, struct bfield *last); 

  /* add index onto list */
void store_index_list (struct bindex *p);

struct bfield *copy_field_list (struct bfield *p);
struct btable *table_node (char *name);
struct bfield *field_node (char *fname, char *tname, void *value, int type, long recid);
struct bindex *index_node (char *iname, char *tname);
void free_table (struct btable *p);        /* free table list */
void free_field (struct bfield *p);        /* free field list */
void free_index (struct bindex *p);        /* free index list */



struct btable *store_table_list (struct btable *p, struct btable *last)
{
   if (!last) last=p;
   else last->next=p;
   p->next=NULL;
   last=p;
   return last;
}


struct bfield *store_field_list (struct bfield *p, struct bfield *last)
{
   if (!last) last=p;
   else last->next=p;
   p->next=NULL;
   last=p;
   return last;
}


void store_index_list (struct bindex *p)
{
   static struct bindex *last=NULL;

   /* initialize last pointer for the start of a new list */
   if (p==NULL) {
      last=NULL;
      return;
   }

lprintf ("STORE INDEX LIST");
   if (!last) last=p;
   else last->next=p;
   p->next=NULL;
   last=p;
}


struct bfield *copy_field_list (struct bfield *p)
{
   struct bfield *head=NULL, *new=NULL, *new_last=NULL, *q;

   for (q=p; q!=NULL; q=q->next) {

      /* allocate */
      new = field_node(q->fname, q->tname, q->value, q->type, q->recid);

      if (new==NULL) {
         free_field (head);
         head=NULL;
         break;
      }

      /* store head of list */
      if (head == NULL)  /* save the head of the fields list */
         head = new;

      /* add to list */ 
      new_last = store_field_list (new, new_last);
   }

   return head;
}


struct btable *table_node(char *name)
{
   struct btable *tptr;

   if ((tptr = (struct btable *) mymalloc (tptr, sizeof (struct btable)))==NULL)
      return NULL;

   strcpy (tptr->name, name);   /* store the table name */
   strcpy (tptr->iname, name);  /* default index */
   tptr->search_type = SEQ;     /* default search type */
   tptr->ro = 'n';              /* read only? default is no */
   tptr->nfields = 0L;
   /* initialize pointers in structure to NULL */
   tptr->fields=NULL;
   tptr->f_last=NULL;
   tptr->f=NULL;
   tptr->values=NULL;
   tptr->v_last=NULL;
   tptr->v=NULL;
   tptr->indexes=NULL;
   tptr->i=NULL;
   tptr->next=NULL;
   tptr->last=NULL;

   return tptr;
}


struct bfield *field_node (char *fname, char *tname, void *value, int type, long recid)
{
   struct bfield *vptr=NULL;
   long length;
   char *p;

   vptr = (struct bfield *) mymalloc (vptr, sizeof (struct bfield));

   if (vptr != NULL) {

      vptr->value = NULL;
      vptr->next = NULL;

      if (value != NULL) { 

         if (type==FTYPE_OID) {
            length = sizeof (long);
            vptr->value = (long *) mymalloc (vptr->value, length);
         }
         else if (type==FTYPE_CHAR) {
            length = strlen ((char *) value) + 1L;
            vptr->value = (char *) mymalloc (vptr->value, length);
         } /*magras@texas.net J.C. Magras--Jan 25, 1998*/
         else if (type==FTYPE_INT) {
            length = sizeof (long);
            vptr->value = (long *) mymalloc (vptr->value, length);
            lprintf ("Integer field with value %ld",*(long*)value);
         } 
         else if (type==FTYPE_TIME||type==FTYPE_DATE||type==FTYPE_TIMESTAMP) {
            length = sizeof(time_t)+sizeof(struct tm)+BEAGLETIME_;
            vptr->value = (time_t*) mymalloc (vptr->value, length);
	 }else {
             lprintf ("Unknown field type %d in field_node()",type); 
         }

         if (vptr->value!=NULL)
            memcpy (vptr->value, value, length);
         else {
            myfree (vptr);
            return NULL;
         }
	 /*  if (type==FTYPE_INT)
         lprintf ("created int field_node with value %d",*(long *)(vptr->value));
	 */
      }

      /* strip the quotes from the field name and table name if needed */

      if (*(fname)=='\'') fname++;
      strcpy (vptr->fname, fname);
      p=vptr->fname+strlen(vptr->fname)-1;
      if (*p=='\'') *p='\0';

      if (*(tname)=='\'') tname++;
      strcpy (vptr->tname, tname);
      p=vptr->tname+strlen(vptr->tname)-1;
      if (*p=='\'') *p='\0';

      vptr->type = type;
      vptr->recid = recid;
   }

   return vptr;
}



struct bindex *index_node (char *iname, char *tname)
{
   struct bindex *vptr=NULL;

   if ((vptr = (struct bindex *) mymalloc (vptr, sizeof (struct bindex))) != NULL) {
      strcpy (vptr->iname, iname);
      strcpy (vptr->tname, tname);
      vptr->fields=NULL;
      vptr->f_last=NULL;
      vptr->f=NULL;
      vptr->next=NULL;
   }

   return vptr;
}



void free_table (struct btable *p)
{
   struct btable *pp;
   struct bfield *q;

   for (pp=p; pp!=NULL;) {
      p = pp->next;
      free_field (pp->fields);
      for (q=pp->values; q!=NULL;) {
         pp->f = q->next;
         myfree (q->value); 
         q->value = NULL;
         myfree (q);
         q=pp->f;
      }
      free_index (pp->indexes);
      myfree (pp);
      pp = p;
   }
}


/* free field list */
void free_field (struct bfield *p)
{
   struct bfield *q;

   while (p!=NULL) {
      q = p->next;
      myfree (p->value);
      myfree (p);
      p=q;
   }
}


/* free index list */
void free_index (struct bindex *p)
{
   struct bindex *pp;

   for (pp=p; pp!=NULL;) {
      p = pp->next;
      free_field (pp->fields);
      myfree (pp);
      pp = p;
   }
}

