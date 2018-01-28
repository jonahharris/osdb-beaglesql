/*
 
 linklist.h
     
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

 /* add table onto list */
extern struct btable *store_table_list (struct btable *p, struct btable *last);

/* add field onto list */
extern struct bfield *store_field_list (struct bfield *p, struct bfield *last); 

/* add index onto list */
extern void store_index_list (struct bindex *p);

extern struct bfield *copy_field_list (struct bfield *p);
extern struct btable *table_node (char *name);
extern struct bfield *field_node (char *fname, char *tname, void *value, int type, long recid);
extern struct bindex *index_node (char *iname, char *tname);
extern void free_table (struct btable *p);        /* free table list */
extern void free_field (struct bfield *p);        /* free field list */
extern void free_index (struct bindex *p);        /* free index list */

/* the following also defined in linklist.c */
#define LL_NA      0
#define LL_SAVE    1
#define LL_RESTORE 2

