#include "config.h"
/*
 
 beagle.h     

 Copyright (c) 1996,1997 Robert Klein

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
#ifndef BEAGLEH
#define BEAGLEH
#include "messages.h"
#include "berror.h"
#include "connectTCP.h"
#include "passiveTCP.h"

#define GETPASSWD     char passwd[16],hostname[16],__UkLp[96],__5Z[16],*__8Zp;\
                      extern char *getCurrentDB();    \
                      struct bresult __sr,__sr2;\
  __sr.values=NULL;__sr.fields=NULL; sr_initresult(&__sr);\
  if (getCurrentDB()==NULL || strlen(getCurrentDB())==0) {\
      setCurrentDB("test");           \
      }\
 int_SQLselect("* from sys_user where sys_user_user = 'beagle' ",&__sr);\
 gethostname(hostname,16);                \
 sprintf(__UkLp,"sys_user values ( 'beagle','%s','test',62879458,'BeagLe8') ",hostname); \
 if (__sr.ntuples==0) int_SQLinsert(__UkLp);  \
  __sr2.values=NULL;__sr2.fields=NULL; sr_initresult(&__sr2);\
 sprintf(__UkLp,"* from sys_user where sys_user_user = '%s' ",getlogin()); \
 lprintf ("now search for %s",__UkLp); \
 int_SQLselect(__UkLp,&__sr2);\
 if (__sr2.ntuples) {   \
    __8Zp = sr_getfieldbyname(&__sr2,0,"sys_user_passwd"); \
    strcpy(__5Z,__8Zp); \
   strncpy(passwd,&__5Z[1],strlen(__5Z)-2);  \
   passwd[strlen(__5Z)-1]='\0';   \
   lprintf ("this user passwd is %s",passwd); \
  setCurrentDB(NULL); \
      }


typedef unsigned long int magic_t;
#define MAKE_MAGIC 0x34b786e4;

#define SERVICE "beagle"     /* the port that client will use to talk to the
                              server.  Needs to be setup in /etc/services */
#define MAX_HOST_NAME_LEN 64
#define MAX_USER_NAME_LEN 64

#define CREATE_TABLE 0
#define DROP_TABLE   1
#define INSERT_INTO  2
#define SELECT       3
#define CREATE_INDEX 4
#define DROP_INDEX   5
#define DELETE       6
#define UPDATE       7

#define NUMCMDS 8

/* Action codes for record reads */
#define NONE          0
#define DELETE_RECORD 1
#define UPDATE_RECORD 2

/* Field Types */
#define FTYPE_CHAR 0
#define FTYPE_INT  1
#define FTYPE_FLOAT 2
#define FTYPE_BLOB  3 
#define FTYPE_TIME  4 
#define FTYPE_DATE  5 
#define FTYPE_TIMESTAMP 6
#define FTYPE_OID 9990

#define DBROOT getenv("BG_DATA")
typedef unsigned long LONG;
typedef unsigned short BOOLEAN;
/* types of searches available for select statements */
#define SEQ 0
#define BTREE 1


/* Field Information */
struct bfield {
   char fname[MAXIDSIZE]; /* name of the field */
   char tname[MAXIDSIZE]; /* name of the table for this field */
   void *value;           /* value stored for the field (directly correlates
                             to the fields stored in the bfield structure for
                             any given query */
   int type;              /* field type.  used to determine how the data
                             should be treated */
   long recid;            /* record Id of the tuple this field belongs to */
   struct bfield *next;   /* pointer to the next field in the list */
                          /* a link list is used here because for any given
                             table you never know what the next field will
                             be. For example: "SELECT field1, field3 FROM
                             sometable"  would only select fields 1 & 3 from
                             the table where "SELECT * FROM sometable" would
                             select all fields in the table.  Also, the
                             SELECT statement could be constructed in such
                             a way as to return the fields in the table in
                             a different order then they are acctually 
                             stored. */
};

#define INDEX_TOKEN_LEN 15   /* max length of each attribute in an index */

struct bindex {
   char iname[MAXIDSIZE]; /* name of the index */
   char tname[MAXIDSIZE]; /* name of the table */
   struct bfield *fields,   /* root pointer to a link-list of fields */
                 *f_last,
                 *f;        /* pointer used to traverse the list */
   struct bindex *next;     /* pointer to the next bindex structure */
};


/* Query Result */
struct bresult {
   int resultcode;          /* unique identifier that allows the client 
                               program to execute multiple SELECT statements
                               and reference them by the 'resultcode' */
   long ntuples,            /* Number of records returned */
        nfields;            /* Number of fields returned */
   char errcode[MAX_ERROR_LENGTH]; /* message returned by the server upon completion
                               of the request */
   struct bfield *fields,   /* root pointer to a link-list of fields */
                 *f_last,
                 *f;        /* pointer used to traverse the list */
   struct bfield *values,   /* root pointer to a link-list of values */
                 *v_last,
                 *v;        /* pointer used to traverse the list */
   struct bresult *next;    /* pointer to the next result structure */
};

/* Table */
struct btable {
   char name[MAXIDSIZE]; /* name of the table */
   char iname[MAXIDSIZE]; /* name of the index */
   char ro;               /* 'y' or 'n' */
   long nfields;
   int search_type;         /* type of search to be done on this table */
   struct bfield *fields,   /* root pointer to a link-list of fields */
                 *f_last,
                 *f;        /* pointer used to traverse the list */
   struct bfield *values,   /* root pointer to a link-list of fields */
                 *v_last,
                 *v;        /* pointer used to traverse the list */
   struct bindex *indexes,  /* root pointer to a link-list of indexes */
                 *i;        /* pointer used to traverse the list */
   struct btable *next;     /* pointer to a link-list of tables */
   struct btable *last;     /* pointer to the last table in the list */
};


/* Database */
struct bdb {
   char *name;
   struct btable *tables,   /* root pointer to a link-list of tables */
                 *t;        /* pointer used to traverse the list */
   struct bdb    *next;
};

#if ( PORT_DECUNIX32|PORT_SOLARIS|PORT_AIX|PORT_LINUX|PORT_HPUX|HAVE_STRERROR )
#define STRERROR   strerror(errno)
#else
#define STRERROR   sys_errlist[errno]
#endif

#define BEAGLETIME_ 0
#define TIME_ACCESS_TM(w) w->value+sizeof(time_t)
#define TIME_ACCESS_TIME_T(w) w->value
#define DATASEG_SIZE 256L
#define NEW -1L

struct idx_rec {
   long recid;     /* unique record Id */
   char stat;      /* record status */
   long left;      /* offset of left branch children */
   long right;     /* offset of right branch children */
};

struct record_seg {
   long recid;     /* unique record Id */
   char stat;      /* record status */
   int  segment;   /* segment number for this record. 0 = head */
   int  nseg;      /* number of segments */
   long next;      /* offset of the next segment */
   char data[DATASEG_SIZE]; /* data buffer for this segment */
};
#endif
