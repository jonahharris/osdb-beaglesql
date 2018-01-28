static const char  rcsfile []= "$Header: /home/magrasjc/test/src/RCS/filesys.c,v 0.87.2.1 2000/02/05 06:13:16 magrasjc Exp $";
/*
      
 filesys.c
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

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <termios.h>
#include <time.h>
#include <sys/time.h>
#include <errno.h>

#include "beagle.h"
#include "log.h"
#include "int_sql.h"
#include "parse.h"
#include "linklist.h"
#include "bt.h"
#include "mymalloc.h"
#ifndef HAVE_GETDATE
#include "getdate.h"
#endif
#include "auth.h"
#include "sr.h"

#define YES 1
#define NO 0

/* get table information (fields,type, sizes, etc) */
struct btable *sys_gettableinfo (char *table);  
struct btable *gettableinfo (char *table);  
int puttableinfo (struct btable *tptr);
int getindexinfo (struct bindex *iptr);
int putindexinfo (struct bindex *iptr);
int apendindexinfo (struct bindex *iptr);
FILE *bg_fopen (char *db, char *name, char *ext, char *flags);
void bg_fclose (FILE *fp);
long read_first(FILE *fp, struct btable *tptr, struct clist *where, int action,int*);
long read_next (FILE *fp, struct btable *tptr, struct clist *where, int action,int *);
long read_record (struct btable *tptr, long offset, struct clist *where, int action,int *match );
long write_record (char *dbname, char *tname, struct bfield *start, struct bfield *stop, long recid,unsigned long);
int delete_record (char *dbname, char *tname, long offset);
void delete_table_files (struct btable *tptr);
void clean_filesys(void);
/*int read_match=NO;  Set if the last read_record() matched the Where clause */
static char *data_buffer=NULL;
static struct bdb  *DBlistP    =NULL;
/* the following are defined in beagleb.c */
extern char *getCurrentDB();
extern int syntax_error (int err);


struct btable *sys_gettableinfo (char *tname)
{
   struct btable *tptr=NULL;
   struct bfield *fptr=NULL;
   struct bindex *iptr=NULL;
   FILE *fp;
   char attrib;
   char name[MAXIDSIZE];  /* field name */
   char otname[MAXIDSIZE]; /* name of the original table (for joined tables) */
   int ftype, c;
    

   if ((fp = bg_fopen (getCurrentDB(), tname, "", "r")) == NULL) {
      lprintf ("Can't Open Table Header Information");
      return NULL;
   }

   if ((tptr=table_node (tname)) == NULL) {
      lprintf ("ERROR: Can't allocate Memory for Table");
      return NULL;
   }

   lprintf ("Getting Table Information");
   while ((c = fscanf (fp, "%c %s %d %s\n", &attrib, name, &ftype, otname)) == 4) {

      if (attrib == 'f') {
         /* use otname because it could be different from tname in the case of
            joined tables
         */
         fptr = field_node (name, otname, NULL, ftype, -1);

         if (fptr == NULL) {
            lprintf ("ERROR: Can't allocate Memory for Field List");
            free_table (tptr);
            return NULL;
         }

         if (tptr->fields == NULL)  /* save the head of the fields list */
            tptr->fields = fptr;

         tptr->f_last = store_field_list (fptr, tptr->f_last); /* add this node to the list */
         tptr->nfields++;         /* increment the field counter */
         lprintf ("   %s %d", fptr->fname, fptr->type);
      }
      else if (attrib == 'i') {
         /* use otname because it could be different from tname in the case of
            joined tables
         */
         iptr = index_node (name, otname);

         if (iptr == NULL) {
            lprintf ("ERROR: Can't allocate Memory for Index List");
            free_table (tptr);
            store_index_list (NULL);  /* Initialize the static variable in store() */
            return NULL;
         }

         getindexinfo (iptr);

         if (tptr->indexes == NULL)  /* save the head of the fields list */
            tptr->indexes = iptr;

         store_index_list (iptr); /* add this node to the list */
         lprintf ("   INDEX %s for table %s", iptr->iname, iptr->tname);
      }
   }

   bg_fclose (fp);
   store_index_list (NULL); /* initialize the static last pointer */

   lprintf ("   %ld fields", tptr->nfields);

   return tptr;
}


struct btable *gettableinfo (char *tname)
{
   struct btable *tptr=NULL;
   struct bfield *fptr=NULL;
   struct bindex *iptr=NULL;
   FILE *fp;
   char attrib;
   char name[MAXIDSIZE];  /* field name */
   char otname[MAXIDSIZE]; /* name of the original table (for joined tables) */
   int ftype, c, i;
   struct bresult sr = {0,0L,0L,"",NULL,NULL,NULL,NULL,NULL,NULL,NULL};
   char request [256];

   /* check to see if it's a system table */
   if (!strncmp (tname, "sys_", 4))
      return sys_gettableinfo (tname);

   /* Initialize search_result structure */
   sr_initresult(&sr);
   sprintf (request, "sys_table_ro from sys_table where sys_table_name = '%s'", tname);
   int_SQLselect (request, &sr);

   if (sr.ntuples) {

      if ((tptr=table_node (tname)) == NULL) {
         lprintf ("ERROR: Can't allocate Memory for Table");
         sr_initresult(&sr);
         return NULL;
      }
      tptr->ro=*(((char *) sr_getvalue (&sr, 0, 0))+1);
      sr_initresult(&sr);
      /*

      */
      sprintf (request, "sys_field_name , sys_field_ltname , sys_field_type from sys_field where sys_field_tname = '%s' ", tname);
      int_SQLselect (request, &sr);

      {
         int x;struct bfield *p=sr.values;
         for (x=0;  x < sr.ntuples ;x++,p=p->next) {
             lprintf ("field %s checked",p->fname);
             if (p==sr.v_last ) break;
	 }
      }  
       tptr->nfields = sr.ntuples;
      /*      tptr->nfields = sr.nfields;*/
      lprintf ("   %ld fields", tptr->nfields);

      for (i=0; i<tptr->nfields; i++) {
         fptr = field_node ((char *)sr_getvalue(&sr,i,0), (char *)sr_getvalue(&sr,i,1), NULL,*((long *)sr_getvalue(&sr,i,2)),1);

         if (fptr == NULL) {
            lprintf ("ERROR: Can't allocate Memory for Field List");
            free_table (tptr);
            return NULL;
         }

         if (tptr->fields == NULL)  /* save the head of the fields list */
            tptr->fields = fptr;

         tptr->f_last = store_field_list (fptr, tptr->f_last); 
      }

      sr_initresult(&sr);

      if ((fp = bg_fopen (getCurrentDB(), tname, "", "r")) == NULL) {
         lprintf ("Can't Open Table Header Information");
         return NULL;
      }

      lprintf ("Getting Table Information");
      while ((c = fscanf (fp, "%c %s %d %s\n", &attrib, name, &ftype, otname)) == 4) {

         if (attrib == 'f') {
            /* use otname because it could be different from tname in the
               case of joined tables
            */
/*
            fptr = field_node (name, otname, NULL, ftype, -1);

            if (fptr == NULL) {
               lprintf ("ERROR: Can't allocate Memory for Field List");
               free_table (tptr);
               return NULL;
            }

            if (tptr->fields == NULL) 
               tptr->fields = fptr;

            tptr->f_last = store_field_list (fptr, tptr->f_last); 
            lprintf ("   %s %d", fptr->fname, fptr->type);
*/
         }
         else if (attrib == 'i') {
            /* use otname because it could be different from tname in the case of
               joined tables
            */
            iptr = index_node (name, otname);
 
            if (iptr == NULL) {
               lprintf ("ERROR: Can't allocate Memory for Index List");
               free_table (tptr);
               store_index_list (NULL);  /* Initialize the static variable in store() */
               return NULL;
            }

            getindexinfo (iptr);

            if (tptr->indexes == NULL)  /* save the head of the fields list */
               tptr->indexes = iptr;

            store_index_list (iptr); /* add this node to the list */
            lprintf ("   INDEX %s for table %s", iptr->iname, iptr->tname);
         }
      }

      bg_fclose (fp);
      store_index_list (NULL); /* initialize the static last pointer */


      return tptr;
   }
   lprintf ("gettableinfo(): table not found in sys_table");
   return NULL;
}


int puttableinfo (struct btable *tptr)
{
   FILE *fp;
   struct bfield *fptr;
   struct bindex *iptr;
   char request [256];

   /* insert table name into sys_table */
   lprintf("puttableinfo");
   lprintf("getCurrentDB()=%s",getCurrentDB());
   lprintf("tptr->name=%s",tptr->name);
   lprintf("tptr->ro=%c",tptr->ro);
   lprintf("BGUSER=%s",BG_user);
   sprintf (request, "sys_table values ('%s','%s','%s','%c') ", getCurrentDB(), tptr->name, BG_user, tptr->ro);
   int_SQLinsert (request);

   /* contruct file name for table */
   if ((fp = bg_fopen (getCurrentDB(), tptr->name, "", "w")) != NULL) {
      /* write field information */
      for (fptr=tptr->fields; fptr!=NULL;fptr=fptr->next) {
         fprintf (fp, "f %s %d %s\n", fptr->fname, fptr->type, fptr->tname);

         /* insert field info into sys_field */
         sprintf (request, "sys_field values ('%s','%s','%s',%d) ", tptr->name, fptr->tname, fptr->fname, fptr->type);
         int_SQLinsert (request);

      }
      /* write index information */
      for (iptr=tptr->indexes; iptr!=NULL;iptr=iptr->next)
         fprintf (fp, "i %s 0 %s\n", iptr->iname, iptr->tname);
      bg_fclose (fp);
      return 1;
   }
   return 0;
}



int putindexinfo (struct bindex *iptr)
{
   FILE *fp;
   struct bfield *fptr;
   int i;
   char request [256];

   if ((fp = bg_fopen (getCurrentDB(), iptr->iname, "", "w")) != NULL) {
      /* write field information */
      for (i=0,fptr=iptr->fields; fptr!=NULL;fptr=fptr->next,i++) {
         fprintf (fp, "f %s %d %s\n", fptr->fname, fptr->type, fptr->tname);

         /* insert field info into sys_field */
         sprintf (request, "sys_index values ('%s','%s','%s',%d,%d) ", fptr->tname, iptr->iname, fptr->fname, fptr->type, i);
         int_SQLinsert (request);

      }
      bg_fclose (fp);
      return 1;
   }
   return 0;
}



int getindexinfo (struct bindex *iptr)
{
   struct bfield *fptr=NULL;
   FILE *fp;
   char attrib;
   char name[MAXIDSIZE];  /* field name */
   char otname[MAXIDSIZE]; /* name of the original table (for joined tables) */
   int ftype, c;

   iptr->f_last = NULL;

   if ((fp = bg_fopen (getCurrentDB(), iptr->iname, "", "r")) == NULL) {
      lprintf ("Can't Open Table Header Information");
      return 0;
   }

   lprintf ("Getting Index Information");
   while ((c = fscanf (fp, "%c %s %d %s\n", &attrib, name, &ftype, otname)) == 4) {

      if (attrib == 'f') {
         /* use otname because it could be different from tname in the case of
            joined tables
         */
         fptr = field_node (name, otname, NULL, ftype, -1);

         if (fptr == NULL) {
            lprintf ("ERROR: Can't allocate Memory for Field List");
            return 0;
         }

         if (iptr->fields == NULL)  /* save the head of the fields list */
            iptr->fields = fptr;

         iptr->f_last = store_field_list (fptr, iptr->f_last); /* add this node to the list */
         lprintf ("   %s %d", fptr->fname, fptr->type);
      }
   }

   bg_fclose (fp);

   return 1;
}



int appendindexinfo (struct bindex *iptr)
{
   FILE *fp;
   struct bindex *i;

   if ((fp = bg_fopen (getCurrentDB(), iptr->tname, "", "a")) != NULL) {
      fseek (fp, 0L, SEEK_END);
      /* write index information */
      for (i=iptr; i!=NULL;i=i->next)
         fprintf (fp, "i %s 0 %s\n", i->iname, i->tname);
      bg_fclose (fp);
      return 1;
   }
   return 0;
}


FILE *bg_fopen (char *db, char *name, char *ext, char *flags)
{
   char path[256];

   if (!strcmp (name, "sys_db") || !strcmp (name, "sys_user") ||
       !strcmp (name, "sys_auth")) {
      if (strcmp (ext, "bt_driver")) 
         sprintf (path, "%s/%s%s", DBROOT, name, ext);
      else 
         sprintf (path, "%s/%s", DBROOT, name);
   }
   else if (strcmp (ext, "bt_driver")) 
      sprintf (path, "%s/%s/%s%s", DBROOT, db, name, ext);
   else
      sprintf (path, "%s/%s/%s", DBROOT, db, name);


   if (strcmp (ext, "bt_driver")) {
      lprintf ("BG_FOPEN: Opening file: %s", path);
      return fopen (path, flags);
   }
   else {
      lprintf ("BG_FOPEN: bt_driver Opening index: %s", path);
      bt_driver ('o', path);  /* open index */
      return NULL;
   }
}


void bg_fclose (FILE *fp)
{
   lprintf ("Closing File");
   fclose (fp);
}

long read_first (FILE *fp,               /* Index file pointer */
                 struct btable *tptr,    /* pointer to the current table */
                 struct clist *where,    /* where clause */
                 int action,int *read_match)             /* action flag */
{
   struct idx_rec idx;

   lprintf ("read_first(%ld)", ftell(fp));

   if (fread (&idx, sizeof (struct idx_rec), 1, fp) != 1) {
      lprintf ("ERROR: read_first() Reading Index Record");
      return ERROR;
   } 
   lprintf ("Table Offset for first record %ld", idx.recid);
   return read_record (tptr, idx.recid, where, action,read_match);
}

 

long read_next (FILE *fp,               /* Index file pointer */
                struct btable *tptr,    /* pointer to the current table */
                struct clist *where,    /* where clause */
                int action, int* read_match)             /* action flag */
{
   struct idx_rec idx;
   lprintf ("read_next(%ld)",ftell(fp));
   if (fread (&idx, sizeof (struct idx_rec), 1, fp) != 1) {
      lprintf ("ERROR: read_next() Reading Index Record");
      return ERROR;
   } 
   lprintf ("Table Offset for next record %ld", idx.recid);
   return read_record (tptr, idx.recid, where, action,read_match);
}




long read_record (struct btable *tptr,    /* pointer to the current table */
                  long offset,            /* position of record */
                  struct clist *where,    /* where clause */
                  int action,             /* action flag */
                  int  *record_match)
{
   char *p, *q, *r, temp[512], indexstr[512];
   int err=NO, c;
   long attrlen, sv_offset;
   FILE *fp;
   struct record_seg rec;
   struct bfield *fptr=NULL, *fptr2=NULL;
   struct bfield *vptr=NULL;
   struct bindex *iptr=NULL;
   struct clist *w=NULL;
   extern int getdate_err;

   if (action==DELETE_RECORD)
      lprintf ("read_record() for deletion");
   else
      lprintf ("read_record() for search");

   if (tptr == NULL)
      return ERROR;

   /* open the file */
   if ((fp = bg_fopen (getCurrentDB(), tptr->name, ".data", "r+b")) == NULL) {
      lprintf ("Can't Open Table Data File");
      return ERROR;
   }

   lprintf ("Seeking to %ld", offset);

   /* position to the front of the record */
   if (fseek (fp, offset, SEEK_SET)) {
      lprintf ("fseek() - %s", strerror (errno));
      bg_fclose (fp);
      return ERROR;
   }

   /* read file header information */
   if (fread (&rec, sizeof (struct record_seg), 1, fp) != 1) {
      lprintf ("fread() - %s", strerror (errno));
      bg_fclose (fp);
      return ERROR;
   }

   /* record is flagged as deleted, ignore and return */   
   if (rec.stat == 'd') {
      lprintf ("deleted record, ignore");
      *record_match=NO;
      bg_fclose (fp);
      return offset;
   }


   /* allocate a large enough buffer to store all the data for the record */
   q = data_buffer = (char *) myrealloc (data_buffer, (size_t) DATASEG_SIZE * rec.nseg);
   if (q == NULL) {
      lprintf ("ERROR: realloc() - Can't Allocate Memory");
      bg_fclose (fp);
      return ERROR;
   }

   memcpy (q, rec.data, DATASEG_SIZE);
   q += DATASEG_SIZE;

   lprintf ("rec.stat = %c", rec.stat);
   lprintf ("rec.recid = %ld", rec.recid);
   lprintf ("rec.next = %ld", rec.next);
   lprintf ("rec.segment = %d", rec.segment);
   lprintf ("rec.nseg = %d", rec.nseg);

   /* if there is more than one data segment for the record then read in the
      rest of the data into the data buffer
   */ 
   for (c=1; c<rec.nseg; c++) {
      lprintf ("Reading the Rest if the Segments");
      if (fseek (fp, rec.next, SEEK_SET)) {
         lprintf ("fseek() - %s", strerror (errno));
         bg_fclose (fp);
         return ERROR;
      }
      if (fread (&rec, sizeof (struct record_seg), 1, fp) != 1) {
         lprintf ("fread() - %s", strerror (errno));
         bg_fclose (fp);
         return ERROR;
      }
      memcpy (q, rec.data, DATASEG_SIZE);
      q += DATASEG_SIZE;
      lprintf ("rec.stat = %c", rec.stat);
      lprintf ("rec.recid = %ld", rec.recid);
      lprintf ("rec.next = %ld", rec.next);
      lprintf ("rec.segment = %d", rec.segment);
   }


   q = data_buffer;
   for (fptr=tptr->fields; fptr != NULL && !err; fptr=fptr->next) {
      memcpy (&attrlen, q, sizeof (long));
      q += sizeof (long);

      if (fptr->type==FTYPE_OID||fptr->type==FTYPE_INT) {
         if (fptr->value==NULL) {  /* no need to realloc longs */
            lprintf ("allocating %ld bytes of memory", sizeof(long));
            fptr->value = (long *) mymalloc ( fptr->value, sizeof(long));
         }
      }
      else if (fptr->type==FTYPE_CHAR) {
         lprintf ("allocating %ld bytes of memory", attrlen + 1L);
         fptr->value = (char *) myrealloc ( (char *) fptr->value, (size_t) (attrlen+1L));
      } else if (fptr->type==FTYPE_TIME||fptr->type==FTYPE_DATE||fptr->type==FTYPE_TIMESTAMP) {
         fptr->value = (char *) myrealloc ( (char *) fptr->value, (size_t) (sizeof(struct tm)+sizeof(time_t)))+BEAGLETIME_;
      } 
      else if (fptr->type==FTYPE_BLOB) {
         
      }
      else lprintf ("unrecognized type %d found",fptr->value);

      if (fptr->value == NULL) {
         err = syntax_error (MEMORY);
         lprintf ("memory allocation Failed");
      }
      else { 
         memcpy (fptr->value, q, attrlen);

         q += attrlen;
         if (fptr->type==FTYPE_CHAR) {
            p = (char *) fptr->value;  /* NULL Terminate character data */
            p[attrlen] = '\0';
         }

         if (fptr->type==FTYPE_OID)
            lprintf ("read OID value %ld", *((long *) fptr->value));
         else if (fptr->type==FTYPE_INT)
            lprintf ("read INTEGER value %ld", *((long *) fptr->value));
         else if (fptr->type == FTYPE_CHAR)
            lprintf ("read CHAR value '%s'", (char *) fptr->value);
         else if (fptr->type == FTYPE_TIME) {
            char timebuf[32] ;
            int  p_i;
            struct tm *workP = localtime((time_t*)TIME_ACCESS_TIME_T(fptr));
            time_t scratch=*(time_t*)TIME_ACCESS_TIME_T(fptr);

            strftime(timebuf,32,"%H:%M:%S",workP);
            lprintf ("read TIME value %s %u",timebuf, scratch);
         }
          else if (fptr->type == FTYPE_DATE) {
            char timebuf[32] ;
            int  p_i;
            struct tm *workP = localtime((time_t*)TIME_ACCESS_TIME_T(fptr));
            time_t scratch = *(time_t*)TIME_ACCESS_TIME_T(fptr);
            strftime(timebuf,32,"%x",workP);
            lprintf ("read DATE value %s %u",timebuf,scratch);
         }else if (fptr->type == FTYPE_TIMESTAMP) {
            char timebuf[32] ;
            int  p_i;
            time_t scratch=*(time_t*)TIME_ACCESS_TIME_T(fptr);
            struct tm *workP=(struct tm*) localtime((time_t*)TIME_ACCESS_TIME_T(fptr));

            strftime(timebuf,32,"%C",workP);
            lprintf ("read TIMESTAMP value %s %u",timebuf,scratch );
         } else if (fptr->type == FTYPE_BLOB) {

         }
         else
            lprintf ("Warning - Unknown field type");

         /* 
            Store values for the variables in the where clause.  These
            variable values will be used by the expression parser to
            determine is this record matches the expression
         */
         for (w=where; w!=NULL; w=w->next) {
/*
            lprintf ("checking token '%s' for field '%s.%s'", 
               w->token, fptr->tname, fptr->fname);
*/

            /* strip THIS table name prefix from field name if there 
            */
            p = w->token;
            sprintf (temp, "%s.", fptr->tname);
            if (!strncmp (w->token, temp, strlen (temp)))
               p += strlen (temp);

            /* check to see if the field name and table name match the
               variable in the field definition
            */
/*
            lprintf ("look for this field %s found in where clause in %s",p,fptr->fname); 
*/
            if (!strcmp (p, fptr->fname) && 
                !strncmp (w->token, fptr->tname, strlen(fptr->tname))) {
               /*lprintf ("   field match found");*/

               w->type = fptr->type;
               if (fptr->type==FTYPE_OID||fptr->type==FTYPE_INT) {
                  if (w->value==NULL) /* no need to realloc longs */
                     w->value = (long *) mymalloc (w->value, sizeof(long));
                  memcpy((void *)w->value ,(void*)fptr->value,sizeof(long));
               } else if (fptr->type==FTYPE_TIME||fptr->type==FTYPE_DATE||fptr->type==FTYPE_TIMESTAMP) {
                   time_t scratch;
                   if (w->value==NULL)
                         w->value = (char *) mymalloc (w->value,16);
                   scratch=*(time_t*)fptr->value;
                   sprintf((char *)w->value ,"%u",scratch);

               }else if (fptr->type==FTYPE_CHAR) {
                  w->value = (char *) myrealloc (w->value,(size_t)(attrlen+1L));
                  memcpy (w->value, fptr->value, attrlen+1L);
               }else if (fptr->type==FTYPE_BLOB) {
               }
               w->type = fptr->type;
            }
         }
      }
   }


   lprintf ("WHERE clause after value subsitution");
   for (w=where; w!=NULL; w=w->next) {
      if (w->value==NULL) {

            struct tm *scratchP;
            struct tm ws;
            int length,error;
            time_t secCount;
            char *CheckP=(char *) &secCount;

            length=strlen(w->token)-1;
            if (*(char*)w->token=='\''  && w->next==NULL) {
                if (where->type==FTYPE_TIME ||
                    where->type==FTYPE_DATE || where->type==FTYPE_TIMESTAMP) {
		   *(char*)w->token=' ';
                      *(char*)(w->token+length)=' ';
                      lprintf ("date token %s",(char*)w->token);

                      scratchP = getdate((char*)w->token);
                      if (scratchP==NULL)
                          lprintf ("getdate failed with %d",getdate_err);
                      sprintf(w->token,"%u",secCount=(time_t)mktime(scratchP));
                }
                lprintf ("literal   %s",(char*)w->token);
                w->type=where->type;
	    }
      } else {
         if (w->type==FTYPE_OID||w->type==FTYPE_INT)
            lprintf ("integer   %ld", *((long *) w->value));
         else if (w->type==FTYPE_TIME ) {
            lprintf ("time   %s",(char*)w->value/**(time_t*)w->value*/);
         }
         else if (w->type==FTYPE_DATE ) {
            lprintf ("date   %s",(char*)w->value/**(time_t*)w->value*/);
         }
         else if (w->type==FTYPE_TIMESTAMP ) {
            lprintf ("timestamp   %s",(char*)w->value);
         }
         else if (w->type==FTYPE_BLOB) {

         }
          else /* FTYPE_CHAR */
            lprintf ("string   %s", (char *) w->value);
      }
   }


   /* BOOLEAN_get_exp() executes a call to the boolean expresion parser */

   *record_match=NO;
   if (where == NULL || BOOLEAN_get_exp(where)) {
      *record_match=YES;

      /* copy fields to the value list */

      for (fptr=tptr->fields; fptr!=NULL; fptr=fptr->next) {
         vptr = field_node (fptr->fname, fptr->tname, fptr->value, fptr->type, rec.recid);
         if (vptr != NULL) {
            if (tptr->values == NULL) 
               tptr->values = vptr; 
            tptr->v_last = store_field_list (vptr, tptr->v_last);
         }
         else {
            err = syntax_error (MEMORY);
            lprintf ("memory allocation Failed");
         }
      }

      if (action==DELETE_RECORD) {

         /* flag the record as deleted */

         lprintf ("deleting record segments seeking to %ld", offset);
         /* position to the front of the record */
         if (fseek (fp, offset, SEEK_SET)) {
            lprintf ("fseek() - %s", strerror (errno));
            bg_fclose (fp);
            return ERROR;
         }

         /* read file header information */
         if (fread (&rec, sizeof (struct record_seg), 1, fp) != 1) {
            lprintf ("fread() - %s", strerror (errno));
            bg_fclose (fp);
            return ERROR;
         }

         lprintf ("Flagging offset %ld as deleted", offset);
         rec.stat = 'd';
         fseek (fp, offset, SEEK_SET);
         fwrite (&rec, sizeof (struct record_seg), 1, fp);

         /* delete record from any indexes attached to this table */
         for (iptr=tptr->indexes; iptr!=NULL; iptr=iptr->next) {
            bg_fopen (getCurrentDB(), iptr->iname, "bt_driver", ""); /* open index */
            lprintf ("DELETE FROM INDEX %s", iptr->iname);

            memset (indexstr, ' ', 256); /* initialize to spaces */
            /* add existing records to index */
            p = indexstr;

            /* make the value pointers in the bindex field list point
               to the values already malloc()'d and stored in the btable
               field list.  Needs to make sure that these values aren't
               free()'d twice BTW.
            */
            for (fptr=tptr->values; fptr!=NULL; fptr=fptr->next) {
               for (fptr2=iptr->fields; fptr2!=NULL; fptr2=fptr2->next) {
                   if (!strcmp (fptr->fname, fptr2->fname))
                      fptr2->value = fptr->value;
               }
            }

            for (fptr=iptr->fields; fptr!=NULL; fptr=fptr->next) {

               if (fptr->type==FTYPE_OID||fptr->type==FTYPE_INT)
                  lprintf ("field='%s' value=%ld", fptr->fname, *((long *) fptr->value));
               else if (fptr->type==FTYPE_TIME) {
                   char timeBuf[32];
                   strftime(timeBuf,32,"%H:%M:%S",
                        localtime((time_t*)TIME_ACCESS_TIME_T(fptr)));
                   lprintf ("field='%s' value=%s", fptr->fname, timeBuf);
               } else if (fptr->type==FTYPE_DATE) {
                   char timeBuf[32];
                   strftime(timeBuf,32,"%x",
                        localtime((time_t*)TIME_ACCESS_TIME_T(fptr)));
                   lprintf ("field='%s' value=%s", fptr->fname, timeBuf);
               } else if (fptr->type==FTYPE_TIMESTAMP) {
                   char timeBuf[32];
                   struct tm *workP=(struct tm*)TIME_ACCESS_TM(fptr);
                   strftime(timeBuf,32,"%C",
                        localtime((time_t*)TIME_ACCESS_TIME_T(fptr)));
                   lprintf ("field='%s' value=%s (%u) %d", fptr->fname, timeBuf,*(time_t*)TIME_ACCESS_TIME_T(fptr),workP->tm_mon);
               } else if (fptr->type==FTYPE_BLOB) {

               }
               else
                  lprintf ("field='%s' value=%ld", fptr->fname, (char *) fptr->value);

               /* only allow INDEX_TOKEN_LEN chars per field in the index */

               q = fptr->value;
               fptr->value = NULL;
               if (*q == '\'') {  /* skip quote if there */
                  q++;
                  /* copy until a quote */
                  r = (char *) memccpy (p, q, (int) '\'', (size_t) INDEX_TOKEN_LEN);
               }
               else
                  /* copy until a NULL */
                  r = (char *) memccpy (p, q, 0, (size_t) INDEX_TOKEN_LEN);

              /* if memccpy reached the 'stop' character during the operation
                  then replace that character in the destination string with a
                  space. 
               */
               if (r != NULL && r != indexstr)
                  *(r-1) = ' ';

               p+=INDEX_TOKEN_LEN;  /* goto the next postion for the next index attribute */
            }
            *p = '\0';
            sprintf(indexstr, "%s;%ld", indexstr, offset);
            lprintf ("Index String: '%s'", indexstr);
/* why did I do a find first ???? */
            /*bt_driver ('f', indexstr);*/ /* add to index */
            bt_driver ('d', indexstr); /* add to index */
            bt_driver ('q', "");    /* close index */
         }

         for (c=1; c<rec.nseg; c++) {
            lprintf ("Reading the Rest if the Segments");
            sv_offset = rec.next;
            if (fseek (fp, sv_offset, SEEK_SET)) {
               lprintf ("fseek() - %s", strerror (errno));
               bg_fclose (fp);
               return ERROR;
            }
            if (fread (&rec, sizeof (struct record_seg), 1, fp) != 1) {
               lprintf ("fread() - %s", strerror (errno));
               bg_fclose (fp);
               return ERROR;
            }

            lprintf ("Flagging offset %ld as deleted", sv_offset);
            rec.stat = 'd';
            fseek (fp, sv_offset, SEEK_SET);
            fwrite (&rec, sizeof (struct record_seg), 1, fp);
         }
      }

   }

   lprintf ("Initializing WHERE clause variable values");
   for (w=where; w!=NULL; w=w->next) 

      if (w->value!=NULL) {
         myfree (w->value);
         w->value=NULL;
      }

   bg_fclose (fp);

   /* return the offset of this record */
   return offset;
}

/* 
 *
I would like to propose that we do what most databases and 
AIX does with JFS: we use a Log to maintain integrity.
we will need to add a transaction id to help correlate log
and datastore.
struct timeval (tv_sec,tv_usec) -- gettimeofday
unsigned long xid
field type
data
post marker:0xf044dead

 *
 */
long write_record (char *dbname,           /* database name */
                   char *tname,            /* table name */
                   struct bfield *start,   /* data to start write */
                   struct bfield *stop,    /* pointer used to stop write */
                   long recid ,            /* recid is the offset */
          unsigned long flags)             /* turn off commit, etc. */
{
   struct bfield *v;
   long recsize, length, offset;
   char *p;
   FILE *fp,*lfp;
   struct record_seg rec, orec;
   struct idx_rec idx;
   struct timeval logtimestamp;
   unsigned char LogBuffer[1024],*logP=&LogBuffer[8];
   unsigned long Marker=0xf044dead;
   int new;
   struct bfield *backup=stop;
   unsigned long int zero=0L;

   new = (recid == NEW);

   if (start == NULL)
      return 0;


   lprintf ("write_record(%ld)", recid);

   /* calculate the size of the record */
   recsize=0L;
   for (v=start; v!=stop; v=v->next) {
      if (v->type==FTYPE_OID||v->type==FTYPE_INT)
         recsize = recsize + sizeof(long) + sizeof (long);
      else if (v->type==FTYPE_TIME||v->type==FTYPE_DATE||v->type==FTYPE_TIMESTAMP)
         recsize = recsize + sizeof (time_t) + sizeof(struct tm)+BEAGLETIME_;
      else if (v->type==FTYPE_CHAR)
         recsize = recsize + (long) strlen (v->value) + sizeof (long);
      else if (v->type==FTYPE_BLOB) {
      }
   }
   
   /* Add the size of the system fields */
   /* This may need to be removed and have the above loop take care of it */
   recsize += sizeof (long);  /* recid */

   rec.recid = recid;
   rec.stat = 'a';
   rec.nseg = (int) ((recsize - 1L) / DATASEG_SIZE) + 1;

   /* A table lock may be necessary here as I'm actually using three
      writes to write a record.  Or I could build the record into a
      buffer, then write it out in one fell swoop....
   */

   /* allocate the buffer space */
   lprintf ("Allocating data_buffer");
   p = data_buffer = (char *) myrealloc (data_buffer, (size_t) rec.nseg * (size_t) DATASEG_SIZE);
   lprintf ("Done allocating data_buffer");
   if (p == NULL) {
      lprintf ("ERROR: realloc() - Can't Allocate Memory");
      return 0;
   }
   /* init the buffer to zero */
   memset (p, 0, (size_t) rec.nseg * (size_t) DATASEG_SIZE);

   if ((lfp = bg_fopen (dbname, tname, ".log", "a+b")) == NULL) {
      lprintf ("Can't open log");
   } 
   
   if ((flags & 0x1) ==0) {
   if ((fp = bg_fopen (dbname, tname, ".data", "a+b")) == NULL)
      lprintf ("Can't open table");
   else {
      fseek (fp, 0L, SEEK_END);
      lprintf ("Table Opened ftell() returns %ld\n", ftell(fp));
      if (new) recid = ftell(fp);
      offset = recid;

      /* store the recid for this record in the value list (It's always
         the first in the list) 
      */
      *((long *)start->value) = recid;

      /* store data in the buffer space */
      for (v=start; v!=backup; v=v->next) {
       lprintf ("building new record");
         memcpy(logP,&((*v).type),4);
         logP+=4;/*sizeof(v->type);*/
         if (v->type==FTYPE_OID||v->type==FTYPE_INT) {
            length = sizeof (long);             /* OID & INT are long */
            lprintf ("Storing value %ld", *((long *) v->value));
         }
         else if (v->type==FTYPE_CHAR) {
            length = (long) strlen (v->value);
            lprintf ("Storing value %s", (char *) v->value);
         } else if (v->type==FTYPE_TIME) {
            char       timeBuf[32];
            time_t     scratch;
            struct tm *workP=(struct tm*) TIME_ACCESS_TM(v);

            strftime(timeBuf,32,"%H:%M:%S",workP);
            length = (long) sizeof(time_t)+sizeof(struct tm)+BEAGLETIME_; 
            scratch = *(time_t*) TIME_ACCESS_TIME_T(v);
              
            memcpy (workP,localtime(&scratch),sizeof(struct tm));
         } else if (v->type==FTYPE_DATE) {
            char timeBuf[32];
            time_t scratch;
            struct tm *workP=(struct tm*) TIME_ACCESS_TM(v);

            strftime(timeBuf,32,"%x",workP);
            length = (long) sizeof(time_t)+sizeof(struct tm)+BEAGLETIME_; 
            scratch = *(time_t*) TIME_ACCESS_TIME_T(v);
              
            memcpy (workP,localtime(&scratch),sizeof(struct tm));
         } else if (v->type==FTYPE_TIMESTAMP) {
            char timeBuf[32];
            time_t scratch;
            struct tm *workP=(struct tm*) TIME_ACCESS_TM(v);

            strftime(timeBuf,32,"%C",workP);
            length = (long) sizeof(time_t)+sizeof(struct tm)+BEAGLETIME_; 
            scratch = *(time_t*) TIME_ACCESS_TIME_T(v);
              
            memcpy (workP,localtime(&scratch),sizeof(struct tm));
         }  else if (v->type==FTYPE_BLOB) {
	      }
         else {
             lprintf ("invalid type %d",v->type);
             return 0;
         }
         lprintf ("Storing %ld bytes", length);
         memcpy (p, &length, sizeof (long));
         p += sizeof (long);
         lprintf ("Storing  %ld value bytes", length);
         /*if (v->value==0)
             memcpy (p, &zero, length);  */     /* copy the data to the buffer */
         /*else*/
             memcpy (p, v->value, length);       /* copy the data to the buffer */
         p += length;
         lprintf ("next field at %ld", p);
      }
      memcpy(logP,&Marker,sizeof(Marker));
      logP+= sizeof(Marker);
      gettimeofday(&logtimestamp,NULL);
      memcpy(LogBuffer,&(logtimestamp.tv_sec),sizeof(unsigned long));
      memcpy(LogBuffer+sizeof(unsigned long),
               &(logtimestamp.tv_usec),sizeof(unsigned long));
      if (fwrite(LogBuffer,1,logP-LogBuffer,lfp)==0 && ferror(lfp))
	{
            lprintf ("writing integrity log error: %s",strerror(ferror(lfp)));
        }
      fflush(lfp);

      lprintf ("WRITE: record contains %d data segments", rec.nseg);

      for (rec.segment=0; rec.segment<rec.nseg; rec.segment++) {
         if (!new) {
            lprintf ("Seeking to existing Record");
            fseek (fp, offset, SEEK_SET);
            lprintf ("Reading Old Record Info");
            fread (&orec, sizeof (struct record_seg), 1, fp);
            lprintf ("Next record is located at offset %ld", orec.next); 
            rec.next = orec.next;
            if (rec.segment+1 >= orec.nseg) { /* Record has gotten larger */
               lprintf ("Seeking to the end of the file");
               fseek (fp, 0L, SEEK_END);     /* go to the end of the file */
               rec.next = ftell (fp); /* store the offset as the next seg */
               new = NEW;   /* all additional segments are treated as new */
            }
            fseek (fp, offset, SEEK_SET);
         }
         else {
            if (rec.segment==0) rec.recid = ftell (fp);
            idx.recid = rec.recid;
            idx.stat = rec.stat;
            rec.next = ftell (fp) + sizeof (struct record_seg);
            lprintf ("New Record Next Offset is %ld", rec.next);
         }
         lprintf ("Copying %ld bytes into rec.data", DATASEG_SIZE);
         memcpy (rec.data, data_buffer + (rec.segment * DATASEG_SIZE), DATASEG_SIZE);
         lprintf ("Writing Record at %ld", ftell(fp));
         for (v=start; v!=backup; v=v->next) {
            if (v->type==FTYPE_OID||v->type==FTYPE_INT) {
               if (v->value) lprintf ("Value = %ld", *((long *) v->value));
            }
            else if (v->type==FTYPE_CHAR)
               lprintf ("Value = %s", (char *) v->value);
            else if (v->type==FTYPE_TIME) {
               char timeBuf[32];
               struct tm      *workP=(struct tm*)TIME_ACCESS_TM(v);
               strftime(timeBuf,32,"%H:%M:%S",workP);
               lprintf ("Value = %s", (char *) timeBuf);
            } else if (v->type==FTYPE_DATE) {
               char            timeBuf[32];
               struct tm      *workP=(struct tm*)TIME_ACCESS_TM(v);
               strftime(timeBuf,32,"%x",workP);
               lprintf ("Value = %s,%d", (char *) timeBuf,workP->tm_year);
            } else if (v->type==FTYPE_TIMESTAMP) {
               char timeBuf[32];
               struct tm *workP=(struct tm*)TIME_ACCESS_TM(v);
               strftime(timeBuf,32,"%C",workP);
               lprintf ("Value = %s", (char *) timeBuf);
            }
            else if (v->type==FTYPE_BLOB) {
            }
            else{
               lprintf ("Unsupported type %d", v->type);

             }
         }
         lprintf ("   recidi  %ld", rec.recid);
         lprintf ("   stat    %c",  rec.stat);
         lprintf ("   segment %d",  rec.segment);
         lprintf ("   nseg    %d",  rec.nseg);
         lprintf ("   next    %ld", rec.next);
         fwrite (&rec, sizeof (struct record_seg), 1, fp);
      }
      {
      int cc;
      fpos_t  logmarker;
      cc = fgetpos(lfp,&logmarker);
      if (cc)
         lprintf ("fgetpos for integrity log returned %d",errno);
      if (logmarker) {
        logmarker -= 4;
        cc = fsetpos(lfp,&logmarker);
          if (cc)
             lprintf ("fsetpos for integrity log returned %d",errno);
      }
      }
      bg_fclose(lfp);
      bg_fclose (fp);

      if (new) {
         if ((fp = bg_fopen (dbname, tname, ".seq", "ab")) == NULL)
            lprintf ("Can't open sequential file");
         else {
            fseek (fp, 0L, SEEK_END);
            lprintf ("Writing Sequential Record");
            lprintf ("   recid  %ld", idx.recid);
            lprintf ("   stat   %c",  idx.stat);
            fwrite (&idx, sizeof (struct idx_rec), 1, fp);
            bg_fclose (fp);
         }
      }

   }

   return recid; 
   }
}

int delete_record (char *dbname, char *tname, long offset)
{
   FILE *fp,*lfp;
   struct timeval logtimestamp;
   unsigned char LogBuffer[1024],*logP=&LogBuffer[8];
   struct record_seg rec;
   unsigned long Marker=0xb001f00b;
   /* open the file */
   if ((fp = bg_fopen (dbname, tname, ".data", "r+b")) == NULL) {
      lprintf ("Can't Open Table Data File");
      return 0;
   }
   if ((lfp = bg_fopen (dbname, tname, ".log", "r+b")) == NULL) {
      lprintf ("Can't Open Table Integrity Log File");
      return 0;
   } 
   /* position to the front of the record */
   fseek (fp, offset, SEEK_SET);

   /* read file header information */
   fread (&rec, sizeof (struct record_seg), 1, fp);

   /* re-position to the front of the record */
   fseek (fp, offset, SEEK_SET);

   /* mark as deleted */
   rec.stat = 'd';

   *logP='d';
   memcpy(logP+1,&Marker,sizeof(Marker));
   logP+= sizeof(Marker)+1;
   gettimeofday(&logtimestamp,NULL);
   memcpy(LogBuffer,&(logtimestamp.tv_sec),sizeof(unsigned long));
   memcpy(LogBuffer+sizeof(unsigned long),
             &(logtimestamp.tv_usec),sizeof(unsigned long));

   if (fwrite(LogBuffer,1,logP-LogBuffer,lfp)==0 && ferror(lfp))
     {
            lprintf ("writing integrity log error: %s",strerror(ferror(lfp)));
     }
    fflush(lfp);
   /* write new header */
   fwrite (&rec, sizeof (struct record_seg), 1, fp);

   {
      int cc;
      fpos_t  logmarker;
      cc = fgetpos(lfp,&logmarker);
      if (cc)
         lprintf ("delete rec:fgetpos :integrity log returned %d",errno);
      if (logmarker) {
        logmarker -= 4;
        cc = fsetpos(lfp,&logmarker);
          if (cc)
             lprintf ("delete rec:fsetpos: integrity log returned %d",errno);
      }
   }


   bg_fclose (lfp);
   bg_fclose (fp);

   return 1;
}


void delete_table_files (struct btable *tptr)
{
   char path[256];
   struct bindex *iptr=NULL;
   char request [256];
   struct bresult sr = {0,0L,0L,"",NULL,NULL,NULL,NULL,NULL,NULL,NULL};

   /* Initialize search_result structure */
   sr_initresult(&sr);

   /* delete table name from sys_table */
   sprintf (request, "sys_table where sys_table_dbname = '%s' and sys_table_name = '%s' ", getCurrentDB(), tptr->name);
   int_SQLdelete (request, &sr);

   /* Initialize search_result structure */
   sr_initresult(&sr);

   /* delete indexes for this table name from sys_index */
   sprintf (request, "sys_index where sys_index_dbname = '%s' and sys_index_tname = '%s' ", getCurrentDB(), tptr->name);
   int_SQLdelete (request, &sr);

   /* Initialize search_result structure */
   sr_initresult(&sr);

   /* delete fields for this table name from sys_index */
   sprintf (request, "sys_field where sys_field_dbname = '%s' and sys_field_tname = '%s' ", getCurrentDB(), tptr->name);
   int_SQLdelete (request, &sr);

   sprintf (path, "%s/%s/%s", DBROOT, getCurrentDB(), tptr->name);
   lprintf ("Deleted File Path '%s'", path);
   unlink ((const char *)path);

   /* delete data (if there) */
   sprintf (path, "%s/%s/%s.data", DBROOT, getCurrentDB(), tptr->name);
   lprintf ("Deleted File Path '%s'", path);
   unlink ((const char *)path);

   /* delete seq index (if there) */
   sprintf (path, "%s/%s/%s.seq", DBROOT, getCurrentDB(), tptr->name);
   lprintf ("Deleted File Path '%s'", path);
   unlink ((const char *)path);

   /* delete any additional indexes (if there) */
   for (iptr=tptr->indexes; iptr!=NULL; iptr=iptr->next) {

      sprintf (path, "%s/%s/%s", DBROOT, getCurrentDB(), iptr->iname);
      lprintf ("Deleted File Path '%s'", path);
      unlink ((const char *)path);
      sprintf (path, "%s/%s/%s.ndx", DBROOT, getCurrentDB(), iptr->iname);
      lprintf ("Deleted File Path '%s'", path);
      unlink ((const char *)path);
      sprintf (path, "%s/%s/%s.dat", DBROOT, getCurrentDB(), iptr->iname);
      lprintf ("Deleted File Path '%s'", path);
      unlink ((const char *)path);
      sprintf (path, "%s/%s/%s.log", DBROOT, getCurrentDB(), iptr->iname);
      lprintf ("Deleted File Path '%s'", path);
      unlink ((const char *)path);
   }
}


void clean_filesys()
{
   lprintf ("Freeing data_buffer");
   if (data_buffer != NULL) myfree (data_buffer);
}



long update_record (struct btable *tptr,    /* pointer to the current table */
                  long offset,            /* position of record */
                  struct clist *where,     /* where clause */
                  struct clist *UpdateP,     /*alterations to make clause */
                  int *record_match
                  )
{
   char *p, *q, *r, temp[512], indexstr[512];
   int err=NO, c;
   long attrlen, sv_offset;
   FILE *fp;
   struct record_seg rec;
   struct bfield *fptr=NULL, *fptr2=NULL,*fptr2_i;
   struct bfield *vptr=NULL;
   struct bindex *iptr=NULL;
   struct clist *w=NULL;
   extern int    getdate_err;

   lprintf ("update_record() called ");

   if (tptr == NULL)
      return ERROR;

   /* open the file */
   if ((fp = bg_fopen (getCurrentDB(), tptr->name, ".data", "r+b")) == NULL) {
      lprintf ("Can't Open Table Data File");
      return ERROR;
   }

   lprintf ("Seeking to %ld", offset);

   /* position to the front of the record */
   if (fseek (fp, offset, SEEK_SET)) {
      lprintf ("fseek() - %s", strerror (errno));
      bg_fclose (fp);
      return ERROR;
   }

   /* read file header information */
   if (fread (&rec, sizeof (struct record_seg), 1, fp) != 1) {
      lprintf ("fread() - %s", strerror (errno));
      bg_fclose (fp);
      return ERROR;
   }

   /* record is flagged as deleted, ignore and return */   
   if (rec.stat == 'd') {
      lprintf ("deleted record, ignore");
      *record_match=NO;
      bg_fclose (fp);
      return offset;
   }


   /* allocate a large enough buffer to store all the data for the record */
   q = data_buffer = (char *) myrealloc (data_buffer, (size_t) DATASEG_SIZE * rec.nseg);
   if (q == NULL) {
      lprintf ("ERROR: realloc() - Can't Allocate Memory");
      bg_fclose (fp);
      return ERROR;
   }

   memcpy (q, rec.data, DATASEG_SIZE);
   q += DATASEG_SIZE;

   lprintf ("rec.stat = %c", rec.stat);
   lprintf ("rec.recid = %ld", rec.recid);
   lprintf ("rec.next = %ld", rec.next);
   lprintf ("rec.segment = %d", rec.segment);
   lprintf ("rec.nseg = %d", rec.nseg);

   /* if there is more than one data segment for the record then read in the
      rest of the data into the data buffer
   */ 
   for (c=1; c<rec.nseg; c++) {
      lprintf ("Reading the Rest if the Segments");
      if (fseek (fp, rec.next, SEEK_SET)) {
         lprintf ("fseek() - %s", strerror (errno));
         bg_fclose (fp);
         return ERROR;
      }
      if (fread (&rec, sizeof (struct record_seg), 1, fp) != 1) {
         lprintf ("fread() - %s", strerror (errno));
         bg_fclose (fp);
         return ERROR;
      }
      memcpy (q, rec.data, DATASEG_SIZE);
      q += DATASEG_SIZE;
      lprintf ("rec.stat = %c", rec.stat);
      lprintf ("rec.recid = %ld", rec.recid);
      lprintf ("rec.next = %ld", rec.next);
      lprintf ("rec.segment = %d", rec.segment);
   }


   q = data_buffer;
   fptr2=(struct bfield *)mymalloc(fptr2,sizeof (struct bfield));
   memcpy (fptr2,tptr->fields,sizeof (struct bfield));

   for (fptr = tptr->fields, fptr2_i = fptr2;
          fptr != NULL && !err;
              fptr=fptr->next, fptr2_i=fptr2_i->next) {
      
      memcpy (&attrlen, q, sizeof (long));
      q += sizeof (long);

      if (fptr->type==FTYPE_OID||fptr->type==FTYPE_INT) {
         if (fptr->value==NULL) {  /* no need to realloc longs */
            lprintf ("allocating %ld bytes of memory", sizeof(long));
            fptr->value = (long *) mymalloc ( fptr->value, sizeof(long));
            fptr2_i->value = (long *) mymalloc ( fptr2_i->value, sizeof(long));
         }
      }
      else if (fptr->type==FTYPE_CHAR) {
         lprintf ("allocating %ld bytes of memory", attrlen + 1L);
         fptr->value = (char *) myrealloc ( (char *) fptr->value,
                                            (size_t) (attrlen+1L));
         fptr2_i->value = (char *) myrealloc ( (char *) fptr2_i->value, 
                                            (size_t) (attrlen+1L));
      } else if (fptr->type==FTYPE_TIME ||
                  fptr->type==FTYPE_DATE||fptr->type==FTYPE_TIMESTAMP) 
      {
         fptr->value = 
                      (char *) myrealloc ( (char *) fptr->value, 
                                           (size_t) (sizeof(struct tm)
                                               + sizeof(time_t)))
                                               + BEAGLETIME_;
         fptr2_i->value = (char *) myrealloc ( (char *) fptr2_i->value,
                                               (size_t) (sizeof(struct tm)
                                               +sizeof(time_t)))
                                               +BEAGLETIME_;
      } 
      else if (fptr->type==FTYPE_BLOB) {
         
      }
      else lprintf ("unrecognized type %d found",fptr->value);

      if (fptr->value == NULL) {
         err = syntax_error (MEMORY);
         lprintf ("memory allocation Failed");
      }
      else { 
         memcpy (fptr->value, q, attrlen);

        if (fptr->next!=NULL)
	{
           fptr2_i->next=(struct bfield *)mymalloc(fptr2_i, 
                                                    sizeof (struct bfield));
           memcpy( fptr2_i->next,fptr->next,sizeof(struct bfield));
	 }
         q += attrlen;
         if (fptr->type==FTYPE_CHAR) {
            p = (char *) fptr->value;  /* NULL Terminate character data */
            p[attrlen] = '\0';
         }

         if (fptr->type==FTYPE_OID)
            lprintf ("read OID value %ld", *((long *) fptr->value));
         else if (fptr->type==FTYPE_INT)
            lprintf ("read INTEGER value %ld", *((long *) fptr->value));
         else if (fptr->type == FTYPE_CHAR)
            lprintf ("read CHAR value '%s'", (char *) fptr->value);
         else if (fptr->type == FTYPE_TIME) {
            char timebuf[32] ;
            int  p_i;
            struct tm *workP = localtime((time_t*)TIME_ACCESS_TIME_T(fptr));
            time_t scratch=*(time_t*)TIME_ACCESS_TIME_T(fptr);

            strftime(timebuf,32,"%H:%M:%S",workP);
            lprintf ("read TIME value %s %u",timebuf, scratch);
         }
          else if (fptr->type == FTYPE_DATE) {
            char timebuf[32] ;
            int  p_i;
            struct tm *workP = localtime((time_t*)TIME_ACCESS_TIME_T(fptr));
            time_t scratch = *(time_t*)TIME_ACCESS_TIME_T(fptr);
            strftime(timebuf,32,"%x",workP);
            lprintf ("read DATE value %s %u",timebuf,scratch);
         }else if (fptr->type == FTYPE_TIMESTAMP) {
            char timebuf[32] ;
            int  p_i;
            time_t scratch=*(time_t*)TIME_ACCESS_TIME_T(fptr);
            struct tm *workP=(struct tm*) localtime((time_t*)TIME_ACCESS_TIME_T(fptr));

            strftime(timebuf,32,"%C",workP);
            lprintf ("read TIMESTAMP value %s %u",timebuf,scratch );
         } else if (fptr->type == FTYPE_BLOB) {

         }
         else
            lprintf ("Warning - Unknown field type");

         /* 
            Store values for the variables in the where clause.  These
            variable values will be used by the expression parser to
            determine is this record matches the expression
         */
         for (w=where; w!=NULL; w=w->next) {
/*
            lprintf ("checking token '%s' for field '%s.%s'", 
               w->token, fptr->tname, fptr->fname);
*/

            /* strip THIS table name prefix from field name if there 
            */
            p = w->token;
            sprintf (temp, "%s.", fptr->tname);
            if (!strncmp (w->token, temp, strlen (temp)))
               p += strlen (temp);

            /* check to see if the field name and table name match the
               variable in the field definition
            */
/*
            lprintf ("look for this field %s found in where clause in %s",p,fptr->fname); 
*/
            if (!strcmp (p, fptr->fname) && 
                !strncmp (w->token, fptr->tname, strlen(fptr->tname))) {
               /*lprintf ("   field match found");*/

               w->type = fptr->type;
               if (fptr->type==FTYPE_OID||fptr->type==FTYPE_INT) {
                  if (w->value==NULL) /* no need to realloc longs */
                     w->value = (long *) mymalloc (w->value, sizeof(long));
                  memcpy((void *)w->value ,(void*)fptr->value,sizeof(long));
               } else if (fptr->type==FTYPE_TIME||fptr->type==FTYPE_DATE||fptr->type==FTYPE_TIMESTAMP) {
                   time_t scratch;
                   if (w->value==NULL)
                         w->value = (char *) mymalloc (w->value,16);
                   scratch=*(time_t*)fptr->value;
                   sprintf((char *)w->value ,"%u",scratch);

               }else if (fptr->type==FTYPE_CHAR) {
                  w->value = (char *) myrealloc (w->value,(size_t)(attrlen+1L));
                  memcpy (w->value, fptr->value, attrlen+1L);
               }else if (fptr->type==FTYPE_BLOB) {
               }
               w->type = fptr->type;
            }
         }
      }
   }


   lprintf ("WHERE clause after value subsitution");
   for (w=where; w!=NULL; w=w->next) {
      if (w->value==NULL) {

            struct tm *scratchP;
            struct tm ws;
            int length,error;
            time_t secCount;
            char *CheckP=(char *) &secCount;

            length=strlen(w->token)-1;
            if (*(char*)w->token=='\''  && w->next==NULL) {
                if (where->type==FTYPE_TIME ||
                    where->type==FTYPE_DATE || where->type==FTYPE_TIMESTAMP)
                {
		   *(char*)w->token=' ';
                      *(char*)(w->token+length)=' ';
                      lprintf ("date token %s",(char*)w->token);

                      scratchP = getdate((char*)w->token);
                      if (scratchP==NULL)
                          lprintf ("getdate failed with %d",getdate_err);
                      sprintf(w->token,"%u",secCount=(time_t)mktime(scratchP));
                }
                lprintf ("literal   %s",(char*)w->token);
                w->type=where->type;
	    }
      } else {
         if (w->type==FTYPE_OID||w->type==FTYPE_INT)
            lprintf ("integer   %ld", *((long *) w->value));
         else if (w->type==FTYPE_TIME ) {
            lprintf ("time   %s",(char*)w->value/**(time_t*)w->value*/);
         }
         else if (w->type==FTYPE_DATE ) {
            lprintf ("date   %s",(char*)w->value/**(time_t*)w->value*/);
         }
         else if (w->type==FTYPE_TIMESTAMP ) {
            lprintf ("timestamp   %s",(char*)w->value);
         }
         else if (w->type==FTYPE_BLOB) {

         }
          else /* FTYPE_CHAR */
            lprintf ("string   %s", (char *) w->value);
      }
   }


   /* BOOLEAN_get_exp() executes a call to the boolean expresion parser */

   *record_match=NO;
   if (where == NULL || BOOLEAN_get_exp(where)) {
      int fieldlength,reclength=0,UpdateMarker=0,rebuild=0,fldoffset=0;
      *record_match=YES;

      /* do the update and re-write the record
         variables for positioned write: fieldlength,fldoffset
         variables for rebuild write: reclength, rec.nseg
        if updated field is a string that has grown, regenerate
        else do a positioned write .
      */
#define default  rec.nseg * DATASEG_SIZE

      fseek(fp,fptr->recid,SEEK_SET);
      for (fptr2_i=tptr->fields; fptr2_i!=NULL; fptr2_i=fptr2_i->next) {
         if (0==(UpdateMarker=strcmp(fptr2_i->fname,UpdateP->token)))
         {
             if (fptr2_i->type==FTYPE_CHAR)
	     {
                 int dataLincrease;
                 fieldlength=strlen(UpdateP->next->next->value);
                 if ( (dataLincrease = fieldlength -
                                       strlen(fptr2_i->value))>0 )
	         {
                     if ((dataLincrease+(q-data_buffer))> default)
		     {
                         rec.nseg++;
                         rec.nseg+=dataLincrease/DATASEG_SIZE;
                         rebuild=1;
		     }
                     reclength=(default)+dataLincrease;
                 } 
                 break;
             }
             else if (fptr2_i->type==FTYPE_INT)
             {
                long int updateval;
                fptr2_i->value=(long int *)mymalloc(fptr2_i->value,sizeof(long int));
                updateval=ARITHMETIC_get_exp(UpdateP->next);
                memcpy(fptr2_i->value,&updateval,sizeof(long int ));
                fieldlength=sizeof(unsigned long);
                reclength=default;
                break;
             }
             else if (fptr->type==FTYPE_DATE || fptr->type==FTYPE_TIME || 
                   fptr->type == FTYPE_TIMESTAMP)
                 fieldlength=sizeof(struct tm) + sizeof(time_t) + BEAGLETIME_;
                 break;
         }
         else 
         { 
             if (fptr2_i->type==FTYPE_INT) 
                 fldoffset += sizeof(long);
             if (fptr2_i->type==FTYPE_CHAR)
                 fldoffset += strlen(fptr2_i->value)+1;
             else if (fptr2_i->type==FTYPE_DATE || 
                      fptr2_i->type==FTYPE_TIME || 
                      fptr2_i->type == FTYPE_TIMESTAMP)
                 fldoffset += sizeof(struct tm) + sizeof(time_t) + BEAGLETIME_;
	 }
      }
      /* end of check for lengthened record */

      if (rebuild==0)
      {
          fseek(fp,fptr->recid+offset,SEEK_SET);
          fwrite(fptr2_i->value,fieldlength,1,fp);
          goto updatedone;
      }
      else fseek(fp,fptr->recid+fldoffset,SEEK_SET);

      /* here we rebuild a record */
      fldoffset=0;
      data_buffer= mymalloc(data_buffer,reclength);
      for (fptr2_i=tptr->fields; fptr2_i!=NULL; fptr2_i=fptr2_i->next)
      {
         if (fptr2_i->type==FTYPE_CHAR)
	 {
 
             memcpy(data_buffer+fldoffset,fptr2_i->value,strlen(fptr2_i->value)+1);
             fldoffset += strlen(fptr2_i->value)+1;
         }    
         else if (fptr->type==FTYPE_INT)
	 {
             long int updateval;
             updateval =ARITHMETIC_get_exp(UpdateP->next);
             memcpy(data_buffer+fldoffset,&updateval,
                    sizeof(unsigned long));
             fldoffset += sizeof(unsigned long);
         }
         else if (fptr->type==FTYPE_DATE || fptr->type==FTYPE_TIME || 
                   fptr->type == FTYPE_TIMESTAMP)
	 {
             time_t scratch;
             struct tm *workP;
             char   timeBuf[32];

             strftime(timeBuf,32,"%x",workP);

             memcpy( data_buffer+fldoffset,
                     UpdateP->next->next->value,
                     sizeof(struct tm) + sizeof(time_t) + BEAGLETIME_);
             fldoffset +=sizeof(struct tm) + sizeof(time_t) + BEAGLETIME_;
	 }

      }
      fwrite(data_buffer,fldoffset,1,fp);

   }
  updatedone:
   lprintf ("Initializing WHERE clause variable values");
   for (w=where; w!=NULL; w=w->next) 

      if (w->value!=NULL) {
         myfree (w->value);
         w->value=NULL;
      }

   bg_fclose (fp);

   /* return the offset of this record */
   return offset;
}
