static const char  rcsfile []= "$Header: /home/magrasjc/test/src/RCS/sr.c,v 0.87.2.1 2000/02/05 06:13:51 magrasjc Exp $";
#include "config.h"
/*

   sr.c - routines that manipulate the search result information

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
#include <time.h>

#include "beagle.h"
#include "linklist.h"
#ifndef HAVE_GETDATE
#include"getdate.h"
#endif

#define YES 1
#define NO 0

void sr_initresult (struct bresult *sr);
void *sr_getfieldbyname (struct bresult *sr, int instance, char *fname);
void *sr_getvalue (struct bresult *sr, int instance, int attribute);
int sr_values (struct btable *tptr, struct bresult *sr);


void sr_initresult (struct bresult *sr)
{
   sr->resultcode=0;
   sr->ntuples=0L;
   sr->nfields=0L;
   strcpy (sr->errcode, "");

   /* free information for previous search */
   if (sr->fields != NULL)
      free_field (sr->fields);
   if (sr->values != NULL)
      free_field (sr->values);

   sr->fields=NULL;
   sr->f_last=NULL;
   sr->f=NULL;
   sr->values=NULL;
   sr->v_last=NULL;
   sr->v=NULL;
   sr->next=NULL;
}



void *sr_getfieldbyname (struct bresult *sr, int instance, char *fname)
{
   long i;
   struct bfield *v;

   /*   lprintf ("sr_getfieldbyname():result *=%u,i#=%d,#of fields=%d, field is >%s<",sr,sr->ntuples,instance,fname);*/

   /* advance to the beginning of the instance */
   for (i=0L, v=sr->values; i<sr->nfields*instance && v!=NULL; i++, v=v->next);

   /* advance to the attribute within the instance */
   for (i=0L; i<sr->nfields && v!=NULL; i++, v=v->next)
      if (!strcmp (v->fname, fname))
         return v->value;

  return NULL;
}



void *sr_getvalue (struct bresult *sr, int instance, int attribute)
{
   long i;
   struct bfield *v;

   lprintf ("sr_getvalue(%u,rec #%d,field # %d)",sr,instance,attribute);

   /* advance to the beginning of the instance */
   for (i=0L, v=sr->values; i<sr->nfields*instance+attribute && v!=NULL; i++, v=v->next);/* lprintf ("next=%d,field=%d",v->next,i%(sr->nfields+1));*/
   if (v==NULL) return NULL;

   return v->value;
}



/* store the result of the select operation in the result structure for
   sending to the client 
*/
int sr_values (struct btable *tptr, struct bresult *sr)
{
   struct bfield *sf, *fptr, *vptr, *p;
   int err=NO, i;
   long tuple;

   lprintf ("Storing search results TABLE: '%s'", tptr->name);
   lprintf ("Found %ld tuples", tptr->name, sr->ntuples);

    sr->v_last = NULL;
   fptr=tptr->values;
   for (tuple=0; tuple<sr->ntuples; tuple++) {

      /* store values for this tuple */
      for (sf=sr->fields; sf!=NULL && !err; sf=sf->next) {
         p=fptr;
         for (i=0; !err && fptr!=NULL && i<tptr->nfields; fptr=fptr->next,i++) {
            if (!fldcmpfld (sf, fptr)) {

               if (fptr->type==FTYPE_OID || fptr->type==FTYPE_INT)
                  lprintf ("   %s.%s = %ld", 
                     fptr->tname, fptr->fname, *( (long *) fptr->value));
               else if (fptr->type==FTYPE_CHAR)
                  lprintf ("   %s.%s = '%s'", 
                     fptr->tname, fptr->fname, (char *) fptr->value);
               else if (fptr->type==FTYPE_TIME) {
                  char dateBuf[32];
                  struct tm *workP=(struct tm*)TIME_ACCESS_TM(fptr);

                  strftime(dateBuf,32,"%H:%M:%S",workP);
                  sprintf (dateBuf,"%d:%d:%d",
                      workP->tm_hour,workP->tm_min,workP->tm_sec);
                  lprintf ("   %s.%s = '%d:%d:%d'",
                     fptr->tname, fptr->fname, workP->tm_hour,workP->tm_min,workP->tm_sec);
               }
               else if (fptr->type==FTYPE_DATE) {
                  char dateBuf[32];
                  struct tm *workP=(struct tm*)TIME_ACCESS_TM(fptr);

                  strftime(dateBuf,32,"%x",TIME_ACCESS_TM(fptr));

                  lprintf ("   %s.%s = '%s'", fptr->tname, fptr->fname,dateBuf);
               } 
               else if (fptr->type==FTYPE_TIMESTAMP) {
                  char dateBuf[32];
                  struct tm *workP=(struct tm*)TIME_ACCESS_TM(fptr);

                  strftime(dateBuf,32,"%x",workP);

                  lprintf ("   %s.%s = '%s'", fptr->tname, fptr->fname, dateBuf);
               } 
               else if (fptr->type==FTYPE_BLOB) {
               }
               else 
                  lprintf ("unknown field type %d in result_values()",fptr->type);


               vptr = field_node (fptr->fname, fptr->tname, fptr->value, fptr->type, fptr->recid);
               if (vptr != NULL) {
                  if (sr->values == NULL)
                     sr->values = vptr;
                  sr->v_last = store_field_list (vptr, sr->v_last);
               }
               else {
                  err = syntax_error (MEMORY);
                  lprintf ("memory allocation Failed");
               }
            }
         }  
         fptr=p;
      }

      /* advance to next tuple */
      for (i=0; fptr!=NULL && i<tptr->nfields; fptr=fptr->next, i++);

   }

   return err;
}
