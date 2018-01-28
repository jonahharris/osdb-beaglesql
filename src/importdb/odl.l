

%{
#define SEMICOLON   258
#define DBLCOLON    259 
#define COLON       260
#define OPCURLBRKT  261
#define CLCURLBRKT  262 
#define COMMA       264
#define EQUALS      265
#define OPSQBRKT    266
#define CLSQBRKT    267
#define OPPAREN     268
#define CLPAREN     269
#define XOR_OP      272
#define OR_OP       273
#define AND_OP      274
#define SHRITE_OP   275
#define SHLEFT_OP   276
#define  LESSTHAN   301
#define  GREATERTHAN 302

struct keywordmap {
   char keyword[16];
   unsigned int token;
};
static unsigned long lineno=1;
static const struct keywordmap keywords[]={
{"CONST", 263},
{"CLASS", 270 },
{"EXTENDS",271 },
{"MODULE", 328},
{"INTERFACE", 277},
{"CONTEXT", 278},
{"IN", 279},
{"OUT", 280},
{"INOUT", 281},
{"VOID",282},
{"RELATIONSHIP",283},
{"INVERSE",284},
{"ONEWAY",285},
{"RAISES",286},
{"EXCEPTION",287},
{"STRUCT",288},
{"UNION",289},
{"SWITCH",290},
{"READONLY",291},
{"ATTRIBUTE",292},
{"KEY",293},
{"KEYS",293},
{"SET",295},
{"LIST",296},
{"BAG",297},
{"DICTIONARY",298},
{"ARRAY",299},
{"SEQUENCE",300},
{"INTERVAL",303},
{"LONG",304},
{"SHORT",305},
{"UNSIGNED",306},
{"INT",307},
{"FLOAT",308},
{"DOUBLE",309},
{"OCTET",310},
{"STRING",311},
{"TIME",312},
{"DATE",313},
{"TIMESTAMP",314},
{"BOOLEAN",315},
{"TYPEDEF",316},
{"TRUE",317},
{"FALSE",318},
{"CHAR",319},
{"ANY",320},
{"CASE",321},
{"DEFAULT",322},
{"ENUM",323},
{"EXTENT",324}
};


#define STRING_LITERAL  325
#define CHARACTER_LITERAL       326
#define IDENTIFIER      327
#define FLOATING_PT_LITERAL     329

%}

%%

;    { return SEMICOLON ; }
::   { return DBLCOLON ;  }
:    { return COLON ; }
"{"    { return OPCURLBRKT ;  }
"}"    { return CLCURLBRKT ;  }
,    { return COMMA  ;    }
=    { return  EQUALS ;   }
"["    { return  OPSQBRKT;  }
"]"    { return  CLSQBRKT ; }
"("    { return OPPAREN ;   }
")"    { return  CLPAREN ;  }
"^"    { return  XOR_OP ;   }
"|"    { return OR_OP ;     }
"&"    { return  AND_OP ;   }
">>"   { return SHRITE_OP;  }
"<<"   { return  SHLEFT_OP; }
"<"    { return LESSTHAN;   }
">"    { return  GREATERTHAN; }

\n                                      { ++lineno;   }
"[^\"\n]*"                              { return STRING_LITERAL; }
'[a-zA-Z0-9_]'                         { return  CHARACTER_LITERAL ;   }
[0-9]+"."[0-9]+([eE][+-]?[1-9][0-9]*)  { return FLOATING_PT_LITERAL ; }
[a-zA-Z][a-zA-Z0-9_]+                  { int i;
                                         for(i=0;
                                             i<sizeof(keywords)/sizeof(struct keywordmap);
                                             i++)
                                             if (strcmp(keywords[i].keyword,yytext)==0)
                                                return keywords[i].token;
                                          return IDENTIFIER   ;        }

%%
yywrap()
{
  return 1;
}
void yyerror(char *string) 
{
    printf ("%d: %s at %s\n",lineno,string,yytext);

}

