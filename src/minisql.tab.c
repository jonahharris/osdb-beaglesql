static const char  rcsfile []= "$Header: /home/magrasjc/test/src/RCS/minisql.tab.c,v 0.87.2.1 2000/02/05 06:13:32 magrasjc Exp $";

/*  A Bison parser, made from minisql.y
 by  GNU Bison version 1.25
  */

#define YYBISON 1  /* Identify Bison output.  */

#define	NAME	258
#define	STRING	259
#define	INTNUM	260
#define	APPROXNUM	261
#define	OR	262
#define	AND	263
#define	NOT	264
#define	COMPARISON	265
#define	UMINUS	266
#define	ADA	267
#define	ALL	268
#define	AVG	269
#define	AMMSC	270
#define	MIN	271
#define	MAX	272
#define	SUM	273
#define	COUNT	274
#define	ANY	275
#define	AS	276
#define	ASC	277
#define	AUTHORIZATION	278
#define	BETWEEN	279
#define	BY	280
#define	C	281
#define	CHARACTER	282
#define	CHECK	283
#define	CLOSE	284
#define	COBOL	285
#define	COMMIT	286
#define	CONTINUE	287
#define	CREATE	288
#define	CURRENT	289
#define	CURSOR	290
#define	DECIMAL	291
#define	DECLARE	292
#define	DEFAULT	293
#define	DELETE	294
#define	DESC	295
#define	DISTINCT	296
#define	DOUBLE	297
#define	DROP	298
#define	ESCAPE	299
#define	EXISTS	300
#define	FETCH	301
#define	FLOAT	302
#define	FOR	303
#define	FOREIGN	304
#define	FORTRAN	305
#define	FOUND	306
#define	FROM	307
#define	GOTO	308
#define	GRANT	309
#define	GROUP	310
#define	HAVING	311
#define	INDEX	312
#define	INDICATOR	313
#define	INSERT	314
#define	INTEGER	315
#define	INTO	316
#define	IS	317
#define	KEY	318
#define	LANGUAGE	319
#define	LIKE	320
#define	MODULE	321
#define	NULLX	322
#define	NUMERIC	323
#define	OF	324
#define	ON	325
#define	OPEN	326
#define	OPTION	327
#define	ORDER	328
#define	PARAMETER	329
#define	PASCAL	330
#define	PLI	331
#define	PRECISION	332
#define	PRIMARY	333
#define	PRIVILEGES	334
#define	PROCEDURE	335
#define	PUBLIC	336
#define	REAL	337
#define	REFERENCES	338
#define	ROLLBACK	339
#define	SCHEMA	340
#define	SELECT	341
#define	SET	342
#define	SMALLINT	343
#define	SOME	344
#define	SQLCODE	345
#define	SQLERROR	346
#define	TABLE	347
#define	TO	348
#define	UNION	349
#define	UNIQUE	350
#define	UPDATE	351
#define	USER	352
#define	USING	353
#define	VALUES	354
#define	VIEW	355
#define	WHENEVER	356
#define	WHERE	357
#define	WITH	358
#define	WORK	359
#define	VARYING	360
#define	VARCHAR	361
#define	NATIONAL	362
#define	CHAR	363
#define	NCHAR	364
#define	BIT	365

#line 1 "minisql.y"

#include <string.h>
enum BSQLValues {eUSER,eCHARTYPE,eNUMERIC,eDECIMAL,eINTEGER,eSMALLINT,eFLOAT,eREAL,eDOUBLEPREC,eBOOLEAN,eNULL,eCOLUMN,eTABLE,eFUNCTION,ePARAMATER,eRANGE,eBETWEEN,eLIKE,eNLIKE,eCURSOR,eNULLTEST,eNNULLTEST,eESCAPE,eGROUP,eDEFAULT=512,ePRIMARY=1024,eUNIQUE=2048,eSECURITY=8192};

enum ops { opDISTINCT,opANY,opSOME,opALL,opOPEN=1,opCOMMIT=2,opROLLBACK=3,opSELECT=1,opDELETE=2,opINSERT=4,opUPDATE=8,opDivide,opMultiply,opAdd,opSubtract,opOR,opAND,opNOT };

#define mymalloc(a) malloc(a)

 struct SQLvalue {
  struct {
  int intval;
  double floatval;
  char *strval;
  int dimensions[3];
  } value;
  int subtok;
  struct SQLvalue *nextP,*leftP,*rightP;
 
 };

#define YYDEBUG 1
#define YYERROR_VERBOSE
#define lprintf printf

#line 26 "minisql.y"
typedef union{
  int intval[3];
  double floatval;
  char *strval;
  struct SQLvalue *nextP;
  char semString[16];
} YYSTYPE;
#include <stdio.h>

#ifndef __cplusplus
#ifndef __STDC__
#define const
#endif
#endif



#define	YYFINAL		386
#define	YYFLAG		-32768
#define	YYNTBASE	121

#define YYTRANSLATE(x) ((unsigned)(x) <= 365 ? yytranslate[x] : 205)

static const char  rcsfile yytranslate[] = {     0,;
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,   116,
   117,    13,    11,   118,    12,   120,    14,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,   115,     2,
   119,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     1,     2,     3,     4,     5,
     6,     7,     8,     9,    10,    15,    16,    17,    18,    19,
    20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
    30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
    40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
    50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
    60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
    70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
    80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
    90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
   100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
   110,   111,   112,   113,   114
};

#if YYDEBUG != 0
static const short yyprhs[] = {     0,
     0,     3,     7,     9,    16,    17,    19,    21,    24,    26,
    28,    35,    37,    41,    43,    47,    48,    51,    54,    58,
    63,    66,    69,    72,    74,    78,    79,    83,    91,    92,
    96,    99,   101,   103,   105,   109,   111,   113,   115,   117,
   119,   123,   125,   127,   129,   135,   137,   139,   141,   143,
   145,   147,   149,   151,   153,   155,   157,   159,   161,   164,
   167,   175,   180,   185,   191,   196,   198,   200,   204,   206,
   208,   211,   214,   220,   228,   229,   231,   233,   242,   243,
   245,   249,   253,   257,   263,   265,   269,   271,   272,   274,
   276,   278,   282,   284,   286,   291,   293,   295,   299,   301,
   304,   307,   308,   312,   314,   318,   319,   322,   326,   330,
   333,   337,   339,   341,   343,   345,   347,   349,   351,   353,
   357,   361,   368,   374,   380,   385,   386,   389,   394,   398,
   405,   411,   418,   424,   426,   430,   435,   437,   439,   441,
   444,   452,   456,   460,   464,   468,   471,   474,   476,   478,
   480,   484,   486,   490,   492,   494,   496,   498,   501,   506,
   512,   518,   523,   525,   527,   529,   531,   535,   541,   543,
   547,   549,   554,   556,   561,   568,   570,   575,   582,   584,
   586,   588,   593,   595,   598,   603,   609,   616,   623,   629,
   635,   640,   645,   651,   653,   655,   657,   659,   661,   663
};

static const short yyrhs[] = {   122,
   115,     0,   121,   122,   115,     0,   123,     0,    37,    89,
   200,    27,   203,   124,     0,     0,   125,     0,   126,     0,
   125,   126,     0,   127,     0,   135,     0,    37,    96,   196,
   116,   128,   117,     0,   129,     0,   128,   118,   129,     0,
   130,     0,   198,   197,   131,     0,     0,   131,   132,     0,
     9,    71,     0,     9,    71,    99,     0,     9,    71,    82,
    67,     0,    42,   194,     0,    42,    71,     0,    42,   101,
     0,   198,     0,   133,   118,   198,     0,     0,   116,   133,
   117,     0,    58,   137,    74,   196,    97,   140,   136,     0,
     0,   107,    58,    76,     0,    17,    83,     0,    17,     0,
   138,     0,   139,     0,   138,   118,   139,     0,    90,     0,
    63,     0,    43,     0,    47,     0,   141,     0,   140,   118,
   141,     0,    85,     0,   203,     0,   142,     0,    41,   199,
    39,    52,   165,     0,   143,     0,   144,     0,   156,     0,
   145,     0,   146,     0,   147,     0,   148,     0,   149,     0,
   153,     0,   154,     0,   155,     0,   158,     0,   161,     0,
    33,   199,     0,    35,   108,     0,    43,    56,   196,   106,
    38,    73,   199,     0,    43,    56,   196,   164,     0,    50,
   199,    65,   162,     0,    63,    65,   196,   134,   150,     0,
   103,   116,   151,   117,     0,   155,     0,   152,     0,   151,
   118,   152,     0,   191,     0,    71,     0,    75,   199,     0,
    88,   108,     0,    90,   157,   167,    56,   168,     0,    37,
    61,   204,    74,   196,   102,   134,     0,     0,    17,     0,
    45,     0,   100,   196,    91,   159,   106,    38,    73,   199,
     0,     0,   160,     0,   159,   118,   160,     0,   198,   119,
   189,     0,   198,   119,    71,     0,   100,   196,    91,   159,
   164,     0,   163,     0,   162,   118,   163,     0,   192,     0,
     0,   172,     0,   166,     0,   155,     0,   116,   165,   117,
     0,   190,     0,    13,     0,   169,   164,   173,   175,     0,
   170,     0,   171,     0,   170,   118,   171,     0,   196,     0,
   196,   202,     0,   106,   176,     0,     0,    59,    29,   174,
     0,   195,     0,   174,   118,   195,     0,     0,    60,   176,
     0,   176,     7,   176,     0,   176,     8,   176,     0,     9,
   176,     0,   116,   176,   117,     0,   177,     0,   178,     0,
   179,     0,   180,     0,   182,     0,   183,     0,   185,     0,
   187,     0,   189,    10,   189,     0,   189,    10,   188,     0,
   189,     9,    28,   189,     8,   189,     0,   189,    28,   189,
     8,   189,     0,   195,     9,    69,   191,   181,     0,   195,
    69,   191,   181,     0,     0,    48,   191,     0,   195,    66,
     9,    71,     0,   195,    66,    71,     0,   189,     9,    65,
   116,   188,   117,     0,   189,    65,   116,   188,   117,     0,
   189,     9,    65,   116,   184,   117,     0,   189,    65,   116,
   184,   117,     0,   191,     0,   184,   118,   191,     0,   189,
    10,   186,   188,     0,    24,     0,    17,     0,    93,     0,
    49,   188,     0,   116,    90,   157,   167,    56,   168,   117,
     0,   189,    11,   189,     0,   189,    12,   189,     0,   189,
    13,   189,     0,   189,    14,   189,     0,    11,   189,     0,
    12,   189,     0,   191,     0,   195,     0,   193,     0,   116,
   189,   117,     0,   189,     0,   190,   118,   189,     0,   192,
     0,   194,     0,   101,     0,   201,     0,   201,   201,     0,
    19,   116,    13,   117,     0,    19,   116,    45,   195,   117,
     0,    19,   116,    17,   189,   117,     0,    19,   116,   189,
   117,     0,     4,     0,     5,     0,     6,     0,     3,     0,
     3,   120,     3,     0,     3,   120,     3,   120,     3,     0,
     3,     0,     3,   120,     3,     0,    31,     0,    31,   116,
     5,   117,     0,    72,     0,    72,   116,     5,   117,     0,
    72,   116,     5,   118,     5,   117,     0,    40,     0,    40,
   116,     5,   117,     0,    40,   116,     5,   118,     5,   117,
     0,    64,     0,    92,     0,    51,     0,    51,   116,     5,
   117,     0,    86,     0,    46,    81,     0,   113,   116,     5,
   117,     0,   113,   109,   116,     5,   117,     0,   111,   112,
   109,   116,     5,   117,     0,   111,    31,   109,   116,     5,
   117,     0,    31,   109,   116,     5,   117,     0,   112,   109,
   116,     5,   117,     0,   110,   116,     5,   117,     0,   114,
   116,     5,   117,     0,   114,   109,   116,     5,   117,     0,
     3,     0,     3,     0,     3,     0,    78,     0,     3,     0,
     3,     0,     3,     0
};

#endif

#if YYDEBUG != 0
static const short yyrline[] = { 0,
   154,   156,   158,   161,   168,   170,   175,   177,   180,   185,
   192,   199,   204,   209,   219,   226,   228,   234,   241,   247,
   253,   265,   270,   294,   299,   309,   311,   317,   325,   327,
   333,   338,   342,   349,   354,   361,   367,   373,   379,   388,
   395,   410,   416,   422,   429,   440,   447,   452,   457,   461,
   465,   469,   473,   477,   481,   485,   489,   493,   500,   509,
   516,   530,   538,   545,   552,   557,   563,   569,   582,   588,
   595,   604,   611,   618,   626,   628,   633,   639,   646,   648,
   654,   670,   680,   690,   697,   704,   721,   729,   731,   737,
   748,   753,   761,   766,   774,   782,   791,   800,   816,   824,
   835,   844,   849,   857,   865,   880,   883,   891,   899,   908,
   916,   922,   930,   935,   939,   943,   947,   951,   955,   961,
   968,   975,   980,   991,  1000,  1010,  1012,  1020,  1028,  1039,
  1044,  1048,  1052,  1058,  1065,  1078,  1088,  1093,  1097,  1103,
  1110,  1117,  1128,  1137,  1146,  1155,  1157,  1158,  1166,  1176,
  1180,  1188,  1194,  1207,  1216,  1223,  1231,  1236,  1243,  1250,
  1257,  1264,  1270,  1278,  1284,  1294,  1304,  1313,  1328,  1339,
  1351,  1362,  1371,  1381,  1390,  1399,  1408,  1417,  1425,  1434,
  1443,  1450,  1459,  1467,  1475,  1483,  1491,  1499,  1507,  1515,
  1523,  1531,  1539,  1551,  1563,  1571,  1580,  1590,  1598,  1604
};
#endif


#if YYDEBUG != 0 || defined (YYERROR_VERBOSE)

static const char  rcsfile * const yytname[] = {   "$","error","$undefined.","NAME","STRING",;
"INTNUM","APPROXNUM","OR","AND","NOT","COMPARISON","'+'","'-'","'*'","'/'","UMINUS",
"ADA","ALL","AVG","AMMSC","MIN","MAX","SUM","COUNT","ANY","AS","ASC","AUTHORIZATION",
"BETWEEN","BY","C","CHARACTER","CHECK","CLOSE","COBOL","COMMIT","CONTINUE","CREATE",
"CURRENT","CURSOR","DECIMAL","DECLARE","DEFAULT","DELETE","DESC","DISTINCT",
"DOUBLE","DROP","ESCAPE","EXISTS","FETCH","FLOAT","FOR","FOREIGN","FORTRAN",
"FOUND","FROM","GOTO","GRANT","GROUP","HAVING","INDEX","INDICATOR","INSERT",
"INTEGER","INTO","IS","KEY","LANGUAGE","LIKE","MODULE","NULLX","NUMERIC","OF",
"ON","OPEN","OPTION","ORDER","PARAMETER","PASCAL","PLI","PRECISION","PRIMARY",
"PRIVILEGES","PROCEDURE","PUBLIC","REAL","REFERENCES","ROLLBACK","SCHEMA","SELECT",
"SET","SMALLINT","SOME","SQLCODE","SQLERROR","TABLE","TO","UNION","UNIQUE","UPDATE",
"USER","USING","VALUES","VIEW","WHENEVER","WHERE","WITH","WORK","VARYING","VARCHAR",
"NATIONAL","CHAR","NCHAR","BIT","';'","'('","')'","','","'='","'.'","sql_list",
"sql","schema","opt_schema_element_list","schema_element_list","schema_element",
"base_table_def","base_table_element_commalist","base_table_element","column_def",
"column_def_opt_list","column_def_opt","column_commalist","opt_column_commalist",
"privilege_def","opt_with_grant_option","privileges","operation_commalist","operation",
"grantee_commalist","grantee","cursor_def","manipulative_statement","close_statement",
"commit_statement","delete_statement_positioned","delete_statement_searched",
"fetch_statement","insert_statement","values_or_query_spec","insert_atom_commalist",
"insert_atom","open_statement","rollback_statement","query_spec","create_idx_statement",
"opt_all_distinct","update_statement_positioned","assignment_commalist","assignment",
"update_statement_searched","target_commalist","target","opt_where_clause","query_exp",
"query_term","selection","table_exp","from_clause","table_ref_commalist","table_ref",
"where_clause","opt_group_by_clause","column_ref_commalist","opt_having_clause",
"search_condition","predicate","comparison_predicate","between_predicate","like_predicate",
"opt_escape","test_for_null","in_predicate","atom_commalist","all_or_any_predicate",
"any_all_some","existance_test","subquery","scalar_exp","scalar_exp_commalist",
"atom","parameter_ref","function_ref","literal","column_ref","table","data_type",
"column","cursor","schema_name","parameter","range_variable","user","index", NULL
};
#endif

static const short yyr1[] = {     0,
   121,   121,   122,   123,   124,   124,   125,   125,   126,   126,
   127,   128,   128,   129,   130,   131,   131,   132,   132,   132,
   132,   132,   132,   133,   133,   134,   134,   135,   136,   136,
   137,   137,   137,   138,   138,   139,   139,   139,   139,   140,
   140,   141,   141,   122,   142,   122,   143,   143,   143,   143,
   143,   143,   143,   143,   143,   143,   143,   143,   144,   145,
   146,   147,   148,   149,   150,   150,   151,   151,   152,   152,
   153,   154,   155,   156,   157,   157,   157,   158,   159,   159,
   159,   160,   160,   161,   162,   162,   163,   164,   164,   165,
   166,   166,   167,   167,   168,   169,   170,   170,   171,   171,
   172,   173,   173,   174,   174,   175,   175,   176,   176,   176,
   176,   176,   177,   177,   177,   177,   177,   177,   177,   178,
   178,   179,   179,   180,   180,   181,   181,   182,   182,   183,
   183,   183,   183,   184,   184,   185,   186,   186,   186,   187,
   188,   189,   189,   189,   189,   189,   189,   189,   189,   189,
   189,   190,   190,   191,   191,   191,   192,   192,   193,   193,
   193,   193,   194,   194,   194,   195,   195,   195,   196,   196,
   197,   197,   197,   197,   197,   197,   197,   197,   197,   197,
   197,   197,   197,   197,   197,   197,   197,   197,   197,   197,
   197,   197,   197,   198,   199,   200,   201,   202,   203,   204
};

static const short yyr2[] = {     0,
     2,     3,     1,     6,     0,     1,     1,     2,     1,     1,
     6,     1,     3,     1,     3,     0,     2,     2,     3,     4,
     2,     2,     2,     1,     3,     0,     3,     7,     0,     3,
     2,     1,     1,     1,     3,     1,     1,     1,     1,     1,
     3,     1,     1,     1,     5,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     1,     2,     2,
     7,     4,     4,     5,     4,     1,     1,     3,     1,     1,
     2,     2,     5,     7,     0,     1,     1,     8,     0,     1,
     3,     3,     3,     5,     1,     3,     1,     0,     1,     1,
     1,     3,     1,     1,     4,     1,     1,     3,     1,     2,
     2,     0,     3,     1,     3,     0,     2,     3,     3,     2,
     3,     1,     1,     1,     1,     1,     1,     1,     1,     3,
     3,     6,     5,     5,     4,     0,     2,     4,     3,     6,
     5,     6,     5,     1,     3,     4,     1,     1,     1,     2,
     7,     3,     3,     3,     3,     2,     2,     1,     1,     1,
     3,     1,     3,     1,     1,     1,     1,     2,     4,     5,
     5,     4,     1,     1,     1,     1,     3,     5,     1,     3,
     1,     4,     1,     4,     6,     1,     4,     6,     1,     1,
     1,     4,     1,     2,     4,     5,     6,     6,     5,     5,
     4,     4,     5,     1,     1,     1,     1,     1,     1,     1
};

static const short yydefact[] = {     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,    75,
     0,     0,     0,     3,    44,    46,    47,    49,    50,    51,
    52,    53,    54,    55,    56,    48,    57,    58,   195,    59,
    60,     0,     0,     0,     0,     0,     0,    71,    72,    76,
    77,     0,   169,     0,     0,     1,   200,     0,   196,     0,
     0,    88,     0,    26,   166,   163,   164,   165,     0,     0,
    94,     0,   197,   156,     0,     0,   152,    93,   148,   154,
   150,   155,   149,   157,     0,    79,     2,     0,     0,     0,
     0,    62,    89,    63,    85,    87,     0,     0,     0,   146,
   147,     0,     0,     0,     0,     0,     0,     0,     0,   158,
   170,   194,    88,    80,     0,     0,   199,     5,     0,    91,
    45,    90,     0,     0,     0,     0,   101,   112,   113,   114,
   115,   116,   117,   118,   119,     0,   149,     0,     0,    24,
     0,    64,    66,   167,     0,     0,     0,     0,   151,    73,
    88,    96,    97,    99,   142,   143,   144,   145,   153,     0,
     0,    84,     0,    26,     0,     0,     4,     6,     7,     9,
    10,     0,   110,     0,     0,   140,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,    86,    27,     0,
     0,     0,   159,     0,     0,   162,     0,   102,     0,   198,
   100,     0,    81,    83,    82,    74,     0,    32,    38,    39,
    37,    36,     0,    33,    34,     8,    92,    61,    75,   111,
   108,   109,     0,     0,   138,   137,   139,     0,     0,   121,
   120,     0,     0,     0,     0,   129,   126,    25,    70,     0,
    67,    69,   168,   161,   160,     0,   106,    98,     0,     0,
    31,     0,     0,     0,     0,     0,   136,     0,     0,     0,
   134,   126,   128,     0,   125,    65,     0,     0,     0,    95,
    78,     0,     0,    35,     0,     0,     0,     0,   123,   133,
     0,   131,   124,   127,    68,   103,   104,   107,     0,    12,
    14,     0,     0,     0,   122,   132,   130,   135,     0,    11,
     0,   171,   176,     0,   181,   179,   173,   183,   180,     0,
     0,     0,     0,     0,    16,    42,    29,    40,    43,     0,
   105,    13,     0,     0,     0,   184,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,    15,     0,     0,    28,
   141,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,    17,     0,    41,     0,
   172,   177,     0,   182,   174,     0,   191,     0,     0,     0,
     0,   185,     0,   192,    18,    22,    23,    21,    30,   189,
     0,     0,     0,     0,   190,   186,   193,     0,    19,   178,
   175,   188,   187,    20,     0,     0
};

static const short yydefgoto[] = {    12,
    13,    14,   157,   158,   159,   160,   279,   280,   281,   327,
   347,   129,    88,   161,   330,   203,   204,   205,   307,   308,
    15,    16,    17,    18,    19,    20,    21,    22,   132,   230,
   231,    23,    24,    25,    26,    42,    27,   103,   104,    28,
    84,    85,    82,   111,   112,    66,   140,   141,   142,   143,
    83,   237,   276,   260,   117,   118,   119,   120,   121,   255,
   122,   123,   249,   124,   219,   125,   166,   126,    68,    69,
    70,    71,    72,    73,   144,   305,   105,    30,    50,    74,
   191,   309,    48
};

static const short yypact[] = {   331,
    20,   -41,    26,    20,   -27,    20,    21,    20,    -2,    96,
   146,   288,     4,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,   156,   158,   128,   146,   119,   146,-32768,-32768,-32768,
-32768,   185,    66,   101,    87,-32768,-32768,   145,-32768,   198,
   178,   132,   172,   142,   151,-32768,-32768,-32768,   261,   261,
-32768,   160,-32768,-32768,   261,   218,   286,   161,-32768,-32768,
-32768,-32768,-32768,   172,   274,   284,-32768,   146,   299,   -62,
    27,-32768,-32768,   167,-32768,-32768,   284,   -56,   308,-32768,
-32768,    79,    31,   146,   261,   261,   261,   261,   261,-32768,
-32768,-32768,    17,-32768,   170,   204,-32768,   114,   -62,-32768,
-32768,-32768,   159,   239,   200,   159,   199,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,   373,    71,   172,    94,-32768,
   201,-32768,-32768,   195,   202,   261,   317,    37,-32768,-32768,
   216,   206,-32768,   323,   208,   208,-32768,-32768,   286,    98,
   284,-32768,   236,   142,   231,   103,-32768,   114,-32768,-32768,
-32768,   215,-32768,    20,   243,-32768,     1,   282,   159,   159,
    60,   212,   261,   220,   271,    10,   125,-32768,-32768,   284,
   264,   341,-32768,    58,   228,-32768,   159,   287,   146,-32768,
-32768,   275,-32768,-32768,   286,-32768,   146,   267,-32768,-32768,
-32768,-32768,   279,   251,-32768,-32768,-32768,-32768,    96,-32768,
   349,-32768,   261,   254,-32768,-32768,-32768,   240,   200,-32768,
   286,   270,    11,   125,   300,-32768,   325,-32768,-32768,   116,
-32768,-32768,-32768,-32768,-32768,   350,   320,-32768,    20,   276,
-32768,   146,    95,   185,   347,    11,-32768,   261,   136,   273,
-32768,   325,-32768,   125,-32768,-32768,   264,   317,   159,-32768,
-32768,   284,   294,-32768,   337,   261,   139,   280,   286,-32768,
   125,-32768,-32768,-32768,-32768,   278,-32768,   199,   144,-32768,
-32768,   303,    15,   146,   286,-32768,-32768,-32768,   317,-32768,
   284,   -43,   289,   319,   291,-32768,   292,-32768,-32768,   293,
   -17,   295,    23,    85,-32768,-32768,    38,-32768,-32768,   281,
-32768,-32768,   296,   397,   398,-32768,   405,   406,   413,   311,
   313,   307,   309,   419,   310,   422,    13,   370,    15,-32768,
-32768,   424,   315,   186,   316,   191,   318,   314,   321,   429,
   431,   322,   435,   324,   371,     7,-32768,   367,-32768,   327,
-32768,-32768,   440,-32768,-32768,   441,-32768,   442,   443,   332,
   333,-32768,   334,-32768,   -47,-32768,-32768,-32768,-32768,-32768,
   335,   336,   338,   339,-32768,-32768,-32768,   387,-32768,-32768,
-32768,-32768,-32768,-32768,   457,-32768
};

static const short yypgoto[] = {-32768,
   446,-32768,-32768,-32768,   301,-32768,-32768,   169,-32768,-32768,
-32768,-32768,   312,-32768,-32768,-32768,-32768,   219,-32768,   134,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
   207,-32768,-32768,   140,-32768,   252,-32768,-32768,   326,-32768,
-32768,   340,   -79,   356,-32768,   223,   187,-32768,-32768,   283,
-32768,-32768,-32768,-32768,  -106,-32768,-32768,-32768,-32768,   217,
-32768,-32768,   224,-32768,-32768,-32768,   -46,   -39,-32768,  -102,
   -12,-32768,   127,   -76,   -10,-32768,   -81,    -4,-32768,   400,
-32768,   396,-32768
};


#define	YYLAST		477


static const short yytable[] = {    34,
    44,    36,    67,    38,   127,   130,   163,   169,   170,   167,
    56,    57,    58,   320,    56,    57,    58,   107,   225,    90,
    91,   345,    29,   152,    52,    93,    54,    10,    35,    55,
    56,    57,    58,    10,   378,   113,   127,    59,    60,   127,
    86,    95,    96,    97,    98,    62,   131,    95,    96,    97,
    98,   379,   138,   109,   346,   145,   146,   147,   148,   149,
   185,   188,   211,   212,   114,   313,    31,   106,    95,    96,
    97,    98,   314,   127,   227,   115,   168,   366,   232,   175,
   226,    55,    56,    57,    58,    37,    32,   213,    63,    59,
    60,   135,   127,   127,   321,   136,   184,    62,   228,   306,
    55,    56,    57,    58,    63,    39,   113,   367,    59,    60,
   127,    64,    40,   195,    33,    86,    62,   210,    46,   198,
   251,   252,   150,   137,   214,   220,   165,    64,    56,    57,
    58,   323,   221,   222,   151,   192,   176,   199,   324,   177,
    41,   200,   116,   251,   328,   199,   115,   139,    43,   200,
   155,   274,   278,   186,   232,   329,    63,   201,    47,   208,
    49,    55,    56,    57,    58,   201,    51,   113,   288,    59,
    60,   156,   247,   245,   234,    63,   250,    62,    93,    64,
   282,   277,   127,    53,   202,    75,   240,    55,    56,    57,
    58,    76,   202,   325,    65,    59,    60,    61,    64,   268,
   326,    77,    63,    62,    67,   169,   170,   115,   269,   282,
   179,   180,   311,   116,    55,    56,    57,    58,    78,   110,
    97,    98,    59,    60,    79,    64,   285,   133,   215,    80,
    62,   263,   256,   257,   261,   216,    63,    81,    55,    56,
    57,    58,    55,    56,    57,    58,    59,    60,   110,    63,
    59,    60,   270,   271,    62,   286,   271,    87,    62,    64,
   290,   291,    63,    55,    56,    57,    58,    56,    57,    58,
    89,    59,    60,    94,   116,    92,   101,   248,    99,    62,
    95,    96,    97,    98,   128,    64,   102,   385,   153,    63,
   171,   172,    95,    96,    97,    98,    95,    96,    97,    98,
    65,   107,   352,   353,   217,   154,   194,   355,   356,   173,
   134,   164,    64,    63,   182,   165,   181,    63,   183,    55,
     1,   187,     2,   189,     3,   190,   197,   218,     4,   209,
     5,   207,   209,   292,   229,   223,    64,     6,    63,   224,
    64,    63,   293,   233,   235,   236,   174,   239,   294,   241,
     7,    65,   242,   295,   266,    65,   170,    95,    96,    97,
    98,    64,     8,     1,    64,     2,   296,     3,   243,   246,
   253,     4,   254,     5,   297,     9,    65,    10,   258,   259,
     6,   171,   172,    95,    96,    97,    98,    11,   298,   272,
   283,   262,   284,     7,   299,   289,   287,   331,   139,   316,
   173,   333,   334,   322,   315,     8,   317,   318,   319,   335,
   336,   332,   300,   301,   302,   303,   304,   337,     9,   338,
    10,   339,   340,   342,   341,   343,   344,   348,   350,   358,
    11,   351,   354,   360,   357,   361,   359,   174,   362,   363,
   364,   365,   369,   370,   371,   372,   373,   374,   375,   376,
   377,   380,   381,   384,   382,   383,   386,    45,   206,   312,
   244,   264,   349,   275,   162,   196,   265,   178,   273,   267,
   310,   238,   368,   100,   108,     0,   193
};

static const short yycheck[] = {     4,
    11,     6,    42,     8,    81,    87,   113,     7,     8,   116,
     4,     5,     6,    31,     4,     5,     6,     3,     9,    59,
    60,     9,     3,   103,    35,    65,    37,    90,    56,     3,
     4,     5,     6,    90,    82,     9,   113,    11,    12,   116,
    53,    11,    12,    13,    14,    19,   103,    11,    12,    13,
    14,    99,    92,   116,    42,    95,    96,    97,    98,    99,
   137,   141,   169,   170,    38,   109,   108,    78,    11,    12,
    13,    14,   116,   150,   177,    49,   116,    71,   181,     9,
    71,     3,     4,     5,     6,    65,    61,    28,    78,    11,
    12,    13,   169,   170,   112,    17,   136,    19,   180,    85,
     3,     4,     5,     6,    78,   108,     9,   101,    11,    12,
   187,   101,    17,   153,    89,   128,    19,   117,   115,    17,
   223,   224,   106,    45,    65,   172,   116,   101,     4,     5,
     6,   109,   172,   173,   118,    38,    66,    43,   116,    69,
    45,    47,   116,   246,   107,    43,    49,   117,     3,    47,
    37,   254,   259,   117,   257,   118,    78,    63,     3,   164,
     3,     3,     4,     5,     6,    63,    39,     9,   271,    11,
    12,    58,   219,   213,   117,    78,   223,    19,   218,   101,
   262,   258,   259,    65,    90,   120,   197,     3,     4,     5,
     6,    91,    90,   109,   116,    11,    12,    13,   101,   246,
   116,   115,    78,    19,   244,     7,     8,    49,   248,   291,
   117,   118,   289,   116,     3,     4,     5,     6,    74,    80,
    13,    14,    11,    12,    27,   101,   266,    88,    17,    52,
    19,   242,   117,   118,   239,    24,    78,   106,     3,     4,
     5,     6,     3,     4,     5,     6,    11,    12,   109,    78,
    11,    12,   117,   118,    19,   117,   118,   116,    19,   101,
   117,   118,    78,     3,     4,     5,     6,     4,     5,     6,
   120,    11,    12,    56,   116,   116,     3,     8,   118,    19,
    11,    12,    13,    14,   118,   101,     3,     0,   119,    78,
     9,    10,    11,    12,    13,    14,    11,    12,    13,    14,
   116,     3,   117,   118,    93,   102,    71,   117,   118,    28,
     3,    73,   101,    78,   120,   116,   116,    78,   117,     3,
    33,   106,    35,   118,    37,     3,    96,   116,    41,    90,
    43,   117,    90,    31,    71,   116,   101,    50,    78,    69,
   101,    78,    40,     3,   117,    59,    65,    73,    46,    83,
    63,   116,    74,    51,     8,   116,     8,    11,    12,    13,
    14,   101,    75,    33,   101,    35,    64,    37,   118,   116,
    71,    41,    48,    43,    72,    88,   116,    90,    29,    60,
    50,     9,    10,    11,    12,    13,    14,   100,    86,   117,
    97,   116,    56,    63,    92,   118,   117,   117,   117,    81,
    28,     5,     5,   109,   116,    75,   116,   116,   116,     5,
     5,   116,   110,   111,   112,   113,   114,     5,    88,   109,
    90,   109,   116,     5,   116,   116,     5,    58,     5,   116,
   100,   117,   117,     5,   117,     5,   116,    65,   117,     5,
   117,    71,    76,   117,     5,     5,     5,     5,   117,   117,
   117,   117,   117,    67,   117,   117,     0,    12,   158,   291,
   209,   243,   329,   257,   109,   154,   244,   128,   252,   246,
   284,   189,   346,    74,    79,    -1,   151
};
/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
#line 3 "/usr/local/share/bison.simple"

/* Skeleton output parser for bison,
   Copyright (C) 1984, 1989, 1990 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

#ifndef alloca
#ifdef __GNUC__
#define alloca __builtin_alloca
#else /* not GNU C.  */
#if (!defined (__STDC__) && defined (sparc)) || defined (__sparc__) || defined (__sparc) || defined (__sgi)
#include <alloca.h>
#else /* not sparc */
#if defined (MSDOS) && !defined (__TURBOC__)
#include <malloc.h>
#else /* not MSDOS, or __TURBOC__ */
#if defined(_AIX)
#include <malloc.h>
 #pragma alloca
#else /* not MSDOS, __TURBOC__, or _AIX */
#ifdef __hpux
#ifdef __cplusplus
extern "C" {
void *alloca (unsigned int);
};
#else /* not __cplusplus */
void *alloca ();
#endif /* not __cplusplus */
#endif /* __hpux */
#endif /* not _AIX */
#endif /* not MSDOS, or __TURBOC__ */
#endif /* not sparc.  */
#endif /* not GNU C.  */
#endif /* alloca not defined.  */

/* This is the parser code that is written into each bison parser
  when the %semantic_parser declaration is not specified in the grammar.
  It was written by Richard Stallman by simplifying the hairy parser
  used when %semantic_parser is specified.  */

/* Note: there must be only one dollar sign in this file.
   It is replaced by the list of actions, each action
   as one case of the switch.  */

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		-2
#define YYEOF		0
#define YYACCEPT	return(0)
#define YYABORT 	return(1)
#define YYERROR		goto yyerrlab1
/* Like YYERROR except do call yyerror.
   This remains here temporarily to ease the
   transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */
#define YYFAIL		goto yyerrlab
#define YYRECOVERING()  (!!yyerrstatus)
#define YYBACKUP(token, value) \
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    { yychar = (token), yylval = (value);			\
      yychar1 = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { yyerror ("syntax error: cannot back up"); YYERROR; }	\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

#ifndef YYPURE
#define YYLEX		yylex()
#endif

#ifdef YYPURE
#ifdef YYLSP_NEEDED
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, &yylloc, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval, &yylloc)
#endif
#else /* not YYLSP_NEEDED */
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval)
#endif
#endif /* not YYLSP_NEEDED */
#endif

/* If nonreentrant, generate the variables here */

#ifndef YYPURE

int	yychar;			/*  the lookahead symbol		*/
YYSTYPE	yylval;			/*  the semantic value of the		*/
				/*  lookahead symbol			*/

#ifdef YYLSP_NEEDED
YYLTYPE yylloc;			/*  location data for the lookahead	*/
				/*  symbol				*/
#endif

int yynerrs;			/*  number of parse errors so far       */
#endif  /* not YYPURE */

#if YYDEBUG != 0
int yydebug;			/*  nonzero means print parse trace	*/
/* Since this is uninitialized, it does not stop multiple parsers
   from coexisting.  */
#endif

/*  YYINITDEPTH indicates the initial size of the parser's stacks	*/

#ifndef	YYINITDEPTH
#define YYINITDEPTH 200
#endif

/*  YYMAXDEPTH is the maximum size the stacks can grow to
    (effective only if the built-in stack extension method is used).  */

#if YYMAXDEPTH == 0
#undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
#define YYMAXDEPTH 10000
#endif

/* Prevent warning if -Wstrict-prototypes.  */
#ifdef __GNUC__
int yyparse (void);
#endif

#if __GNUC__ > 1		/* GNU C and GNU C++ define this.  */
#define __yy_memcpy(TO,FROM,COUNT)	__builtin_memcpy(TO,FROM,COUNT)
#else				/* not GNU C or C++ */
#ifndef __cplusplus

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (to, from, count)
     char *to;
     char *from;
     int count;
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#else /* __cplusplus */

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (char *to, char *from, int count)
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#endif
#endif

#line 196 "/usr/local/share/bison.simple"

/* The user can define YYPARSE_PARAM as the name of an argument to be passed
   into yyparse.  The argument should have type void *.
   It should actually point to an object.
   Grammar actions can access the variable by casting it
   to the proper pointer type.  */

#ifdef YYPARSE_PARAM
#ifdef __cplusplus
#define YYPARSE_PARAM_ARG void *YYPARSE_PARAM
#define YYPARSE_PARAM_DECL
#else /* not __cplusplus */
#define YYPARSE_PARAM_ARG YYPARSE_PARAM
#define YYPARSE_PARAM_DECL void *YYPARSE_PARAM;
#endif /* not __cplusplus */
#else /* not YYPARSE_PARAM */
#define YYPARSE_PARAM_ARG
#define YYPARSE_PARAM_DECL
#endif /* not YYPARSE_PARAM */

int
yyparse(YYPARSE_PARAM_ARG)
     YYPARSE_PARAM_DECL
{
  register int yystate;
  register int yyn;
  register short *yyssp;
  register YYSTYPE *yyvsp;
  int yyerrstatus;	/*  number of tokens to shift before error messages enabled */
  int yychar1 = 0;		/*  lookahead token as an internal (translated) token number */

  short	yyssa[YYINITDEPTH];	/*  the state stack			*/
  YYSTYPE yyvsa[YYINITDEPTH];	/*  the semantic value stack		*/

  short *yyss = yyssa;		/*  refer to the stacks thru separate pointers */
  YYSTYPE *yyvs = yyvsa;	/*  to allow yyoverflow to reallocate them elsewhere */

#ifdef YYLSP_NEEDED
  YYLTYPE yylsa[YYINITDEPTH];	/*  the location stack			*/
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;

#define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
#define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

  int yystacksize = YYINITDEPTH;

#ifdef YYPURE
  int yychar;
  YYSTYPE yylval;
  int yynerrs;
#ifdef YYLSP_NEEDED
  YYLTYPE yylloc;
#endif
#endif

  YYSTYPE yyval;		/*  the variable used to return		*/
				/*  semantic values from the action	*/
				/*  routines				*/

  int yylen;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Starting parse\n");
#endif

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss - 1;
  yyvsp = yyvs;
#ifdef YYLSP_NEEDED
  yylsp = yyls;
#endif

/* Push a new state, which is found in  yystate  .  */
/* In all cases, when you get here, the value and location stacks
   have just been pushed. so pushing a state here evens the stacks.  */
yynewstate:

  *++yyssp = yystate;

  if (yyssp >= yyss + yystacksize - 1)
    {
      /* Give user a chance to reallocate the stack */
      /* Use copies of these so that the &'s don't force the real ones into memory. */
      YYSTYPE *yyvs1 = yyvs;
      short *yyss1 = yyss;
#ifdef YYLSP_NEEDED
      YYLTYPE *yyls1 = yyls;
#endif

      /* Get the current used size of the three stacks, in elements.  */
      int size = yyssp - yyss + 1;

#ifdef yyoverflow
      /* Each stack pointer address is followed by the size of
	 the data in use in that stack, in bytes.  */
#ifdef YYLSP_NEEDED
      /* This used to be a conditional around just the two extra args,
	 but that might be undefined if yyoverflow is a macro.  */
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yyls1, size * sizeof (*yylsp),
		 &yystacksize);
#else
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yystacksize);
#endif

      yyss = yyss1; yyvs = yyvs1;
#ifdef YYLSP_NEEDED
      yyls = yyls1;
#endif
#else /* no yyoverflow */
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
	{
	  yyerror("parser stack overflow");
	  return 2;
	}
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;
      yyss = (short *) alloca (yystacksize * sizeof (*yyssp));
      __yy_memcpy ((char *)yyss, (char *)yyss1, size * sizeof (*yyssp));
      yyvs = (YYSTYPE *) alloca (yystacksize * sizeof (*yyvsp));
      __yy_memcpy ((char *)yyvs, (char *)yyvs1, size * sizeof (*yyvsp));
#ifdef YYLSP_NEEDED
      yyls = (YYLTYPE *) alloca (yystacksize * sizeof (*yylsp));
      __yy_memcpy ((char *)yyls, (char *)yyls1, size * sizeof (*yylsp));
#endif
#endif /* no yyoverflow */

      yyssp = yyss + size - 1;
      yyvsp = yyvs + size - 1;
#ifdef YYLSP_NEEDED
      yylsp = yyls + size - 1;
#endif

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Stack size increased to %d\n", yystacksize);
#endif

      if (yyssp >= yyss + yystacksize - 1)
	YYABORT;
    }

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Entering state %d\n", yystate);
#endif

  goto yybackup;
 yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (yychar == YYEMPTY)
    {
#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Reading a token: ");
#endif
      yychar = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with */

  if (yychar <= 0)		/* This means end of input. */
    {
      yychar1 = 0;
      yychar = YYEOF;		/* Don't call YYLEX any more */

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Now at end of input.\n");
#endif
    }
  else
    {
      yychar1 = YYTRANSLATE(yychar);

#if YYDEBUG != 0
      if (yydebug)
	{
	  fprintf (stderr, "Next token is %d (%s", yychar, yytname[yychar1]);
	  /* Give the individual parser a way to print the precise meaning
	     of a token, for further debugging info.  */
#ifdef YYPRINT
	  YYPRINT (stderr, yychar, yylval);
#endif
	  fprintf (stderr, ")\n");
	}
#endif
    }

  yyn += yychar1;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
    goto yydefault;

  yyn = yytable[yyn];

  /* yyn is what to do for this token type in this state.
     Negative => reduce, -yyn is rule number.
     Positive => shift, yyn is new state.
       New state is final state => don't bother to shift,
       just return success.
     0, or most negative number => error.  */

  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrlab;

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting token %d (%s), ", yychar, yytname[yychar1]);
#endif

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  /* count tokens shifted since error; after three, turn off error status.  */
  if (yyerrstatus) yyerrstatus--;

  yystate = yyn;
  goto yynewstate;

/* Do the default action for the current state.  */
yydefault:

  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;

/* Do a reduction.  yyn is the number of a rule to reduce with.  */
yyreduce:
  yylen = yyr2[yyn];
  if (yylen > 0)
    yyval = yyvsp[1-yylen]; /* implement default value of the action */

#if YYDEBUG != 0
  if (yydebug)
    {
      int i;

      fprintf (stderr, "Reducing via rule %d (line %d), ",
	       yyn, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (i = yyprhs[yyn]; yyrhs[i] > 0; i++)
	fprintf (stderr, "%s ", yytname[yyrhs[i]]);
      fprintf (stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif


  switch (yyn) {

case 4:
#line 163 "minisql.y"
{
         yyval.nextP=yyvsp[0].nextP;
      ;
    break;}
case 5:
#line 169 "minisql.y"
{ ;
    break;}
case 6:
#line 171 "minisql.y"
{
       yyval.nextP=yyvsp[0].nextP;
     ;
    break;}
case 9:
#line 182 "minisql.y"
{
       yyval.nextP=yyvsp[0].nextP;
     ;
    break;}
case 10:
#line 186 "minisql.y"
{
       yyval.nextP=yyvsp[0].nextP;
     ;
    break;}
case 11:
#line 193 "minisql.y"
{
      lprintf("base_table_def <-- CREATE TABLE table '(' base_table_element_commalist ')'");
     yyval.nextP=yyvsp[-3].nextP;
     ;
    break;}
case 12:
#line 200 "minisql.y"
{
       yyval.nextP=yyvsp[0].nextP;
       lprintf ("base_table_element_commalist <-- base_table_element");
     ;
    break;}
case 13:
#line 204 "minisql.y"
{
       lprintf ("base_table_element_commalist <-- base_table_element_commalist ',' base_table_element");
    ;
    break;}
case 14:
#line 211 "minisql.y"
{
      lprintf ("base_table_element <-- column_def");
      yyval.nextP=yyvsp[0].nextP;
    ;
    break;}
case 15:
#line 220 "minisql.y"
{
        yyval.nextP->subtok=eCOLUMN;
        lprintf ("column_def <--  column data_type column_def_opt_list");
   ;
    break;}
case 16:
#line 227 "minisql.y"
{ ;
    break;}
case 17:
#line 228 "minisql.y"
{ 
       yyval.nextP=yyvsp[-1].nextP;
       lprintf ("column_def_opt_list <-- column_def_opt_list column_def_opt"); 
    ;
    break;}
case 18:
#line 236 "minisql.y"
{
         lprintf ("column_def_opt <-- NOT NULLX");
         yyval.nextP=(struct SQLvalue *)malloc(sizeof(struct SQLvalue));
         yyval.nextP->subtok=eNNULLTEST;
      ;
    break;}
case 19:
#line 242 "minisql.y"
{
         lprintf ("column_def_opt <-- NOT NULLX UNIQUE"); 
         yyval.nextP=(struct SQLvalue *)malloc(sizeof(struct SQLvalue));
         yyval.nextP->subtok=eNNULLTEST|eUNIQUE;
     ;
    break;}
case 20:
#line 248 "minisql.y"
{
         lprintf ("column_def_opt <-- NOT NULLX PRIMARY KEY");
         yyval.nextP=(struct SQLvalue *)malloc(sizeof(struct SQLvalue));
         yyval.nextP->subtok=eNNULLTEST|ePRIMARY;
     ;
    break;}
case 21:
#line 254 "minisql.y"
{ 
         lprintf ("column_def_opt <-- DEFAULT literal"); 
         yyval.nextP=(struct SQLvalue *)malloc(sizeof(struct SQLvalue));
         yyval.nextP->subtok=eDEFAULT|yyvsp[0].nextP->subtok;
         yyval.nextP->value.intval   =yyvsp[0].nextP->value.intval;
         yyval.nextP->value.floatval =yyvsp[0].nextP->value.floatval;
         yyval.nextP->value.strval   =yyvsp[0].nextP->value.strval;
         yyval.nextP->value.dimensions[0]=yyvsp[0].nextP->value.dimensions[0];
         yyval.nextP->value.dimensions[1]=yyvsp[0].nextP->value.dimensions[1];
         yyval.nextP->value.dimensions[2]=yyvsp[0].nextP->value.dimensions[2];
     ;
    break;}
case 22:
#line 265 "minisql.y"
{
         lprintf ("column_def_opt <-- DEFAULT NULLX"); 
         yyval.nextP=(struct SQLvalue *)malloc(sizeof(struct SQLvalue));
         yyval.nextP->subtok=eDEFAULT|eNULL;
     ;
    break;}
case 23:
#line 270 "minisql.y"
{ 
         lprintf ("column_def_opt <-- DEFAULT USER"); 
         yyval.nextP=(struct SQLvalue *)malloc(sizeof(struct SQLvalue));
         yyval.nextP->subtok=eDEFAULT|eUSER;
         yyval.nextP->value.strval=yyvsp[0].strval;
     ;
    break;}
case 24:
#line 295 "minisql.y"
{
         yyval.nextP=yyvsp[0].nextP;
         lprintf ("column_commalist <-- column");
       ;
    break;}
case 25:
#line 300 "minisql.y"
{
         yyval.nextP=yyvsp[-2].nextP;
         yyval.nextP->nextP=yyvsp[0].nextP;
	 
         lprintf ("column_commalist <-- column_commalist ',' column");
      ;
    break;}
case 26:
#line 310 "minisql.y"
{ ;
    break;}
case 27:
#line 312 "minisql.y"
{
         yyval.nextP=yyvsp[-1].nextP;
     ;
    break;}
case 28:
#line 319 "minisql.y"
{
        yyval.nextP->subtok=eSECURITY;
        yyval.nextP->value.intval=yyvsp[0].intval[0];
      ;
    break;}
case 29:
#line 326 "minisql.y"
{ ;
    break;}
case 30:
#line 328 "minisql.y"
{
       yyval.intval[0]=128;
     ;
    break;}
case 31:
#line 335 "minisql.y"
{
       yyval.nextP->subtok=opALL;
      ;
    break;}
case 32:
#line 339 "minisql.y"
{
       yyval.nextP->subtok=opALL;
      ;
    break;}
case 33:
#line 343 "minisql.y"
{
         yyval.nextP=yyvsp[0].nextP;
       ;
    break;}
case 34:
#line 351 "minisql.y"
{
        yyval.nextP->subtok=yyvsp[0].nextP->subtok;
      ;
    break;}
case 35:
#line 355 "minisql.y"
{

        yyval.nextP->subtok=yyvsp[-2].nextP->subtok|yyvsp[0].nextP->subtok;
;
    break;}
case 36:
#line 362 "minisql.y"
{
        yyval.nextP=(struct SQLvalue*)malloc(sizeof(struct SQLvalue));
        yyval.nextP->subtok=opSELECT;
       lprintf ("operation <-- SELECT");
       ;
    break;}
case 37:
#line 367 "minisql.y"
{
        yyval.nextP=(struct SQLvalue*)malloc(sizeof(struct SQLvalue));

        yyval.nextP->subtok=opINSERT;
       lprintf ("operation <-- INSERT");
    ;
    break;}
case 38:
#line 373 "minisql.y"
{
        yyval.nextP=(struct SQLvalue*)malloc(sizeof(struct SQLvalue));
        yyval.nextP->subtok=opDELETE;
       lprintf ("operation <-- DELETE");
    ;
    break;}
case 39:
#line 379 "minisql.y"
{
        yyval.nextP=(struct SQLvalue*)malloc(sizeof(struct SQLvalue));
        yyval.nextP->subtok=opDELETE;
       lprintf ("operation <-- DELETE");
     ;
    break;}
case 40:
#line 389 "minisql.y"
{
      lprintf ("grantee_commalist <--   grantee");
      yyval.nextP=(struct SQLvalue*)mymalloc(sizeof(struct SQLvalue));
      yyval.nextP->value.strval=yyvsp[0].nextP->value.strval;
      yyval.nextP->nextP=NULL;
    ;
    break;}
case 41:
#line 395 "minisql.y"
{
      struct SQLvalue *lastP=NULL,*searchP=yyvsp[0].nextP;
      lprintf ("grantee_commalist <--  grantee_commalist ',' grantee ");

       while (searchP) {
          lastP=searchP;
          searchP=searchP->nextP; 
       }   
       lastP->nextP=(struct SQLvalue*)mymalloc(sizeof(struct SQLvalue));
       lastP->nextP->value.strval=yyvsp[0].nextP->value.strval;
       lastP->nextP->nextP=NULL;
       memcpy(lastP->nextP,yyvsp[0].nextP,sizeof(struct SQLvalue));
    ;
    break;}
case 42:
#line 411 "minisql.y"
{
      lprintf ("grantee <--  PUBLIC");
      yyval.nextP->value.strval=(char*)malloc(7);
      strcpy(yyval.nextP->value.strval,"PUBLIC");
       ;
    break;}
case 43:
#line 416 "minisql.y"
{
      lprintf ("grantee <--  user ");
      yyval.nextP->value.strval=yyvsp[0].strval;
    ;
    break;}
case 44:
#line 423 "minisql.y"
{
      yyval.nextP=yyvsp[0].nextP;
     ;
    break;}
case 45:
#line 431 "minisql.y"
{
       /*opt_order_by_clause*/
        yyval.nextP=(struct SQLvalue*)malloc(sizeof(struct SQLvalue));
        yyval.nextP->subtok=eCURSOR;
        yyval.nextP->nextP=yyvsp[0].nextP;
     ;
    break;}
case 46:
#line 441 "minisql.y"
{
       yyval.nextP=yyvsp[0].nextP;
      lprintf ("sql <-- manipulative_statement");
     ;
    break;}
case 47:
#line 449 "minisql.y"
{
   yyval.nextP=yyvsp[0].nextP;
;
    break;}
case 48:
#line 454 "minisql.y"
{
     yyval.nextP=yyvsp[0].nextP;
   ;
    break;}
case 49:
#line 458 "minisql.y"
{
   yyval.nextP=yyvsp[0].nextP;
;
    break;}
case 50:
#line 462 "minisql.y"
{
   yyval.nextP=yyvsp[0].nextP;
;
    break;}
case 51:
#line 466 "minisql.y"
{
   yyval.nextP=yyvsp[0].nextP;
;
    break;}
case 52:
#line 470 "minisql.y"
{
   yyval.nextP=yyvsp[0].nextP;
;
    break;}
case 53:
#line 473 "minisql.y"
{
        lprintf ("manipulative_statement <--  insert_statement");
         yyval.nextP=yyvsp[0].nextP;
      ;
    break;}
case 54:
#line 478 "minisql.y"
{
   yyval.nextP=yyvsp[0].nextP;
;
    break;}
case 55:
#line 482 "minisql.y"
{
   yyval.nextP=yyvsp[0].nextP;
;
    break;}
case 56:
#line 485 "minisql.y"
{/*select_statement*/
      yyval.nextP=yyvsp[0].nextP;
      lprintf ("manipulative_statement <--  select_statement");
    ;
    break;}
case 57:
#line 490 "minisql.y"
{
   yyval.nextP=yyvsp[0].nextP;
;
    break;}
case 58:
#line 494 "minisql.y"
{
   yyval.nextP=yyvsp[0].nextP;
;
    break;}
case 59:
#line 502 "minisql.y"
{
           yyval.nextP=(struct SQLvalue*)malloc (sizeof(struct SQLvalue));
           yyval.nextP->subtok=eCURSOR;         
           yyval.nextP->value.strval=yyvsp[0].nextP->value.strval;
       ;
    break;}
case 60:
#line 511 "minisql.y"
{
           yyval.nextP->subtok=eNULL;
        ;
    break;}
case 61:
#line 518 "minisql.y"
{
          yyval.nextP=(struct SQLvalue*)malloc(sizeof(struct SQLvalue));
          yyval.nextP->value.strval=yyvsp[-4].nextP->value.strval;
          yyval.nextP->nextP=(struct SQLvalue*)malloc(sizeof(struct SQLvalue));
          yyval.nextP->value.strval=yyvsp[0].nextP->value.strval;
          yyval.nextP->subtok=opDELETE;
          yyval.nextP->nextP->subtok=eCURSOR;
          yyval.nextP->nextP->nextP=NULL;
          
      ;
    break;}
case 62:
#line 532 "minisql.y"
{
        yyval.nextP=yyvsp[0].nextP;
     ;
    break;}
case 63:
#line 540 "minisql.y"
{
        yyval.nextP=yyvsp[0].nextP;
     ;
    break;}
case 64:
#line 546 "minisql.y"
{
      lprintf ("insert_statement <-- INSERT INTO table opt_column_commalist values_or_query_spec");
        yyval.nextP=yyvsp[-1].nextP;
      ;
    break;}
case 65:
#line 553 "minisql.y"
{
      lprintf ("values_or_query_spec <--   VALUES '(' insert_atom_commalist ')'");
          yyval.nextP=yyvsp[-1].nextP;
      ;
    break;}
case 66:
#line 557 "minisql.y"
{
          yyval.nextP=yyvsp[0].nextP;
      lprintf ("values_or_query_spec <--  query_spec ");
;
    break;}
case 67:
#line 564 "minisql.y"
{
      lprintf ("insert_atom_commalist <--   insert_atom");
        yyval.nextP=yyvsp[0].nextP;
        yyval.nextP->nextP=NULL;
      ;
    break;}
case 68:
#line 569 "minisql.y"
{
       struct SQLvalue *lastP=NULL,*searchP=yyvsp[0].nextP;
      lprintf ("insert_atom_commalist <--  insert_atom_commalist ',' insert_atom ");
       while (searchP) {
          lastP=searchP;
          searchP=searchP->nextP; 
       }   
       lastP->nextP=(struct SQLvalue*)mymalloc(sizeof(struct SQLvalue));
       lastP->nextP->nextP=NULL;
       memcpy(lastP->nextP,yyvsp[0].nextP,sizeof(struct SQLvalue));
      ;
    break;}
case 69:
#line 583 "minisql.y"
{
      lprintf ("insert_atom <--   atom");
      
         yyval.nextP=yyvsp[0].nextP;
       ;
    break;}
case 70:
#line 588 "minisql.y"
{
      lprintf (" insert_atom <--  NULLX ");
        yyval.nextP=(struct SQLvalue*)malloc(sizeof(struct SQLvalue));
        yyval.nextP->subtok=eNULL;
      ;
    break;}
case 71:
#line 597 "minisql.y"
{
       yyval.nextP->value.strval=yyvsp[0].nextP->value.strval;
       yyval.nextP->subtok=eCURSOR;
     ;
    break;}
case 72:
#line 606 "minisql.y"
{
       yyval.nextP->subtok=eCURSOR;
      ;
    break;}
case 73:
#line 613 "minisql.y"
{
        lprintf ("query_spec <--    SELECT opt_all_distinct selection FROM table_exp");
     ;
    break;}
case 74:
#line 620 "minisql.y"
{
         lprintf("create_idx_statement <-- CREATE INDEX name ON table '(' opt_column_commalist ')'");
         yyval.nextP=yyvsp[0].nextP;
     ;
    break;}
case 75:
#line 627 "minisql.y"
{ ;
    break;}
case 76:
#line 628 "minisql.y"
{
         lprintf ("opt_all_distinct <--  ALL");
         yyval.intval[0]=opALL;

         ;
    break;}
case 77:
#line 633 "minisql.y"
{
         yyval.intval[0]=opDISTINCT;
         lprintf ("opt_all_distinct <--  DISTINCT ");
      ;
    break;}
case 78:
#line 641 "minisql.y"
{
           yyval.nextP=yyvsp[-4].nextP;
        ;
    break;}
case 79:
#line 647 "minisql.y"
{ ;
    break;}
case 80:
#line 649 "minisql.y"
{

           yyval.nextP=yyvsp[0].nextP; 

          ;
    break;}
case 81:
#line 655 "minisql.y"
{
           struct SQLvalue *searchP=yyvsp[0].nextP,*lastP=NULL;
           lprintf ("target_commalist <--  target_commalist ',' target");
            while (searchP) {
               lastP=searchP;
               searchP=searchP->nextP; 
            }   
           lastP->nextP=(struct SQLvalue *)mymalloc(sizeof(struct SQLvalue));
           lastP->nextP->nextP=NULL;
           lastP->nextP->subtok=yyvsp[0].nextP->subtok;
           lastP->nextP->value.strval=yyvsp[0].nextP->value.strval;

          ;
    break;}
case 82:
#line 672 "minisql.y"
{

            yyval.nextP=(struct SQLvalue*)malloc(sizeof(struct SQLvalue));
            yyval.nextP->subtok=eNULL;
            yyval.nextP->value.strval=yyvsp[-2].nextP->value.strval;
            yyval.nextP->value.intval=eCOLUMN;
            yyval.nextP->nextP=yyvsp[0].nextP;
       ;
    break;}
case 83:
#line 681 "minisql.y"
{  
            yyval.nextP=(struct SQLvalue*)malloc(sizeof(struct SQLvalue));
            yyval.nextP->subtok=eNULL;
            yyval.nextP->value.strval=yyvsp[-2].nextP->value.strval;
            yyval.nextP->value.intval=eCOLUMN;
            yyval.nextP->nextP=NULL;
         ;
    break;}
case 84:
#line 692 "minisql.y"
{
            yyval.nextP=yyvsp[-1].nextP;
         ;
    break;}
case 85:
#line 699 "minisql.y"
{
        lprintf ("target_commalist <--   target");
        yyval.nextP=yyvsp[0].nextP;
        yyval.nextP->nextP=NULL;
        ;
    break;}
case 86:
#line 705 "minisql.y"
{

       struct SQLvalue *searchP=yyvsp[0].nextP,*lastP=NULL;
       yyval.nextP=yyvsp[-2].nextP; 
      lprintf ("target_commalist <--  target_commalist ',' target");
       while (searchP) {
          lastP=searchP;
          searchP=searchP->nextP; 
       }   
       lastP->nextP=(struct SQLvalue *)mymalloc(sizeof(struct SQLvalue));
       lastP->nextP->nextP=NULL;
       lastP->nextP->subtok=yyvsp[0].nextP->subtok;
       lastP->nextP->value.strval=yyvsp[0].nextP->value.strval;
       ;
    break;}
case 87:
#line 723 "minisql.y"
{
        yyval.nextP=(struct SQLvalue*)malloc(sizeof(struct SQLvalue));
        yyval.nextP->subtok=yyvsp[0].nextP->subtok;
      ;
    break;}
case 88:
#line 730 "minisql.y"
{ ;
    break;}
case 89:
#line 732 "minisql.y"
{
           yyval.nextP=yyvsp[0].nextP;
         ;
    break;}
case 90:
#line 739 "minisql.y"
{
     yyval.nextP=yyvsp[0].nextP;
   ;
    break;}
case 91:
#line 750 "minisql.y"
{
        yyval.nextP=yyvsp[0].nextP;
      ;
    break;}
case 92:
#line 754 "minisql.y"
{
        yyval.nextP=yyvsp[-1].nextP;
       ;
    break;}
case 93:
#line 762 "minisql.y"
{
      lprintf ("selection <--  scalar_exp_commalist ");
        yyval.nextP=yyvsp[0].nextP;
        ;
    break;}
case 94:
#line 766 "minisql.y"
{
      lprintf ("selection <--  '*' ");
       yyval.nextP=(struct SQLvalue*)malloc(sizeof(struct SQLvalue));
       yyval.nextP->subtok=ALL;
     ;
    break;}
case 95:
#line 775 "minisql.y"
{
      yyval.nextP=yyvsp[-3].nextP;
      lprintf ("table_exp <--  from_clause  opt_where_clause  opt_group_by_clause opt_having_clause");
       
     ;
    break;}
case 96:
#line 784 "minisql.y"
{
      lprintf ("from_clause <-- table_ref_commalist ");
        yyval.nextP=yyvsp[0].nextP;
      
      ;
    break;}
case 97:
#line 792 "minisql.y"
{
      lprintf ("table_ref_commalist <--    table_ref");
        yyval.nextP=(struct SQLvalue*)mymalloc(sizeof(struct SQLvalue));
        yyval.nextP->value.strval=yyvsp[0].nextP->value.strval;
        yyval.nextP->subtok=eTABLE;
        yyval.nextP->nextP=NULL;
        yyval.nextP=yyvsp[0].nextP;
      ;
    break;}
case 98:
#line 800 "minisql.y"
{ 
      struct SQLvalue *searchP=yyvsp[0].nextP,*lastP=NULL;
      yyval.nextP=yyvsp[-2].nextP;
      lprintf ("table_ref_commalist <--  table_ref_commalist ',' table_ref");
       while (searchP) {
          lastP=searchP;
          searchP=searchP->nextP; 
       }   
       lastP->nextP=(struct SQLvalue*)mymalloc(sizeof(struct SQLvalue));
       lastP->nextP->nextP=NULL;
       lastP->nextP->subtok=eTABLE;
       lastP->nextP->value.strval=yyvsp[0].nextP->value.strval;
       yyval.nextP->nextP=yyvsp[0].nextP;
      ;
    break;}
case 99:
#line 817 "minisql.y"
{
         lprintf ("table_ref <--    table");
          yyval.nextP=(struct SQLvalue*)malloc(sizeof(struct SQLvalue));
          yyval.nextP->value.strval=yyvsp[0].nextP->value.strval;
          yyval.nextP->subtok=eTABLE;
         yyval.nextP->nextP=NULL;
        ;
    break;}
case 100:
#line 825 "minisql.y"
{
          yyval.nextP=(struct SQLvalue*)malloc(sizeof(struct SQLvalue));
          yyval.nextP->value.strval=yyvsp[-1].nextP->value.strval;
          yyval.nextP->subtok=eTABLE;
          yyval.nextP->nextP=(struct SQLvalue*)malloc(sizeof(struct SQLvalue));
          yyval.nextP->nextP->subtok=eRANGE;
          yyval.nextP->nextP->value.strval=yyvsp[0].strval;
        ;
    break;}
case 101:
#line 837 "minisql.y"
{
      lprintf ("where_clause <-- WHERE search_condition ");
           yyval.nextP=yyvsp[0].nextP;

     ;
    break;}
case 102:
#line 846 "minisql.y"
{
     ;
    break;}
case 103:
#line 850 "minisql.y"
{
         lprintf ("opt_group_by_clause <--  GROUP BY column_ref_commalist");
         yyval.nextP=yyvsp[0].nextP;  
         yyval.nextP->subtok=eGROUP;
       ;
    break;}
case 104:
#line 858 "minisql.y"
{
      lprintf ("column_ref_commalist <--   column_ref");
       yyval.nextP=(struct SQLvalue*)malloc(sizeof(struct SQLvalue));
       yyval.nextP->nextP=NULL;
       yyval.nextP->subtok=eCOLUMN;
       yyval.nextP->value.strval=yyvsp[0].nextP->value.strval;
     ;
    break;}
case 105:
#line 865 "minisql.y"
{
       struct SQLvalue *lastP=NULL,*searchP=yyvsp[-2].nextP;
       lprintf ("column_ref_commalist <--  column_ref_commalist ',' column_ref ");
       while (searchP) {
          lastP=searchP;
          searchP=searchP->nextP; 
       }   
       lastP->nextP=(struct SQLvalue*)mymalloc(sizeof(struct SQLvalue));
       lastP->nextP->nextP=NULL;
       yyval.nextP->subtok=eCOLUMN;
       yyval.nextP->value.strval=yyvsp[0].nextP->value.strval;

     ;
    break;}
case 106:
#line 881 "minisql.y"
{;
    break;}
case 107:
#line 884 "minisql.y"
{
           yyval.nextP=yyvsp[0].nextP;
          lprintf ("opt_having_clasue <-- HAVING search_condition ");

        ;
    break;}
case 108:
#line 892 "minisql.y"
{
        lprintf ("search_condition <-- search_condition OR search_condition ");
        yyval.nextP=(struct SQLvalue*)malloc(sizeof(struct SQLvalue));
        yyval.nextP->subtok=opOR;
        yyval.nextP->leftP=yyvsp[-2].nextP;
        yyval.nextP->rightP=yyvsp[0].nextP;
     ;
    break;}
case 109:
#line 900 "minisql.y"
{
      lprintf ("search_condition <-- search_condition AND search_condition  ");
      yyval.nextP=(struct SQLvalue*)malloc(sizeof(struct SQLvalue));
      yyval.nextP->subtok=opAND;
      yyval.nextP->leftP=yyvsp[-2].nextP;
      yyval.nextP->rightP=yyvsp[0].nextP;

    ;
    break;}
case 110:
#line 909 "minisql.y"
{
      lprintf ("search_condition <-- NOT search_condition  ");
      yyval.nextP=(struct SQLvalue*)malloc(sizeof(struct SQLvalue));
      yyval.nextP->subtok=opNOT;
      yyval.nextP->nextP=yyvsp[0].nextP;

   ;
    break;}
case 111:
#line 917 "minisql.y"
{
      lprintf ("search_condition <-- '(' search_condition ')' ");
       yyval.nextP=yyvsp[-1].nextP;
       yyval.nextP->nextP=NULL;
   ;
    break;}
case 112:
#line 923 "minisql.y"
{
      lprintf ("search_condition <-- predicate ");
       yyval.nextP=yyvsp[0].nextP;

  ;
    break;}
case 113:
#line 932 "minisql.y"
{ 
          yyval.nextP=yyvsp[0].nextP;
        ;
    break;}
case 114:
#line 936 "minisql.y"
{ 
          yyval.nextP=yyvsp[0].nextP;
        ;
    break;}
case 115:
#line 940 "minisql.y"
{ 
          yyval.nextP=yyvsp[0].nextP;
        ;
    break;}
case 116:
#line 944 "minisql.y"
{ 
          yyval.nextP=yyvsp[0].nextP;
        ;
    break;}
case 117:
#line 948 "minisql.y"
{ 
          yyval.nextP=yyvsp[0].nextP;
        ;
    break;}
case 118:
#line 952 "minisql.y"
{ 
          yyval.nextP=yyvsp[0].nextP;
        ;
    break;}
case 119:
#line 956 "minisql.y"
{ 
          yyval.nextP=yyvsp[0].nextP;
        ;
    break;}
case 120:
#line 963 "minisql.y"
{ 
          lprintf ("comparison_predicate <-- scalar_exp COMPARISON scalar_exp");
	  
          yyval.nextP=yyvsp[-2].nextP;
        ;
    break;}
case 121:
#line 969 "minisql.y"
{ 
          lprintf ("comparison_predicate <-- scalar_exp COMPARISON subquery");
          yyval.nextP=yyvsp[-2].nextP;
        ;
    break;}
case 122:
#line 977 "minisql.y"
{ 
          yyval.nextP=yyvsp[-5].nextP;
        ;
    break;}
case 123:
#line 981 "minisql.y"
{ 
          yyval.nextP=(struct SQLvalue*)malloc(sizeof(struct SQLvalue));
          yyval.nextP->subtok=eBETWEEN;
          yyval.nextP->rightP=(struct SQLvalue*)malloc(sizeof(struct SQLvalue ));
          memcpy(yyval.nextP->rightP,yyvsp[-2].nextP,sizeof(struct SQLvalue));
          yyval.nextP->leftP=(struct SQLvalue*)malloc(sizeof(struct SQLvalue));
          memcpy(yyval.nextP->leftP,yyvsp[0].nextP,sizeof(struct SQLvalue));
        ;
    break;}
case 124:
#line 993 "minisql.y"
{ 
           yyval.nextP=(struct SQLvalue*) malloc(sizeof(struct SQLvalue));
           yyval.nextP->subtok=eNLIKE;
           yyval.nextP->value.intval=yyvsp[-4].nextP->value.intval;
           yyval.nextP->value.strval=yyvsp[-4].nextP->value.strval;
           yyval.nextP->nextP=yyvsp[-1].nextP;
        ;
    break;}
case 125:
#line 1001 "minisql.y"
{ 
           yyval.nextP=(struct SQLvalue*) malloc(sizeof(struct SQLvalue));
           yyval.nextP->subtok=eLIKE;
           yyval.nextP->value.intval=yyvsp[-3].nextP->value.intval;
           yyval.nextP->value.strval=yyvsp[-3].nextP->value.strval;
           yyval.nextP->nextP=yyvsp[-1].nextP;
        ;
    break;}
case 126:
#line 1011 "minisql.y"
{ ;
    break;}
case 127:
#line 1013 "minisql.y"
{ 
          yyval.nextP=(struct SQLvalue*)malloc(sizeof(struct SQLvalue));
          yyval.nextP->subtok=eESCAPE;
          yyval.nextP->nextP=yyvsp[0].nextP;
        ;
    break;}
case 128:
#line 1022 "minisql.y"
{
           yyval.nextP=(struct SQLvalue*) malloc(sizeof(struct SQLvalue));
           yyval.nextP->subtok=eNNULLTEST;
           yyval.nextP->value.intval=yyvsp[-3].nextP->value.intval;
           yyval.nextP->value.strval=yyvsp[-3].nextP->value.strval;
	;
    break;}
case 129:
#line 1029 "minisql.y"
{
	  /* column_ref semantics are in "value" 
             by strval for the name and intval has eCOLUMN*/
           yyval.nextP=(struct SQLvalue*) malloc(sizeof(struct SQLvalue));
           yyval.nextP->subtok=eNULLTEST;
           yyval.nextP->value.intval=yyvsp[-2].nextP->value.intval;
           yyval.nextP->value.strval=yyvsp[-2].nextP->value.strval;
        ;
    break;}
case 130:
#line 1041 "minisql.y"
{ 
          yyval.nextP=yyvsp[-5].nextP;
        ;
    break;}
case 131:
#line 1045 "minisql.y"
{ 
          yyval.nextP=yyvsp[-4].nextP;
        ;
    break;}
case 132:
#line 1049 "minisql.y"
{ 
          yyval.nextP=yyvsp[-5].nextP;
        ;
    break;}
case 133:
#line 1053 "minisql.y"
{
          yyval.nextP=yyvsp[-4].nextP;
       ;
    break;}
case 134:
#line 1059 "minisql.y"
{
         lprintf ("atom_commalist <--    atom ");
        
         yyval.nextP=yyvsp[0].nextP; 
         yyval.nextP->nextP=NULL;
      ;
    break;}
case 135:
#line 1065 "minisql.y"
{
          struct SQLvalue *lastP=NULL,*searchP=yyvsp[-2].nextP;
          lprintf ("atom_commalist <--  atom_commalist ',' atom ");
          while (searchP) {
              lastP=searchP;
              searchP=searchP->nextP;
          }
          lastP->nextP=(struct SQLvalue*)mymalloc(sizeof(struct SQLvalue));
          memcpy(lastP->nextP,yyvsp[0].nextP,sizeof(struct SQLvalue));
          lastP->nextP->nextP=NULL;
      ;
    break;}
case 136:
#line 1080 "minisql.y"
{
         yyval.nextP=yyvsp[-3].nextP;
         yyval.nextP->nextP=(struct SQLvalue*)malloc(sizeof(struct SQLvalue));
         yyval.nextP->nextP->subtok=yyvsp[-1].intval[0];
         yyval.nextP->nextP->nextP=yyvsp[0].nextP;
     ;
    break;}
case 137:
#line 1089 "minisql.y"
{
       lprintf ("data_type <--  ANY");
        yyval.intval[0]=opANY;
     ;
    break;}
case 138:
#line 1093 "minisql.y"
{
      lprintf ("data_type <--  ALL ");
      yyval.intval[0]=opALL;
    ;
    break;}
case 139:
#line 1097 "minisql.y"
{
      lprintf ("data_type <--  SOME ");
      yyval.intval[0]=opSOME;
    ;
    break;}
case 140:
#line 1105 "minisql.y"
{
         yyval.nextP=yyvsp[0].nextP;
      ;
    break;}
case 141:
#line 1112 "minisql.y"
{
         yyval.nextP=yyvsp[-3].nextP;
      ;
    break;}
case 142:
#line 1119 "minisql.y"
{
          lprintf ("scalar_exp <-- scalar_exp '+' scalar_exp");
	  
          yyval.nextP=(struct SQLvalue*) malloc(sizeof(struct SQLvalue));
          yyval.nextP->subtok=opAdd;
          yyval.nextP->nextP=yyvsp[-2].nextP;
          yyval.nextP->nextP->nextP=yyvsp[0].nextP;
          yyval.nextP->nextP->nextP->nextP=NULL;
        ;
    break;}
case 143:
#line 1129 "minisql.y"
{
          lprintf ("scalar_exp <-- scalar_exp '-' scalar_exp");
          yyval.nextP=(struct SQLvalue*) malloc(sizeof(struct SQLvalue));
          yyval.nextP->subtok=opSubtract;
          yyval.nextP->nextP=yyvsp[-2].nextP;
          yyval.nextP->nextP->nextP=yyvsp[0].nextP;
          yyval.nextP->nextP->nextP->nextP=NULL;
        ;
    break;}
case 144:
#line 1138 "minisql.y"
{
          lprintf ("scalar_exp <-- scalar_exp '*' scalar_exp");
          yyval.nextP=(struct SQLvalue*)malloc(sizeof(struct SQLvalue));
          yyval.nextP->subtok=opMultiply;
          yyval.nextP->nextP=yyvsp[-2].nextP;
          yyval.nextP->nextP->nextP=yyvsp[0].nextP;
          yyval.nextP->nextP->nextP->nextP=NULL;
        ;
    break;}
case 145:
#line 1147 "minisql.y"
{
          lprintf ("scalar_exp <-- scalar_exp '/' scalar_exp");
          yyval.nextP=(struct SQLvalue*)malloc(sizeof(struct SQLvalue));
          yyval.nextP->subtok=opDivide;
          yyval.nextP->nextP=yyvsp[-2].nextP;
          yyval.nextP->nextP->nextP=yyvsp[0].nextP;
          yyval.nextP->nextP->nextP->nextP=NULL;
        ;
    break;}
case 146:
#line 1155 "minisql.y"
{ yyval.nextP=yyvsp[0].nextP;;
    break;}
case 147:
#line 1157 "minisql.y"
{ yyval.nextP=yyvsp[0].nextP;;
    break;}
case 148:
#line 1158 "minisql.y"
{
          lprintf ("scalar_exp <--  atom");
          if (yyvsp[0].nextP->subtok==eUSER) {
             lprintf ("Illegal reference to user %s", yyvsp[0].nextP->value.strval);
             yyerror("Illegal reference to user");
          }
          yyval.nextP=yyvsp[0].nextP;
       ;
    break;}
case 149:
#line 1166 "minisql.y"
{
         /*
          intval:eCOLUMN,strval:name
            */
          lprintf ("scalar_exp <-- column_ref");
          yyval.nextP=(struct SQLvalue*) malloc(sizeof(struct SQLvalue));
          yyval.nextP->nextP=NULL;
          yyval.nextP->subtok=eCOLUMN;
          yyval.nextP->value.strval=yyvsp[0].nextP->value.strval;
     ;
    break;}
case 150:
#line 1177 "minisql.y"
{
          yyval.nextP=yyvsp[0].nextP;
        ;
    break;}
case 151:
#line 1181 "minisql.y"
{
          lprintf ("scalar_exp <--  '(' scalar_exp ')'");
            yyval.nextP=yyvsp[-1].nextP;
         ;
    break;}
case 152:
#line 1190 "minisql.y"
{
           yyval.nextP=yyvsp[0].nextP;
           yyval.nextP->nextP=NULL;
         ;
    break;}
case 153:
#line 1195 "minisql.y"
{
           void * temp;
           yyval.nextP=yyvsp[-2].nextP;
           temp = yyval.nextP->nextP;
           yyval.nextP->nextP=(struct SQLvalue*) malloc(sizeof(struct SQLvalue));

           memcpy(yyval.nextP->nextP,yyvsp[0].nextP,sizeof(struct SQLvalue));
           yyval.nextP->nextP->nextP=temp;
         ;
    break;}
case 154:
#line 1209 "minisql.y"
{
          yyval.nextP=(struct SQLvalue*)malloc(sizeof(struct SQLvalue));
          yyval.nextP->nextP=NULL;
          yyval.nextP->subtok=yyvsp[0].nextP;
	   /* paramater_ref is just a subtok */
           lprintf ("atom <--  parameter_ref");
       ;
    break;}
case 155:
#line 1217 "minisql.y"
{
	/* lhs is a nextP user */
        lprintf ("atom <-- literal ");
        yyval.nextP=yyvsp[0].nextP;
      ;
    break;}
case 156:
#line 1223 "minisql.y"
{
        yyval.nextP=(struct SQLvalue*)malloc(sizeof(struct SQLvalue));
        lprintf ("atom <--  USER");
        yyval.nextP->subtok=eUSER; 
      ;
    break;}
case 157:
#line 1233 "minisql.y"
{
        yyval.nextP=yyvsp[0].nextP;
      ;
    break;}
case 158:
#line 1237 "minisql.y"
{
          yyval.nextP=yyvsp[-1].nextP;
      ;
    break;}
case 159:
#line 1245 "minisql.y"
{
           yyval.nextP=(struct SQLvalue*)malloc(sizeof(struct SQLvalue));
           yyval.nextP->subtok=opALL;

        ;
    break;}
case 160:
#line 1251 "minisql.y"
{
           yyval.nextP=(struct SQLvalue*)malloc(sizeof(struct SQLvalue));
           yyval.nextP->value.intval=opDISTINCT;
           yyval.nextP->subtok=eCOLUMN;
           yyval.nextP->value.strval=yyvsp[-1].nextP->value.strval;
        ;
    break;}
case 161:
#line 1258 "minisql.y"
{
           yyval.nextP=(struct SQLvalue*)malloc(sizeof(struct SQLvalue));
           yyval.nextP->subtok=opALL;
           yyval.nextP->value.intval=eCOLUMN;
           yyval.nextP->nextP=yyvsp[-1].nextP;
        ;
    break;}
case 162:
#line 1265 "minisql.y"
{
           yyval.nextP=yyvsp[-1].nextP;
        ;
    break;}
case 163:
#line 1271 "minisql.y"
{
          lprintf ("literal <--     STRING");
          yyval.nextP=(struct SQLvalue*)malloc(sizeof(struct SQLvalue));
          yyval.nextP->value.strval=(char*)mymalloc(sizeof(char)*(strlen(yyvsp[0].strval)+1)) ;
          strcpy(yyval.nextP->value.strval,yyvsp[0].strval);
          yyval.nextP->subtok=STRING;
       ;
    break;}
case 164:
#line 1278 "minisql.y"
{
          yyval.nextP=(struct SQLvalue*)malloc(sizeof(struct SQLvalue));
          lprintf ("literal <--     INTNUM  ");
          yyval.nextP->value.intval=yyvsp[0].intval[0];
          yyval.nextP->subtok=INTNUM;
      ;
    break;}
case 165:
#line 1284 "minisql.y"
{
          yyval.nextP=(struct SQLvalue *)malloc(sizeof(struct SQLvalue));
          lprintf ("data_type <--   APPROXNUM ");
      /* $$.approxnum=atof($1);*/
          yyval.nextP->value.floatval=yyvsp[0].floatval;
          yyval.nextP->subtok=APPROXNUM;   
      ;
    break;}
case 166:
#line 1295 "minisql.y"
{
      lprintf ("column_ref <-- NAME[%d]\n",strlen(yyvsp[0].strval));
       yyval.nextP=(struct SQLvalue *)malloc(sizeof(struct SQLvalue));
       yyval.nextP->nextP=NULL;
       yyval.nextP->subtok=eCOLUMN;
       yyval.nextP->value.strval=(char*)malloc(48) ;
       strcpy(yyval.nextP->value.strval,yyvsp[0].strval);

     ;
    break;}
case 167:
#line 1304 "minisql.y"
{
       lprintf ("column_ref <-- NAME '.' NAME");
       yyval.nextP=(struct SQLvalue *)malloc(sizeof(struct SQLvalue));
       yyval.nextP->value.strval=(char*)mymalloc(sizeof(char)*(strlen(yyvsp[-2].strval)+2+strlen(yyvsp[0].strval))) ;
       strcpy(yyval.nextP->value.strval,yyvsp[-2].strval);
       strcat(yyval.nextP->value.strval,".");
       strcat(yyval.nextP->value.strval,yyvsp[0].strval);
       yyval.nextP->subtok=eCOLUMN;
      ;
    break;}
case 168:
#line 1313 "minisql.y"
{
       lprintf ("column_ref <-- NAME '.' NAME");
       yyval.nextP=(struct SQLvalue *)malloc(sizeof(struct SQLvalue));
       yyval.nextP->value.strval=(char*)
         mymalloc(sizeof(char)*
            (strlen(yyvsp[-4].strval)+4+strlen(yyvsp[-2].strval)+strlen(yyvsp[0].strval))) ;
       strcpy(yyval.nextP->value.strval,yyvsp[-4].strval);
       strcat(yyval.nextP->value.strval,".");
       strcat(yyval.nextP->value.strval,yyvsp[-2].strval);
       strcat(yyval.nextP->value.strval,".");
       strcat(yyval.nextP->value.strval,yyvsp[0].strval);
       yyval.nextP->subtok=eCOLUMN;
      ;
    break;}
case 169:
#line 1329 "minisql.y"
{

        lprintf ("table <-- name <%s>\n",yyvsp[0].strval);
       yyval.nextP=(struct SQLvalue *)malloc(sizeof(struct SQLvalue));
        yyval.nextP->nextP=NULL;
       yyval.nextP->value.strval=
        (char*)mymalloc(strlen(yyvsp[0].strval)+8);
        strcpy(yyval.nextP->value.strval,yyvsp[0].strval);
        yyval.nextP->subtok=eTABLE;
    ;
    break;}
case 170:
#line 1339 "minisql.y"
{
       lprintf ("table <-- NAME '.' NAME");
       yyval.nextP=(struct SQLvalue *)malloc(sizeof(struct SQLvalue));
       yyval.nextP->value.strval=
        (char*)mymalloc(sizeof(char)*((strlen(yyvsp[-2].strval)+2+strlen(yyvsp[0].strval))));
       strcpy(yyval.nextP->value.strval,yyvsp[-2].strval);
       strcat(yyval.nextP->value.strval,".");
       strcat(yyval.nextP->value.strval,yyvsp[0].strval);
       yyval.nextP->subtok=eTABLE;
   ;
    break;}
case 171:
#line 1352 "minisql.y"
{
          yyval.nextP=(struct SQLvalue *)malloc(sizeof(struct SQLvalue));
          lprintf ("data_type <--  CHARACTER");
          yyval.nextP->subtok=eCHARTYPE;
          yyval.nextP->value.dimensions[0]=-1;
          yyval.nextP->value.dimensions[1]=-1;
          yyval.nextP->value.dimensions[2]=-1;
          yyval.nextP->nextP=NULL;
	  
      ;
    break;}
case 172:
#line 1362 "minisql.y"
{
          lprintf ("data_type <--  CHARACTER '(' INTNUM ')'");
          yyval.nextP=(struct SQLvalue *)malloc(sizeof(struct SQLvalue));
          yyval.nextP->value.dimensions[0]=yyvsp[-1].intval[0];
          yyval.nextP->value.dimensions[1]=-1;
          yyval.nextP->value.dimensions[2]=-1;
          yyval.nextP->subtok=eCHARTYPE;
          yyval.nextP->nextP=NULL;
      ;
    break;}
case 173:
#line 1371 "minisql.y"
{
          lprintf ("data_type <--   NUMERIC ");
          yyval.nextP=(struct SQLvalue *)malloc(sizeof(struct SQLvalue));
          yyval.nextP->subtok=eNUMERIC;
          yyval.nextP->value.dimensions[1]=-1;
          yyval.nextP->value.dimensions[1]=-1;
          yyval.nextP->value.dimensions[2]=-1;
          yyval.nextP->value.intval=eCHARTYPE;
          yyval.nextP->nextP=NULL;
      ;
    break;}
case 174:
#line 1381 "minisql.y"
{
          lprintf ("data_type <--   NUMERIC '(' INTNUM ')' ");
          yyval.nextP=(struct SQLvalue *)malloc(sizeof(struct SQLvalue));
          yyval.nextP->value.dimensions[0]=yyvsp[-1].intval[0];
          yyval.nextP->value.dimensions[1]=-1;
          yyval.nextP->value.dimensions[2]=-1;
          yyval.nextP->subtok=eNUMERIC;
          yyval.nextP->nextP=NULL;
      ;
    break;}
case 175:
#line 1390 "minisql.y"
{
          lprintf ("data_type <--   NUMERIC '(' INTNUM ',' INTNUM ')' ");
          yyval.nextP=(struct SQLvalue *)malloc(sizeof(struct SQLvalue));
          yyval.nextP->value.dimensions[0]=yyvsp[-3].intval[0];
          yyval.nextP->value.dimensions[1]=yyvsp[-1].intval[0];
          yyval.nextP->value.dimensions[2]=-1;
          yyval.nextP->subtok=eNUMERIC;
          yyval.nextP->nextP=NULL;
      ;
    break;}
case 176:
#line 1399 "minisql.y"
{
          lprintf ("data_type <--   DECIMAL ");
          yyval.nextP=(struct SQLvalue *)malloc(sizeof(struct SQLvalue));
          yyval.nextP->value.dimensions[0]=-1;
          yyval.nextP->value.dimensions[1]=-1;
          yyval.nextP->value.dimensions[2]=-1;
          yyval.nextP->subtok=eDECIMAL;
          yyval.nextP->nextP=NULL;
      ;
    break;}
case 177:
#line 1408 "minisql.y"
{
          lprintf ("data_type <--   DECIMAL  '(' INTNUM ')' ");
          yyval.nextP=(struct SQLvalue *)malloc(sizeof(struct SQLvalue));
          yyval.nextP->value.dimensions[0]=yyvsp[-1].intval[0];
          yyval.nextP->value.dimensions[1]=-1;
          yyval.nextP->value.dimensions[2]=-1;
          yyval.nextP->subtok=eDECIMAL;
          yyval.nextP->nextP=NULL;
      ;
    break;}
case 178:
#line 1417 "minisql.y"
{
          yyval.nextP=(struct SQLvalue *)malloc(sizeof(struct SQLvalue));
          lprintf ("data_type <--   DECIMAL  '(' INTNUM ',' INTNUM ')' ");
          yyval.nextP->value.dimensions[0]=yyvsp[-3].intval[0];
          yyval.nextP->value.dimensions[1]=yyvsp[-3].intval[0];
          yyval.nextP->value.dimensions[2]=-1;
          yyval.nextP->subtok=eDECIMAL;
      ;
    break;}
case 179:
#line 1425 "minisql.y"
{
          yyval.nextP=(struct SQLvalue *)malloc(sizeof(struct SQLvalue));
          lprintf ("data_type <--   INTEGER ");
          yyval.nextP->value.dimensions[0]=-1;
          yyval.nextP->value.dimensions[1]=-1;
          yyval.nextP->value.dimensions[2]=-1;
          yyval.nextP->subtok=eINTEGER;
          yyval.nextP->nextP=NULL;
      ;
    break;}
case 180:
#line 1434 "minisql.y"
{
          lprintf ("data_type <--   SMALLINT ");
          yyval.nextP=(struct SQLvalue *)malloc(sizeof(struct SQLvalue));
          yyval.nextP->value.dimensions[0]=-1;
          yyval.nextP->value.dimensions[1]=-1;
          yyval.nextP->value.dimensions[2]=-1;
          yyval.nextP->value.intval=eSMALLINT;
          yyval.nextP->nextP=NULL;
      ;
    break;}
case 181:
#line 1443 "minisql.y"
{
          yyval.nextP=(struct SQLvalue *)malloc(sizeof(struct SQLvalue));
          lprintf ("data_type <--   FLOAT ");
          yyval.nextP->value.floatval=yyvsp[0].floatval;
          yyval.nextP->subtok=eFLOAT;
          yyval.nextP->nextP=NULL;
      ;
    break;}
case 182:
#line 1450 "minisql.y"
{
          yyval.nextP=(struct SQLvalue *)malloc(sizeof(struct SQLvalue));
          yyval.nextP->value.dimensions[0]=yyvsp[-1].intval[0];
          yyval.nextP->value.dimensions[1]=-1;
          yyval.nextP->value.dimensions[2]=-1;
          lprintf ("data_type <--   FLOAT '(' INTNUM ')' ");
          yyval.nextP->subtok=eFLOAT;
          yyval.nextP->nextP=NULL;
      ;
    break;}
case 183:
#line 1459 "minisql.y"
{
          lprintf ("data_type <--   REAL ");
          yyval.nextP->value.dimensions[0]=-1;
          yyval.nextP->value.dimensions[1]=-1;
          yyval.nextP->value.dimensions[2]=-1;
          yyval.nextP->subtok=eREAL;
          yyval.nextP->nextP=NULL;
      ;
    break;}
case 184:
#line 1467 "minisql.y"
{
          lprintf ("data_type <-- DOUBLE PRECISION ");
          yyval.nextP->value.dimensions[0]=-1;
          yyval.nextP->value.dimensions[1]=-1;
          yyval.nextP->value.dimensions[2]=-1;
          yyval.nextP->subtok=eDOUBLEPREC;
          yyval.nextP->nextP=NULL;
      ;
    break;}
case 185:
#line 1475 "minisql.y"
{
          lprintf ("data_type <-- NCHAR ( INTNUM )");
          yyval.nextP->value.dimensions[0]=yyvsp[-1].intval[0];
          yyval.nextP->value.dimensions[1]=-1;
          yyval.nextP->value.dimensions[2]=-1;
          yyval.nextP->subtok=eCHARTYPE;
          yyval.nextP->nextP=NULL;
      ;
    break;}
case 186:
#line 1483 "minisql.y"
{
          lprintf ("data_type <-- NCHAR VARYING ( int )");
          yyval.nextP->value.dimensions[0]=yyvsp[-1].intval[0];
          yyval.nextP->value.dimensions[1]=-1;
          yyval.nextP->value.dimensions[2]=-1;
          yyval.nextP->subtok=eCHARTYPE;
          yyval.nextP->nextP=NULL;
      ;
    break;}
case 187:
#line 1491 "minisql.y"
{
          lprintf ("data_type <-- NATIONAL CHAR ( int )");
          yyval.nextP->value.dimensions[0]=yyvsp[-1].intval[0];
          yyval.nextP->value.dimensions[1]=-1;
          yyval.nextP->value.dimensions[2]=-1;
          yyval.nextP->subtok=eCHARTYPE;
          yyval.nextP->nextP=NULL;
      ;
    break;}
case 188:
#line 1499 "minisql.y"
{
          lprintf ("data_type <-- NCHAR ( int )");
          yyval.nextP->value.dimensions[0]=yyvsp[-1].intval[0];
          yyval.nextP->value.dimensions[1]=-1;
          yyval.nextP->value.dimensions[2]=-1;
          yyval.nextP->subtok=eCHARTYPE;
          yyval.nextP->nextP=NULL;
     ;
    break;}
case 189:
#line 1507 "minisql.y"
{
          lprintf ("data_type <-- CHARACTER VARYING ( int )");
          yyval.nextP->value.dimensions[0]=yyvsp[-1].intval[0];
          yyval.nextP->value.dimensions[1]=-1;
          yyval.nextP->value.dimensions[2]=-1;
          yyval.nextP->subtok=eCHARTYPE;
          yyval.nextP->nextP=NULL;
       ;
    break;}
case 190:
#line 1515 "minisql.y"
{
          lprintf ("data_type <-- CHAR VARYING ( int )");
          yyval.nextP->value.dimensions[0]=yyvsp[-1].intval[0];
          yyval.nextP->value.dimensions[1]=-1;
          yyval.nextP->value.dimensions[2]=-1;
          yyval.nextP->subtok=eCHARTYPE;
          yyval.nextP->nextP=NULL;
      ;
    break;}
case 191:
#line 1523 "minisql.y"
{
          lprintf ("data_type <-- VARCHAR ( int )");
          yyval.nextP->value.dimensions[0]=yyvsp[-1].intval[0];
          yyval.nextP->value.dimensions[1]=-1;
          yyval.nextP->value.dimensions[2]=-1;
          yyval.nextP->subtok=eCHARTYPE;
          yyval.nextP->nextP=NULL;
      ;
    break;}
case 192:
#line 1531 "minisql.y"
{
          lprintf ("data_type <-- BIT ( int )");
          yyval.nextP->value.dimensions[0]=yyvsp[-1].intval[0];
          yyval.nextP->value.dimensions[1]=-1;
          yyval.nextP->value.dimensions[2]=-1;
          yyval.nextP->subtok=eBOOLEAN;
          yyval.nextP->nextP=NULL;
      ;
    break;}
case 193:
#line 1539 "minisql.y"
{
          lprintf ("data_type <-- BIT VARYING ( int )");
          yyval.nextP->value.dimensions[0]=yyvsp[-1].intval[0];
          yyval.nextP->value.dimensions[1]=-1;
          yyval.nextP->value.dimensions[2]=-1;
          yyval.nextP->subtok=eBOOLEAN;
          yyval.nextP->nextP=NULL;
      ;
    break;}
case 194:
#line 1552 "minisql.y"
{
      lprintf ("column <- NAME\n"); 
       yyval.nextP=(struct SQLvalue*)malloc(sizeof(struct SQLvalue));
       yyval.nextP->subtok=eCOLUMN;
       /*       $$->value.strval =(char*)malloc(strlen($1)+1) ;*/
       yyval.nextP->value.strval =(char*)malloc(48) ;
       strcpy(yyval.nextP->value.strval,yyvsp[0].strval);
          yyval.nextP->nextP=NULL;
   ;
    break;}
case 195:
#line 1564 "minisql.y"
{
       yyval.nextP=(struct SQLvalue*)malloc(sizeof(struct SQLvalue));
       yyval.nextP->value.strval=(char*)malloc(strlen(yyvsp[0].strval)+1);
       strcpy(yyval.nextP->value.strval,yyvsp[0].strval);
       yyval.nextP->subtok=eCURSOR;
     ;
    break;}
case 196:
#line 1572 "minisql.y"
{
       yyval.nextP=(struct SQLvalue*)malloc(sizeof(struct SQLvalue));
       yyval.nextP->value.strval=(char*)malloc(strlen(yyvsp[0].strval)+1);
       strcpy(yyval.nextP->value.strval,yyvsp[0].strval);
       yyval.nextP->subtok=eCURSOR;
     ;
    break;}
case 197:
#line 1582 "minisql.y"
{
      yyval.nextP=(struct SQLvalue*)malloc(sizeof(struct SQLvalue));
      yyval.nextP->value.strval=(char*)malloc(strlen(yyvsp[0].strval)+1);
      strcpy(yyval.nextP->value.strval,yyvsp[0].strval);
      yyval.nextP->subtok=ePARAMATER;
    ;
    break;}
case 198:
#line 1592 "minisql.y"
{
      yyval.strval=yyvsp[0].strval;
    ;
    break;}
case 199:
#line 1598 "minisql.y"
{
      lprintf ("user <--  NAME ");
      yyval.strval=yyvsp[0].strval;
    ;
    break;}
case 200:
#line 1604 "minisql.y"
{
     lprintf ("index <--  NAME ");
      yyval.strval=yyvsp[0].strval;
    ;
    break;}
}
   /* the action file gets copied in in place of this dollarsign */
#line 498 "/usr/local/share/bison.simple"

  yyvsp -= yylen;
  yyssp -= yylen;
#ifdef YYLSP_NEEDED
  yylsp -= yylen;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

  *++yyvsp = yyval;

#ifdef YYLSP_NEEDED
  yylsp++;
  if (yylen == 0)
    {
      yylsp->first_line = yylloc.first_line;
      yylsp->first_column = yylloc.first_column;
      yylsp->last_line = (yylsp-1)->last_line;
      yylsp->last_column = (yylsp-1)->last_column;
      yylsp->text = 0;
    }
  else
    {
      yylsp->last_line = (yylsp+yylen-1)->last_line;
      yylsp->last_column = (yylsp+yylen-1)->last_column;
    }
#endif

  /* Now "shift" the result of the reduction.
     Determine what state that goes to,
     based on the state we popped back to
     and the rule number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
  if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTBASE];

  goto yynewstate;

yyerrlab:   /* here on detecting error */

  if (! yyerrstatus)
    /* If not already recovering from an error, report this error.  */
    {
      ++yynerrs;

#ifdef YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (yyn > YYFLAG && yyn < YYLAST)
	{
	  int size = 0;
	  char *msg;
	  int x, count;

	  count = 0;
	  /* Start X at -yyn if nec to avoid negative indexes in yycheck.  */
	  for (x = (yyn < 0 ? -yyn : 0);
	       x < (sizeof(yytname) / sizeof(char *)); x++)
	    if (yycheck[x + yyn] == x)
	      size += strlen(yytname[x]) + 15, count++;
	  msg = (char *) malloc(size + 15);
	  if (msg != 0)
	    {
	      strcpy(msg, "parse error");

	      if (count < 5)
		{
		  count = 0;
		  for (x = (yyn < 0 ? -yyn : 0);
		       x < (sizeof(yytname) / sizeof(char *)); x++)
		    if (yycheck[x + yyn] == x)
		      {
			strcat(msg, count == 0 ? ", expecting `" : " or `");
			strcat(msg, yytname[x]);
			strcat(msg, "'");
			count++;
		      }
		}
	      yyerror(msg);
	      free(msg);
	    }
	  else
	    yyerror ("parse error; also virtual memory exceeded");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror("parse error");
    }

  goto yyerrlab1;
yyerrlab1:   /* here on error raised explicitly by an action */

  if (yyerrstatus == 3)
    {
      /* if just tried and failed to reuse lookahead token after an error, discard it.  */

      /* return failure if at end of input */
      if (yychar == YYEOF)
	YYABORT;

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Discarding token %d (%s).\n", yychar, yytname[yychar1]);
#endif

      yychar = YYEMPTY;
    }

  /* Else will try to reuse lookahead token
     after shifting the error token.  */

  yyerrstatus = 3;		/* Each real token shifted decrements this */

  goto yyerrhandle;

yyerrdefault:  /* current state does not do anything special for the error token. */

#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */
  yyn = yydefact[yystate];  /* If its default is to accept any token, ok.  Otherwise pop it.*/
  if (yyn) goto yydefault;
#endif

yyerrpop:   /* pop the current state because it cannot handle the error token */

  if (yyssp == yyss) YYABORT;
  yyvsp--;
  yystate = *--yyssp;
#ifdef YYLSP_NEEDED
  yylsp--;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "Error: state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

yyerrhandle:

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yyerrdefault;

  yyn += YYTERROR;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
    goto yyerrdefault;

  yyn = yytable[yyn];
  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrpop;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrpop;

  if (yyn == YYFINAL)
    YYACCEPT;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting error token, ");
#endif

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  yystate = yyn;
  goto yynewstate;
}
#line 1611 "minisql.y"

/*view_def:
       CREATE VIEW table opt_column_commalist
       AS   query_spec opt_with_check_option
       ;*/
/*   
opt_with_check_option:
*/ /* empty *//*
    |  '(' column_commalist  ')'
    ;
*/
/*
table_constraint_def:
       UNIQUE '('  column_commalist ')'
   |   PRIMARY KEY '(' column_commalist ')'
   |   FOREIGN KEY '(' column_commalist ')'  REFERENCES   table
   |   FOREIGN KEY '(' column_commalist ')'  REFERENCES   table '(' column_commalist ')'
   |   CHECK '(' column_commalist ')'
   ;
*/

/* 
sql:
      WHENEVER NOT FOUND when_action
     | WHENEVER SQLERROR when_action
      ;     


when_action:   GOTO NAME
     | CONTINUE
     ;
*/


/*opt_order_by_clause:
 */ /* empty*//*
     | ORDER BY ordering_spec_commalist
     ; 

*/
/*

ordering_spec_commalist:
        ordering_spec
     | ordering_spec_commalist ',' ordering_spec
     ;
  
ordering_spec:
        INTNUM opt_asc_desc
     |  column_ref opt_asc_desc
     ;

opt_asc_desc:
*/  /* empty *//*
     | ASC
     | DESC
      ;

     | '+' scalar_exp %prec UMINUS

     | '-' scalar_exp %prec UMINUS
*/
/*
select_statement:
       SELECT opt_all_distinct selection INTO target_commalist FROM table_exp
      {
      lprintf ("select_statement <--   SELECT opt_all_distinct selection INTO target_commalist FROM table_exp");
       }
     ; 

%type <nextP>  select_statement
*/
