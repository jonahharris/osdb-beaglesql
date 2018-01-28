/*
 
 filesys.h
     
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

extern struct btable *gettableinfo (char *path);  
extern int puttableinfo (struct btable *tptr);
extern int putindexinfo (struct bindex *iptr);
extern int appendindexinfo (struct bindex *iptr);
extern FILE *bg_fopen (char *db, char *name, char *ext, char *flags);
extern void bg_fclose (FILE *fp);
extern long read_first (FILE *fp, struct btable *tptr, struct clist *where, int action,int *);
extern long read_next (FILE *fp, struct btable *tptr, struct clist *where, int action,int *);
extern long read_record (struct btable *tptr, long offset, struct clist *where, int action, int *record_match);
extern long write_record (char *dbname, char *tname, struct bfield *start, struct bfield *stop, long recid, unsigned long flags);
extern int delete_record (char *dbname, char *tname, long offset);
extern void delete_table_files (struct btable *tptr);
extern void clean_filesys (void);

/*extern int read_match;  Set if the last read_record() matched the Where clause */
