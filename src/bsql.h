#ifdef __cplusplus
extern "C" {
#endif
/*
 
 bsql.h
     
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
#include "beagle.h"
#include "linklist.h"

extern int BSQLConnect (char *host,char *,magic_t);
extern int BSQLSetCurrentDB (int socket, char *dbname);
extern char *BSQLGetCurrentDB (int socket);
extern void BSQLDisconnect (int socket);
extern struct bresult *BSQLQueryDB (int socket, char *query);
extern long BSQLntuples (struct bresult *res);
extern long BSQLnfields (struct bresult *res);
extern char *BSQLFieldValue (struct bresult *res, long row, long col);
extern char *BSQLFieldName (struct bresult *res, long col);
extern int BSQLFieldType (struct bresult *res, long col);
extern char *BSQLresult (struct bresult *res);
extern void BSQLFreeResult (struct bresult *p);
extern int BSQLSetPassword (int socket,int version,char **);

extern char *BSQLservice;
#ifdef __cplusplus
 }
#endif
