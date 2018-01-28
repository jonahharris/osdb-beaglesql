
/*  A Bison parser, made from odl.y
 by  GNU Bison version 1.25
  */

#define YYBISON 1  /* Identify Bison output.  */

#define	SEMICOLON	258
#define	DBLCOLON	259
#define	COLON	260
#define	OPCURLBRKT	261
#define	CLCURLBRKT	262
#define	CONST	263
#define	COMMA	264
#define	EQUALS	265
#define	OPSQBRKT	266
#define	CLSQBRKT	267
#define	OPPAREN	268
#define	CLPAREN	269
#define	CLASS	270
#define	EXTENDS	271
#define	XOR_OP	272
#define	OR_OP	273
#define	AND_OP	274
#define	SHRITE_OP	275
#define	SHLEFT_OP	276
#define	INTERFACE	277
#define	CONTEXT	278
#define	IN	279
#define	OUT	280
#define	INOUT	281
#define	VOID	282
#define	RELATIONSHIP	283
#define	INVERSE	284
#define	ONEWAY	285
#define	RAISES	286
#define	EXCEPTION	287
#define	STRUCT	288
#define	UNION	289
#define	SWITCH	290
#define	READONLY	291
#define	ATTRIBUTE	292
#define	KEY	293
#define	KEYS	294
#define	SET	295
#define	LIST	296
#define	BAG	297
#define	DICTIONARY	298
#define	ARRAY	299
#define	SEQUENCE	300
#define	LESSTHAN	301
#define	GREATERTHAN	302
#define	INTERVAL	303
#define	LONG	304
#define	SHORT	305
#define	UNSIGNED	306
#define	INT	307
#define	FLOAT	308
#define	DOUBLE	309
#define	OCTET	310
#define	STRING	311
#define	TIME	312
#define	DATE	313
#define	TIMESTAMP	314
#define	BOOLEAN	315
#define	TYPEDEF	316
#define	TRUE	317
#define	FALSE	318
#define	CHAR	319
#define	ANY	320
#define	CASE	321
#define	DEFAULT	322
#define	ENUM	323
#define	EXTENT	324
#define	STRING_LITERAL	325
#define	CHARACTER_LITERAL	326
#define	IDENTIFIER	327
#define	MODULE	328
#define	FLOATING_PT_LITERAL	329

#line 1 "odl.y"




#define DATATYPEP struct descriptor *
#define DATASIZE  sizeof(struct descriptor)

struct descriptor
{
   struct descriptor *nextP;

};

#line 15 "odl.y"
typedef union {
  double floatval;
  unsigned long uLongVal;
  signed long   LongVal ;
  char * stringP;
  struct descriptor *nextP;
} YYSTYPE;
#include <stdio.h>

#ifndef __cplusplus
#ifndef __STDC__
#define const
#endif
#endif



#define	YYFINAL		351
#define	YYFLAG		-32768
#define	YYNTBASE	81

#define YYTRANSLATE(x) ((unsigned)(x) <= 329 ? yytranslate[x] : 183)

static const char yytranslate[] = {     0,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,    79,     2,     2,     2,
     2,    77,    75,     2,    76,     2,    78,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,    80,     2,     2,     2,     2,
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
     6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
    16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
    26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
    36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
    46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
    56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
    66,    67,    68,    69,    70,    71,    72,    73,    74
};

#if YYDEBUG != 0
static const short yyprhs[] = {     0,
     0,     2,     5,     8,    11,    14,    17,    20,    22,    24,
    29,    35,    38,    42,    45,    50,    53,    58,    64,    71,
    73,    77,    83,    85,    87,    89,    91,    93,    95,    97,
    99,   103,   105,   109,   111,   115,   117,   121,   125,   127,
   131,   135,   137,   141,   145,   149,   152,   154,   156,   158,
   160,   162,   164,   168,   170,   172,   174,   176,   178,   180,
   182,   185,   187,   189,   191,   194,   196,   198,   200,   202,
   204,   206,   208,   210,   212,   214,   216,   218,   220,   222,
   224,   226,   228,   230,   232,   234,   236,   238,   243,   250,
   252,   254,   256,   258,   260,   262,   264,   266,   268,   270,
   274,   276,   278,   280,   282,   284,   286,   288,   290,   292,
   294,   296,   298,   300,   302,   305,   308,   310,   312,   314,
   316,   322,   324,   327,   330,   340,   342,   344,   346,   348,
   350,   352,   355,   358,   360,   363,   367,   370,   373,   379,
   381,   385,   387,   394,   399,   401,   403,   408,   410,   413,
   415,   418,   422,   425,   429,   434,   436,   439,   442,   445,
   447,   451,   453,   457,   459,   463,   465,   467,   470,   474,
   476,   479,   482,   485,   488,   491,   494,   497,   502,   508,
   512,   517,   519,   521,   523,   525,   531,   533,   536,   540,
   544,   550,   555,   560,   565,   572,   578,   584,   590,   595,
   597,   599,   601,   605,   607,   611,   615,   617,   619,   621,
   626,   631,   633,   637,   639
};

static const short yyrhs[] = {    82,
     0,    82,    81,     0,   106,     3,     0,   172,     3,     0,
    83,     3,     0,    85,     3,     0,    88,     3,     0,    84,
     0,    86,     0,    87,     6,   163,     7,     0,    73,    72,
     6,    81,     7,     0,    22,    72,     0,    83,    72,    90,
     0,    83,    72,     0,    89,     6,   163,     7,     0,    15,
    72,     0,    15,    72,    16,   162,     0,    15,    72,    16,
   162,    90,     0,    15,    72,    16,   162,    90,   155,     0,
   162,     0,   162,     9,    90,     0,     8,    92,    72,    10,
    93,     0,   125,     0,   132,     0,   133,     0,   124,     0,
   151,     0,   162,     0,    94,     0,    95,     0,    94,    18,
    95,     0,    96,     0,    95,    17,    96,     0,    97,     0,
    96,    19,    97,     0,    98,     0,    97,    20,    98,     0,
    97,    21,    98,     0,    99,     0,    98,    75,    99,     0,
    98,    76,    99,     0,   100,     0,    99,    77,   100,     0,
    99,    78,   100,     0,    99,    79,   100,     0,   101,   102,
     0,   102,     0,    76,     0,    75,     0,    80,     0,   162,
     0,   103,     0,    13,    93,    14,     0,    70,     0,    71,
     0,    74,     0,   104,     0,    62,     0,    63,     0,    93,
     0,    61,   107,     0,   136,     0,   139,     0,   146,     0,
   108,   120,     0,   109,     0,   119,     0,   110,     0,   115,
     0,   162,     0,   124,     0,   125,     0,   132,     0,   133,
     0,   134,     0,   135,     0,   111,     0,   112,     0,   113,
     0,   114,     0,    58,     0,    57,     0,    48,     0,    59,
     0,   149,     0,   151,     0,   116,     0,   117,    46,   109,
    47,     0,    43,    46,   109,     9,   109,    47,     0,    40,
     0,    41,     0,    42,     0,    40,     0,    41,     0,    42,
     0,   136,     0,   139,     0,   146,     0,   121,     0,   121,
     9,   120,     0,   122,     0,   123,     0,    72,     0,   152,
     0,    53,     0,    54,     0,   127,     0,   126,     0,   130,
     0,   131,     0,   128,     0,   129,     0,    49,     0,    50,
     0,    51,    49,     0,    51,    50,     0,    64,     0,    60,
     0,    55,     0,    65,     0,    33,    72,     6,   137,     7,
     0,   138,     0,   138,   137,     0,   108,   120,     0,    34,
    72,    35,    13,   140,    14,     6,   141,     7,     0,   125,
     0,   132,     0,   133,     0,   146,     0,   162,     0,   142,
     0,   142,   141,     0,   143,   145,     0,   144,     0,   144,
   143,     0,    66,    93,     5,     0,    67,     5,     0,   108,
   121,     0,    68,    72,     6,   147,     6,     0,   148,     0,
   148,     9,   147,     0,    72,     0,   150,    46,   109,     9,
   105,    47,     0,   150,    46,   109,    47,     0,    44,     0,
    45,     0,    56,    46,   105,    47,     0,    56,     0,    72,
   153,     0,   154,     0,   154,   153,     0,    11,   105,    12,
     0,    13,    14,     0,    13,   156,    14,     0,    13,   156,
   157,    14,     0,    64,     0,    69,    70,     0,    38,   158,
     0,    39,   158,     0,   159,     0,   159,     9,   158,     0,
   161,     0,    13,   160,    14,     0,   161,     0,   161,     9,
   160,     0,    72,     0,    72,     0,     4,    72,     0,   162,
     4,    72,     0,   164,     0,   164,   163,     0,   106,     3,
     0,    91,     3,     0,   172,     3,     0,   165,     3,     0,
   168,     3,     0,   171,     3,     0,    37,   167,   166,   154,
     0,    36,    37,   167,   166,   154,     0,    37,   167,   166,
     0,    36,    37,   167,   166,     0,    70,     0,   109,     0,
   136,     0,   146,     0,    28,   169,    72,    29,   170,     0,
    72,     0,   118,    72,     0,    72,     4,    72,     0,   174,
    72,   175,     0,   174,    72,   175,   179,   180,     0,   174,
    72,   175,   180,     0,   174,    72,   175,   179,     0,   173,
   174,    72,   175,     0,   173,   174,    72,   175,   179,   180,
     0,   173,   174,    72,   175,   180,     0,   173,   174,    72,
   175,   179,     0,    32,    72,     6,   137,     6,     0,    32,
    72,     6,     6,     0,    30,     0,   109,     0,    27,     0,
    13,   176,    14,     0,   177,     0,   177,     9,   176,     0,
   178,   109,   121,     0,    24,     0,    25,     0,    26,     0,
    31,    13,   181,    14,     0,    23,    13,   182,    14,     0,
   162,     0,   162,     9,   181,     0,    70,     0,    70,     9,
   182,     0
};

#endif

#if YYDEBUG != 0
static const short yyrline[] = { 0,
    69,    71,    73,    75,    76,    77,    78,    81,    83,    86,
    91,    95,    99,   101,   104,   109,   111,   112,   113,   116,
   118,   121,   125,   126,   127,   128,   129,   130,   133,   137,
   139,   142,   144,   147,   149,   152,   154,   155,   158,   160,
   161,   164,   166,   167,   168,   171,   173,   176,   178,   179,
   182,   184,   185,   189,   191,   192,   193,   196,   197,   200,
   203,   205,   206,   207,   210,   215,   217,   220,   222,   223,
   226,   228,   229,   230,   231,   232,   233,   234,   235,   236,
   239,   242,   245,   248,   252,   254,   255,   259,   261,   265,
   267,   268,   271,   273,   274,   277,   279,   280,   283,   285,
   287,   289,   292,   296,   300,   302,   305,   307,   309,   311,
   314,   315,   318,   322,   326,   330,   335,   339,   343,   347,
   351,   355,   357,   360,   365,   368,   370,   371,   372,   373,
   376,   378,   381,   385,   387,   390,   392,   395,   400,   404,
   406,   409,   413,   415,   418,   420,   422,   424,   427,   431,
   433,   436,   440,   442,   443,   446,   449,   453,   455,   458,
   460,   463,   465,   468,   470,   473,   477,   479,   480,   483,
   485,   488,   490,   491,   492,   493,   494,   498,   500,   501,
   502,   505,   507,   509,   510,   513,   517,   519,   522,   526,
   528,   529,   530,   532,   533,   535,   536,   539,   541,   544,
   547,   549,   552,   555,   557,   560,   563,   565,   566,   569,
   573,   577,   579,   582,   584
};
#endif


#if YYDEBUG != 0 || defined (YYERROR_VERBOSE)

static const char * const yytname[] = {   "$","error","$undefined.","SEMICOLON",
"DBLCOLON","COLON","OPCURLBRKT","CLCURLBRKT","CONST","COMMA","EQUALS","OPSQBRKT",
"CLSQBRKT","OPPAREN","CLPAREN","CLASS","EXTENDS","XOR_OP","OR_OP","AND_OP","SHRITE_OP",
"SHLEFT_OP","INTERFACE","CONTEXT","IN","OUT","INOUT","VOID","RELATIONSHIP","INVERSE",
"ONEWAY","RAISES","EXCEPTION","STRUCT","UNION","SWITCH","READONLY","ATTRIBUTE",
"KEY","KEYS","SET","LIST","BAG","DICTIONARY","ARRAY","SEQUENCE","LESSTHAN","GREATERTHAN",
"INTERVAL","LONG","SHORT","UNSIGNED","INT","FLOAT","DOUBLE","OCTET","STRING",
"TIME","DATE","TIMESTAMP","BOOLEAN","TYPEDEF","TRUE","FALSE","CHAR","ANY","CASE",
"DEFAULT","ENUM","EXTENT","STRING_LITERAL","CHARACTER_LITERAL","IDENTIFIER",
"MODULE","FLOATING_PT_LITERAL","'+'","'-'","'*'","'/'","'%'","'~'","specification",
"definition","interface","interface_decl","module","forward_decl","interface_header",
"class","class_header","inheritance_spec","const_dcl","const_type","const_expr",
"or_expr","xor_expr","and_expr","shift_expr","add_expr","mult_expr","unary_expr",
"unary_operator","primary_expr","literal","boolean_literal","positive_int_const",
"type_dcl","type_declarator","type_spec","simple_type_spec","base_type_spec",
"date_type","time_type","interval_type","timestamp_type","template_type_spec",
"coll_type","coll_spec","rel_collection_type","constr_type_spec","declarators",
"declarator","simple_declarator","complex_declarator","floating_pt_type","integer_type",
"unsigned_int","signed_int","signed_long_int","signed_short_int","unsigned_long_int",
"unsigned_short_int","char_type","boolean_type","octet_type","any_type","struct_type",
"member_list","member","union_type","switch_type_spec","switch_body","case",
"case_label_list","case_label","element_spec","enum_type","enumerator_list",
"enumerator","array_type","array_spec","string_type","array_declarator","array_size_list",
"fixed_array_size","type_property_list","extent_spec","key_spec","key_list",
"key","property_list","property_name","scoped_name","interface_body","export",
"attr_dcl","attribute_name","domain_type","rel_dcl","target_of_path","inverse_traversal_path",
"op_dcl","except_dcl","op_attribute","op_type_spec","paramater_dcls","param_dcl_list",
"param_dcl","param_attribute","raises_expr","context_expr","scoped_name_list",
"string_literal_list", NULL
};
#endif

static const short yyr1[] = {     0,
    81,    81,    82,    82,    82,    82,    82,    83,    83,    84,
    85,    86,    87,    87,    88,    89,    89,    89,    89,    90,
    90,    91,    92,    92,    92,    92,    92,    92,    93,    94,
    94,    95,    95,    96,    96,    97,    97,    97,    98,    98,
    98,    99,    99,    99,    99,   100,   100,   101,   101,   101,
   102,   102,   102,   103,   103,   103,   103,   104,   104,   105,
   106,   106,   106,   106,   107,   108,   108,   109,   109,   109,
   110,   110,   110,   110,   110,   110,   110,   110,   110,   110,
   111,   112,   113,   114,   115,   115,   115,   116,   116,   117,
   117,   117,   118,   118,   118,   119,   119,   119,   120,   120,
   121,   121,   122,   123,   124,   124,   125,   125,   126,   126,
   127,   127,   128,   129,   130,   131,   132,   133,   134,   135,
   136,   137,   137,   138,   139,   140,   140,   140,   140,   140,
   141,   141,   142,   143,   143,   144,   144,   145,   146,   147,
   147,   148,   149,   149,   150,   150,   151,   151,   152,   153,
   153,   154,   155,   155,   155,   132,   156,   157,   157,   158,
   158,   159,   159,   160,   160,   161,   162,   162,   162,   163,
   163,   164,   164,   164,   164,   164,   164,   165,   165,   165,
   165,   166,   167,   167,   167,   168,   169,   169,   170,   171,
   171,   171,   171,   171,   171,   171,   171,   172,   172,   173,
   174,   174,   175,   176,   176,   177,   178,   178,   178,   179,
   180,   181,   181,   182,   182
};

static const short yyr2[] = {     0,
     1,     2,     2,     2,     2,     2,     2,     1,     1,     4,
     5,     2,     3,     2,     4,     2,     4,     5,     6,     1,
     3,     5,     1,     1,     1,     1,     1,     1,     1,     1,
     3,     1,     3,     1,     3,     1,     3,     3,     1,     3,
     3,     1,     3,     3,     3,     2,     1,     1,     1,     1,
     1,     1,     3,     1,     1,     1,     1,     1,     1,     1,
     2,     1,     1,     1,     2,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     4,     6,     1,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     2,     2,     1,     1,     1,     1,
     5,     1,     2,     2,     9,     1,     1,     1,     1,     1,
     1,     2,     2,     1,     2,     3,     2,     2,     5,     1,
     3,     1,     6,     4,     1,     1,     4,     1,     2,     1,
     2,     3,     2,     3,     4,     1,     2,     2,     2,     1,
     3,     1,     3,     1,     3,     1,     1,     2,     3,     1,
     2,     2,     2,     2,     2,     2,     2,     4,     5,     3,
     4,     1,     1,     1,     1,     5,     1,     2,     3,     3,
     5,     4,     4,     4,     6,     5,     5,     5,     4,     1,
     1,     1,     3,     1,     3,     3,     1,     1,     1,     4,
     4,     1,     3,     1,     3
};

static const short yydefact[] = {     0,
     0,     0,     0,     0,     0,     0,     0,     0,     1,     0,
     8,     0,     9,     0,     0,     0,     0,    62,    63,    64,
     0,    16,    12,     0,     0,     0,     0,    90,    91,    92,
     0,   145,   146,    83,   113,   114,     0,   105,   106,   119,
   148,    82,    81,    84,   118,   117,   120,   167,    61,     0,
    66,    68,    77,    78,    79,    80,    69,    87,     0,    67,
    71,    72,   108,   107,   111,   112,   109,   110,    73,    74,
    75,    76,    96,    97,    98,    85,     0,    86,    70,     0,
     0,     2,     5,    14,     6,     0,     7,     0,     3,     4,
     0,     0,     0,     0,   168,     0,   115,   116,     0,   103,
    65,    99,   101,   102,   104,     0,     0,     0,     0,     0,
    13,    20,     0,   202,     0,   200,     0,     0,     0,     0,
   201,     0,   170,     0,     0,     0,     0,     0,     0,     0,
    17,   199,     0,     0,   122,     0,     0,     0,     0,    58,
    59,    54,    55,    56,    49,    48,    50,    60,    29,    30,
    32,    34,    36,    39,    42,     0,    47,    52,    57,     0,
    51,     0,   149,   150,     0,     0,     0,   169,   142,     0,
   140,     0,     0,     0,    26,    23,    24,    25,    27,    28,
    93,    94,    95,   187,     0,     0,     0,   183,   184,   185,
     0,   173,   172,    10,   171,   175,   176,   177,   174,     0,
     0,    15,     0,    18,   124,   198,   123,   121,   126,   127,
   128,     0,   129,   130,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,    46,   147,     0,   151,
   100,    88,     0,   144,   139,     0,    11,    21,     0,   188,
     0,     0,   182,   180,     0,     0,   190,   168,     0,    19,
     0,     0,    53,    31,    33,    35,    37,    38,    40,    41,
    43,    44,    45,   152,     0,   141,     0,     0,   181,   178,
   194,   207,   208,   209,     0,   204,     0,     0,     0,   193,
   192,   153,     0,     0,     0,    89,   143,    22,     0,   186,
   179,   197,   196,   203,     0,     0,     0,     0,   191,   157,
   154,     0,     0,     0,     0,     0,     0,   131,     0,   134,
     0,   195,   205,   206,   214,     0,   212,     0,     0,   166,
   158,   160,   162,   159,   155,     0,   137,   125,   132,     0,
   133,   135,   189,     0,   211,     0,   210,     0,   164,     0,
   136,   138,   215,   213,   163,     0,   161,   165,     0,     0,
     0
};

static const short yydefgoto[] = {    82,
     9,    10,    11,    12,    13,    14,    15,    16,   111,   119,
   174,   148,   149,   150,   151,   152,   153,   154,   155,   156,
   157,   158,   159,   160,    17,    49,   133,    51,    52,    53,
    54,    55,    56,    57,    58,    59,   185,    60,   101,   102,
   103,   104,    61,    62,    63,    64,    65,    66,    67,    68,
    69,    70,    71,    72,    18,   134,   135,    19,   212,   307,
   308,   309,   310,   331,    20,   170,   171,    76,    77,    78,
   105,   163,   164,   250,   284,   304,   321,   322,   338,   323,
   161,   122,   123,   124,   244,   191,   125,   186,   290,   126,
    21,   128,   129,   247,   275,   276,   277,   280,   281,   318,
   316
};

static const short yypact[] = {    -1,
   -29,   -21,   -11,    47,    64,   316,    67,    72,    -1,     9,
-32768,    99,-32768,   110,   160,   166,   163,-32768,-32768,-32768,
   172,   164,-32768,   173,   176,   141,   111,-32768,-32768,-32768,
   138,-32768,-32768,-32768,-32768,-32768,    27,-32768,-32768,-32768,
   139,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,   114,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,   142,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,   143,-32768,   187,   186,
   189,-32768,-32768,    11,-32768,   170,-32768,   170,-32768,-32768,
    11,   283,   316,   180,-32768,   383,-32768,-32768,    71,   185,
-32768,   190,-32768,-32768,-32768,   383,   383,   129,   133,    -1,
-32768,    35,   246,-32768,    -4,-32768,   179,   204,   214,   219,
-32768,   225,   170,   230,   233,   236,   237,   350,   169,   244,
    16,-32768,   114,   250,   316,   258,   105,   234,    71,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,   248,   253,
   254,    33,    30,    49,-32768,    90,-32768,-32768,-32768,   220,
   187,    71,-32768,   185,   114,   227,    10,-32768,-32768,   269,
   268,   271,    11,   207,-32768,-32768,-32768,-32768,-32768,   187,
-32768,-32768,-32768,-32768,   208,   209,   204,-32768,-32768,-32768,
   212,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,   211,
   272,-32768,   216,   273,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,   270,-32768,   187,   383,   276,    71,    71,    71,    71,
    71,    71,    71,    71,    71,    71,-32768,-32768,   279,-32768,
-32768,-32768,    71,-32768,-32768,   133,-32768,-32768,   284,-32768,
   264,   212,-32768,   185,   272,   124,    18,   226,    -7,-32768,
   295,   260,-32768,   253,   254,    33,    30,    30,    49,    49,
-32768,-32768,-32768,-32768,   261,-32768,    71,   239,   185,-32768,
    18,-32768,-32768,-32768,   291,   304,   383,   302,   306,   298,
-32768,-32768,   252,    32,    44,-32768,-32768,-32768,   325,-32768,
-32768,   298,-32768,-32768,   124,   114,   265,    11,-32768,-32768,
-32768,    -3,    -3,   330,    71,   340,   339,    44,   316,    44,
   280,-32768,-32768,-32768,   344,   348,    38,   349,   296,-32768,
-32768,   369,-32768,-32768,-32768,   374,-32768,-32768,-32768,   114,
-32768,-32768,-32768,   265,-32768,    11,-32768,   368,   376,    -3,
-32768,-32768,-32768,-32768,-32768,   296,-32768,-32768,   386,   389,
-32768
};

static const short yypgoto[] = {     4,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,  -115,-32768,
-32768,  -137,-32768,   194,   165,   177,   -97,   -52,   -67,-32768,
   241,-32768,-32768,  -154,   -60,-32768,    -5,   -83,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,   -99,  -274,
-32768,-32768,   289,   -63,-32768,-32768,-32768,-32768,-32768,-32768,
   -24,   -22,-32768,-32768,     3,   -76,-32768,     5,-32768,   104,
-32768,   103,-32768,-32768,     0,   181,-32768,-32768,-32768,   303,
-32768,   255,  -196,-32768,-32768,-32768,  -285,-32768,    74,  -294,
    -6,   -58,-32768,-32768,   188,   231,-32768,-32768,-32768,-32768,
   -59,-32768,   293,   184,   140,-32768,-32768,   174,  -172,   108,
   112
};


#define	YYLAST		455


static const short yytable[] = {    79,
    50,   216,   121,   349,   121,    75,   282,   229,    73,   319,
    74,    83,   138,     1,    27,   204,   136,   324,   233,   203,
     2,   314,   166,   167,   339,   120,   127,   120,   127,   130,
     3,     4,     5,   205,   188,   181,   182,   183,   108,   121,
   278,   108,    22,   173,   121,   301,   336,   270,   279,   176,
    23,   339,   220,   221,   347,   342,   234,   238,   207,     6,
    24,   283,   120,   127,   195,   231,     7,   184,   320,   302,
   303,     8,   291,   209,    27,    97,    98,   112,   265,    79,
    84,    79,    48,   139,   131,    79,    79,    48,   177,    79,
   178,    75,    75,    27,    73,    73,    74,    74,   293,    79,
    79,    85,   139,   188,   222,   223,   180,   299,    27,   305,
   306,    79,   210,   172,   211,    86,    79,   190,    25,   312,
   189,    79,   257,   258,   112,   224,   225,   226,    79,   288,
   214,   252,   140,   141,    75,    26,   213,    73,    80,    74,
   142,   143,    48,    81,   144,   145,   146,   272,   273,   274,
   147,   140,   141,    35,    36,    37,   261,   262,   263,   142,
   143,    48,    87,   144,    45,    89,   112,   326,    46,   259,
   260,    88,     7,    27,    90,    94,    48,   113,    92,    91,
    79,    93,    95,    96,    99,   100,   190,   106,   107,   189,
   108,   109,   137,   296,   110,   162,   114,   115,   165,   116,
   168,     3,     4,     5,   169,   117,   118,    27,    79,    28,
    29,    30,    31,    32,    33,   187,   192,    34,    35,    36,
    37,   193,    38,    39,    40,    41,    42,    43,    44,    45,
     6,   194,   196,    46,    47,   197,     4,     7,   198,   199,
   201,    48,   215,    28,    29,    30,    31,    32,    33,    27,
   202,    34,    35,    36,    37,   206,    38,    39,    40,    41,
    42,    43,    44,    45,   208,   217,   228,    46,    47,   218,
    79,     7,   219,   232,   235,    48,   236,   237,   239,   240,
   241,   243,   245,   251,   246,   249,    27,   248,   132,   253,
   264,   317,   268,   267,    35,    36,    37,  -169,    38,    39,
   285,    41,    79,   330,   294,    45,   286,   287,    75,    46,
   289,    73,   295,    74,   297,     4,     5,    48,   298,    27,
   278,   300,    28,    29,    30,    31,    32,    33,   311,   317,
    34,    35,    36,    37,   315,    38,    39,    40,    41,    42,
    43,    44,    45,   325,   327,   328,    46,    47,     4,     5,
     7,   333,   334,    27,    48,    28,    29,    30,    31,    32,
    33,   335,   337,    34,    35,    36,    37,   320,    38,    39,
    40,    41,    42,    43,    44,    45,   114,   340,   341,    46,
    47,   345,   255,     7,   346,   350,    27,    48,   351,    28,
    29,    30,    31,    32,    33,   256,   227,    34,    35,    36,
    37,   175,    38,    39,    40,    41,    42,    43,    44,    45,
   254,   329,   332,    46,    47,   179,   266,   242,   230,   348,
   200,    48,    28,    29,    30,    31,    32,    33,   271,   269,
    34,    35,    36,    37,   313,    38,    39,    40,    41,    42,
    43,    44,    45,   344,   292,   343,    46,    47,     0,     0,
     0,     0,     0,     0,    48
};

static const short yycheck[] = {     6,
     6,   139,    86,     0,    88,     6,    14,   162,     6,    13,
     6,     3,    96,    15,     4,   131,    93,   303,     9,     4,
    22,   296,   106,   107,   319,    86,    86,    88,    88,    88,
    32,    33,    34,   133,   118,    40,    41,    42,     4,   123,
    23,     4,    72,     9,   128,    14,     9,   244,    31,   113,
    72,   346,    20,    21,   340,   330,    47,   173,   135,    61,
    72,    69,   123,   123,   123,   165,    68,    72,    72,    38,
    39,    73,   269,   137,     4,    49,    50,    84,   233,    86,
    72,    88,    72,    13,    91,    92,    93,    72,   113,    96,
   113,    92,    93,     4,    92,    93,    92,    93,   271,   106,
   107,     3,    13,   187,    75,    76,   113,   280,     4,    66,
    67,   118,   137,   110,   137,     6,   123,   118,    72,   292,
   118,   128,   220,   221,   131,    77,    78,    79,   135,   267,
   137,   215,    62,    63,   135,    72,   137,   135,    72,   135,
    70,    71,    72,    72,    74,    75,    76,    24,    25,    26,
    80,    62,    63,    49,    50,    51,   224,   225,   226,    70,
    71,    72,     3,    74,    60,     3,   173,   305,    64,   222,
   223,     6,    68,     4,     3,    35,    72,     8,     6,    16,
   187,     6,    72,    46,    46,    72,   187,    46,    46,   187,
     4,     6,    13,   277,     6,    11,    27,    28,     9,    30,
    72,    32,    33,    34,    72,    36,    37,     4,   215,    40,
    41,    42,    43,    44,    45,    37,     3,    48,    49,    50,
    51,     3,    53,    54,    55,    56,    57,    58,    59,    60,
    61,     7,     3,    64,    65,     3,    33,    68,     3,     3,
    72,    72,     9,    40,    41,    42,    43,    44,    45,     4,
     7,    48,    49,    50,    51,     6,    53,    54,    55,    56,
    57,    58,    59,    60,     7,    18,    47,    64,    65,    17,
   277,    68,    19,    47,     6,    72,     9,     7,    72,    72,
    72,    70,    72,    14,    13,    13,     4,    72,     6,    14,
    12,   298,    29,    10,    49,    50,    51,    72,    53,    54,
     6,    56,   309,   309,    14,    60,    47,    47,   309,    64,
    72,   309,     9,   309,    13,    33,    34,    72,    13,     4,
    23,    70,    40,    41,    42,    43,    44,    45,     4,   336,
    48,    49,    50,    51,    70,    53,    54,    55,    56,    57,
    58,    59,    60,    14,     5,     7,    64,    65,    33,    34,
    68,    72,     9,     4,    72,    40,    41,    42,    43,    44,
    45,    14,    14,    48,    49,    50,    51,    72,    53,    54,
    55,    56,    57,    58,    59,    60,    27,     9,     5,    64,
    65,    14,   218,    68,     9,     0,     4,    72,     0,    40,
    41,    42,    43,    44,    45,   219,   156,    48,    49,    50,
    51,   113,    53,    54,    55,    56,    57,    58,    59,    60,
   217,   308,   310,    64,    65,   113,   236,   187,   164,   346,
   128,    72,    40,    41,    42,    43,    44,    45,   245,   242,
    48,    49,    50,    51,   295,    53,    54,    55,    56,    57,
    58,    59,    60,   336,   271,   334,    64,    65,    -1,    -1,
    -1,    -1,    -1,    -1,    72
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

case 11:
#line 93 "odl.y"
{ yyval.nextP=(DATATYPEP)malloc ( DATASIZE); ;
    break;}
case 12:
#line 97 "odl.y"
{ yyval.nextP=(DATATYPEP)malloc ( DATASIZE); ;
    break;}
case 13:
#line 100 "odl.y"
{ yyval.nextP=(DATATYPEP)malloc ( DATASIZE); ;
    break;}
case 14:
#line 101 "odl.y"
{ yyval.nextP=(DATATYPEP)malloc ( DATASIZE); ;
    break;}
case 15:
#line 106 "odl.y"
{ yyval.nextP=(DATATYPEP)malloc ( DATASIZE); ;
    break;}
case 23:
#line 125 "odl.y"
{ yyval.nextP=(DATATYPEP)malloc ( DATASIZE); ;
    break;}
case 24:
#line 126 "odl.y"
{ yyval.nextP=(DATATYPEP)malloc ( DATASIZE); ;
    break;}
case 25:
#line 127 "odl.y"
{ yyval.nextP=(DATATYPEP)malloc ( DATASIZE); ;
    break;}
case 26:
#line 128 "odl.y"
{ yyval.nextP=(DATATYPEP)malloc ( DATASIZE); ;
    break;}
case 27:
#line 129 "odl.y"
{ yyval.nextP=(DATATYPEP)malloc ( DATASIZE); ;
    break;}
case 28:
#line 130 "odl.y"
{ yyval.nextP=(DATATYPEP)malloc ( DATASIZE); ;
    break;}
case 48:
#line 177 "odl.y"
{ yyval.nextP=(DATATYPEP)malloc ( DATASIZE); ;
    break;}
case 49:
#line 178 "odl.y"
{ yyval.nextP=(DATATYPEP)malloc ( DATASIZE); ;
    break;}
case 50:
#line 179 "odl.y"
{ yyval.nextP=(DATATYPEP)malloc ( DATASIZE); ;
    break;}
case 52:
#line 184 "odl.y"
{ yyval.nextP=(DATATYPEP)malloc ( DATASIZE); ;
    break;}
case 53:
#line 186 "odl.y"
{ yyval.nextP=(DATATYPEP)malloc ( DATASIZE); ;
    break;}
case 60:
#line 200 "odl.y"
{ yyval.nextP=(DATATYPEP)malloc ( DATASIZE); ;
    break;}
case 61:
#line 204 "odl.y"
{ yyval.nextP=(DATATYPEP)malloc ( DATASIZE); ;
    break;}
case 62:
#line 205 "odl.y"
{ yyval.nextP=(DATATYPEP)malloc ( DATASIZE); ;
    break;}
case 63:
#line 206 "odl.y"
{ yyval.nextP=(DATATYPEP)malloc ( DATASIZE); ;
    break;}
case 64:
#line 207 "odl.y"
{ yyval.nextP=(DATATYPEP)malloc ( DATASIZE); ;
    break;}
case 65:
#line 212 "odl.y"
{ yyval.nextP=(DATATYPEP)malloc ( DATASIZE); ;
    break;}
case 67:
#line 217 "odl.y"
{ yyval.nextP=(DATATYPEP)malloc ( DATASIZE); ;
    break;}
case 70:
#line 223 "odl.y"
{ yyval.nextP=(DATATYPEP)malloc ( DATASIZE); ;
    break;}
case 72:
#line 228 "odl.y"
{ yyval.nextP=(DATATYPEP)malloc ( DATASIZE); ;
    break;}
case 73:
#line 229 "odl.y"
{ yyval.nextP=(DATATYPEP)malloc ( DATASIZE); ;
    break;}
case 74:
#line 230 "odl.y"
{ yyval.nextP=(DATATYPEP)malloc ( DATASIZE); ;
    break;}
case 75:
#line 231 "odl.y"
{ yyval.nextP=(DATATYPEP)malloc ( DATASIZE); ;
    break;}
case 76:
#line 232 "odl.y"
{ yyval.nextP=(DATATYPEP)malloc ( DATASIZE); ;
    break;}
case 77:
#line 233 "odl.y"
{ yyval.nextP=(DATATYPEP)malloc ( DATASIZE); ;
    break;}
case 78:
#line 234 "odl.y"
{ yyval.nextP=(DATATYPEP)malloc ( DATASIZE); ;
    break;}
case 79:
#line 235 "odl.y"
{ yyval.nextP=(DATATYPEP)malloc ( DATASIZE); ;
    break;}
case 80:
#line 236 "odl.y"
{ yyval.nextP=(DATATYPEP)malloc ( DATASIZE); ;
    break;}
case 85:
#line 253 "odl.y"
{ yyval.nextP=(DATATYPEP)malloc ( DATASIZE); ;
    break;}
case 86:
#line 254 "odl.y"
{ yyval.nextP=(DATATYPEP)malloc ( DATASIZE); ;
    break;}
case 87:
#line 256 "odl.y"
{ yyval.nextP=(DATATYPEP)malloc ( DATASIZE); ;
    break;}
case 88:
#line 260 "odl.y"
{ yyval.nextP=(DATATYPEP)malloc ( DATASIZE); ;
    break;}
case 89:
#line 262 "odl.y"
{ yyval.nextP=(DATATYPEP)malloc ( DATASIZE); ;
    break;}
case 90:
#line 266 "odl.y"
{ yyval.nextP=(DATATYPEP)malloc ( DATASIZE); ;
    break;}
case 91:
#line 267 "odl.y"
{ yyval.nextP=(DATATYPEP)malloc ( DATASIZE); ;
    break;}
case 92:
#line 268 "odl.y"
{ yyval.nextP=(DATATYPEP)malloc ( DATASIZE); ;
    break;}
case 93:
#line 272 "odl.y"
{ yyval.nextP=(DATATYPEP)malloc ( DATASIZE); ;
    break;}
case 94:
#line 273 "odl.y"
{ yyval.nextP=(DATATYPEP)malloc ( DATASIZE); ;
    break;}
case 95:
#line 274 "odl.y"
{ yyval.nextP=(DATATYPEP)malloc ( DATASIZE); ;
    break;}
case 105:
#line 301 "odl.y"
{ yyval.nextP=(DATATYPEP)malloc ( DATASIZE); ;
    break;}
case 106:
#line 302 "odl.y"
{ yyval.nextP=(DATATYPEP)malloc ( DATASIZE); ;
    break;}
case 108:
#line 307 "odl.y"
{ yyval.nextP=(DATATYPEP)malloc ( DATASIZE); ;
    break;}
case 109:
#line 310 "odl.y"
{ yyval.nextP=(DATATYPEP)malloc ( DATASIZE); ;
    break;}
case 110:
#line 311 "odl.y"
{ yyval.nextP=(DATATYPEP)malloc ( DATASIZE); ;
    break;}
case 112:
#line 315 "odl.y"
{ yyval.nextP=(DATATYPEP)malloc ( DATASIZE); ;
    break;}
case 113:
#line 319 "odl.y"
{ yyval.nextP=(DATATYPEP)malloc ( DATASIZE); ;
    break;}
case 116:
#line 332 "odl.y"
{ yyval.nextP=(DATATYPEP)malloc ( DATASIZE); ;
    break;}
case 117:
#line 336 "odl.y"
{ yyval.nextP=(DATATYPEP)malloc ( DATASIZE); ;
    break;}
case 118:
#line 340 "odl.y"
{ yyval.nextP=(DATATYPEP)malloc ( DATASIZE); ;
    break;}
case 123:
#line 358 "odl.y"
{ yyval.nextP=(DATATYPEP)malloc ( DATASIZE); ;
    break;}
case 124:
#line 362 "odl.y"
{ yyval.nextP=(DATATYPEP)malloc ( DATASIZE); ;
    break;}
case 128:
#line 371 "odl.y"
{ yyval.nextP=(DATATYPEP)malloc ( DATASIZE); ;
    break;}
case 129:
#line 372 "odl.y"
{ yyval.nextP=(DATATYPEP)malloc ( DATASIZE); ;
    break;}
case 130:
#line 373 "odl.y"
{ yyval.nextP=(DATATYPEP)malloc ( DATASIZE); ;
    break;}
case 138:
#line 397 "odl.y"
{ yyval.nextP=(DATATYPEP)malloc ( DATASIZE); ;
    break;}
case 147:
#line 423 "odl.y"
{ yyval.nextP=(DATATYPEP)malloc ( DATASIZE); ;
    break;}
case 148:
#line 424 "odl.y"
{ yyval.nextP=(DATATYPEP)malloc ( DATASIZE); ;
    break;}
case 153:
#line 441 "odl.y"
{ yyval.nextP=(DATATYPEP)malloc ( DATASIZE); ;
    break;}
case 154:
#line 442 "odl.y"
{ yyval.nextP=(DATATYPEP)malloc ( DATASIZE); ;
    break;}
case 155:
#line 443 "odl.y"
{ yyval.nextP=(DATATYPEP)malloc ( DATASIZE); ;
    break;}
case 156:
#line 446 "odl.y"
{ yyval.nextP=(DATATYPEP)malloc ( DATASIZE); ;
    break;}
case 158:
#line 454 "odl.y"
{ yyval.nextP=(DATATYPEP)malloc ( DATASIZE); ;
    break;}
case 159:
#line 455 "odl.y"
{ yyval.nextP=(DATATYPEP)malloc ( DATASIZE); ;
    break;}
case 167:
#line 478 "odl.y"
{ yyval.nextP=(DATATYPEP)malloc ( DATASIZE); ;
    break;}
case 168:
#line 479 "odl.y"
{ yyval.nextP=(DATATYPEP)malloc ( DATASIZE); ;
    break;}
case 169:
#line 480 "odl.y"
{ yyval.nextP=(DATATYPEP)malloc ( DATASIZE); ;
    break;}
case 170:
#line 484 "odl.y"
{ yyval.nextP=(DATATYPEP)malloc ( DATASIZE); ;
    break;}
case 171:
#line 485 "odl.y"
{ yyval.nextP=(DATATYPEP)malloc ( DATASIZE); ;
    break;}
case 173:
#line 490 "odl.y"
{ yyval.nextP=(DATATYPEP)malloc ( DATASIZE); ;
    break;}
case 175:
#line 492 "odl.y"
{ yyval.nextP=(DATATYPEP)malloc ( DATASIZE); ;
    break;}
case 176:
#line 493 "odl.y"
{ yyval.nextP=(DATATYPEP)malloc ( DATASIZE); ;
    break;}
case 177:
#line 494 "odl.y"
{ yyval.nextP=(DATATYPEP)malloc ( DATASIZE); ;
    break;}
case 182:
#line 505 "odl.y"
{ yyval.nextP=(DATATYPEP)malloc ( DATASIZE); ;
    break;}
case 183:
#line 508 "odl.y"
{ yyval.nextP=(DATATYPEP)malloc ( DATASIZE); ;
    break;}
case 184:
#line 509 "odl.y"
{ yyval.nextP=(DATATYPEP)malloc ( DATASIZE); ;
    break;}
case 185:
#line 510 "odl.y"
{ yyval.nextP=(DATATYPEP)malloc ( DATASIZE); ;
    break;}
case 187:
#line 518 "odl.y"
{ yyval.nextP=(DATATYPEP)malloc ( DATASIZE); ;
    break;}
case 188:
#line 519 "odl.y"
{ yyval.nextP=(DATATYPEP)malloc ( DATASIZE); ;
    break;}
case 189:
#line 523 "odl.y"
{ yyval.nextP=(DATATYPEP)malloc ( DATASIZE); ;
    break;}
case 191:
#line 528 "odl.y"
{ yyval.nextP=(DATATYPEP)malloc ( DATASIZE); ;
    break;}
case 192:
#line 529 "odl.y"
{ yyval.nextP=(DATATYPEP)malloc ( DATASIZE); ;
    break;}
case 193:
#line 530 "odl.y"
{ yyval.nextP=(DATATYPEP)malloc ( DATASIZE); ;
    break;}
case 194:
#line 532 "odl.y"
{ yyval.nextP=(DATATYPEP)malloc ( DATASIZE); ;
    break;}
case 195:
#line 534 "odl.y"
{ yyval.nextP=(DATATYPEP)malloc ( DATASIZE); ;
    break;}
case 196:
#line 535 "odl.y"
{ yyval.nextP=(DATATYPEP)malloc ( DATASIZE); ;
    break;}
case 197:
#line 536 "odl.y"
{ yyval.nextP=(DATATYPEP)malloc ( DATASIZE); ;
    break;}
case 198:
#line 540 "odl.y"
{ yyval.nextP=(DATATYPEP)malloc ( DATASIZE); ;
    break;}
case 199:
#line 541 "odl.y"
{ yyval.nextP=(DATATYPEP)malloc ( DATASIZE); ;
    break;}
case 201:
#line 548 "odl.y"
{ yyval.nextP=(DATATYPEP)malloc ( DATASIZE); ;
    break;}
case 202:
#line 549 "odl.y"
{ yyval.nextP=(DATATYPEP)malloc ( DATASIZE); ;
    break;}
case 212:
#line 578 "odl.y"
{ yyval.nextP=(DATATYPEP)malloc ( DATASIZE); ;
    break;}
case 213:
#line 579 "odl.y"
{ yyval.nextP=(DATATYPEP)malloc ( DATASIZE); ;
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
#line 587 "odl.y"

