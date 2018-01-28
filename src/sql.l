/*
   blatantly stolen from "lex & yacc" by John R. Levin,
   Tony Mason, and Doug Brown, an O'Reilly Nutshell Handbook .
 */
%{
#include "sql1.h"
#include <string.h>
static unsigned long hash;
typedef struct hashedword {
    unsigned long Hash; unsigned char words[24];unsigned token;
} HashedWord;
extern char *yylval;
static HashedWord hashedKeyWords[]=
{
{ 67 , "C",270 },
{ 1199 , "OF",312 },
{ 1327 , "ON",313 },
{ 1342 , "NO",428 },
{ 1348 , "TO",334 },
{ 1391 , "OR",315 },
{ 1393 , "AS",265 },
{ 1401 , "IS",304 },
{ 1409 , "AT",353 },
{ 1490 , "BY",269 },
{ 17793 , "ADA",256 },
{ 18528 , "PAD",435 },
{ 18545 , "ASC",266 },
{ 18561 , "ADD",348 },
{ 18721 , "AND",258 },
{ 19041 , "ARE",351 },
{ 19617 , "AVG",259 },
{ 19984 , "PLI",318 },
{ 20737 , "ALL",257 },
{ 21155 , "SUM",262 },
{ 21213 , "MIN",260 },
{ 22326 , "FOR",291 },
{ 22679 , "GET",401 },
{ 22691 , "SET",329 },
{ 22738 , "BIT",355 },
{ 22846 , "NOT",309 },
{ 23645 , "MAX",261 },
{ 23892 , "DAY",381 },
{ 23963 , "KEY",305 },
{ 24097 , "ANY",264 },
{ 284808 , "LOCAL",418 },
{ 285904 , "NCHAR",426 },
{ 285973 , "ESCAPE",287 },
{ 286201 , "UPDATE",337 },
{ 286471 , "CREATE",277 },
{ 287834 , "FLOAT",290 },
{ 288215 , "COLATE",366 },
{ 288605 , "DOMAIN",389 },
{ 292504 , "SPACE",452 },
{ 293128 , "GLOBAL",402 },
{ 293390 , "CHECK",272 },
{ 294608 , "DOUBLE",286 },
{ 296354 , "READ",441 },
{ 296852 , "DESC",284 },
{ 297125 , "MATCH",420 },
{ 297182 , "FETCH",289 },
{ 298081 , "PASCAL",317 },
{ 301505 , "ORDER",316 },
{ 302677 , "EXCEPT",393 },
{ 303068 , "LIKE",307 },
{ 303328 , "SCHEMA",327 },
{ 303537 , "NAMES",423 },
{ 303588 , "TIME",458 },
{ 303683 , "SOME",331 },
{ 303946 , "ZONE",478 },
{ 303995 , "INNER",407 },
{ 304440 , "DELETE",283 },
{ 304551 , "UPPER",469 },
{ 304678 , "SELECT",328 },
{ 304979 , "CASE",360 },
{ 305157 , "ELSE",391 },
{ 305236 , "DATE",380 },
{ 305349 , "CONERT",373 },
{ 305491 , "ALTER",350 },
{ 305649 , "OUTER",432 },
{ 305780 , "TRUE",467 },
{ 305896 , "LEVEL",417 },
{ 306318 , "LOWER",419 },
{ 306619 , "INSERT",301 },
{ 306915 , "SIZE",451 },
{ 308137 , "DEFAULT",282 },
{ 308367 , "CATALOG",362 },
{ 308938 , "USAGE",470 },
{ 312666 , "EXECUTE",395 },
{ 314098 , "SQLCODE",332 },
{ 314422 , "RIGHT",445 },
{ 315604 , "CASCADE",358 },
{ 315845 , "LEADING",415 },
{ 317671 , "WITH",343 },
{ 317746 , "BOTH",357 },
{ 318654 , "VARCHAR",473 },
{ 319760 , "BEGINS",  13000 },
{ 322176 , "NUMERIC",311 },
{ 322976 , "ACTION",347 },
{ 323198 , "OPTION",314 },
{ 323350 , "HAVING",299 },
{ 326127 , "FOREIGN",292 },
{ 327616 , "INTEGER",302 },
{ 329122 , "REAL",324 },
{ 329385 , "TABLE",333 },
{ 329543 , "WORK",344 },
{ 330777 , "PUBLIC",323 },
{ 332182 , "FULL",400 },
{ 332278 , "NULLX",310 },
{ 333383 , "NULLIF",429 },
{ 335476 , "TRIM",466 },
{ 336998 , "FROM",295 },
{ 337595 , "GRANT",297 },
{ 337852 , "COMMIT",275 },
{ 337905 , "DECIMAL",280 },
{ 338388 , "THEN",457 },
{ 338391 , "WHEN",475 },
{ 339514 , "JOIN",413 },
{ 339660 , "USING",471 },
{ 341887 , "COBOL",274 },
{ 342650 , "FOUND",294 },
{ 342663 , "COUNT",263 },
{ 343089 , "SECOND",448 },
{ 343683 , "UNION",335 },
{ 343746 , "PRIOR",440 },
{ 346409 , "INTO",303 },
{ 346423 , "GOTO",296 },
{ 347023 , "SCROLL",447 },
{ 347965 , "REVOKE",444 },
{ 348661 , "DECLARE",281 },
{ 349284 , "DROP",390 },
{ 352052 , "OUTPUT",433 },
{ 353731,  "CHAR" ,426 }, 
{ 352986 , "UNIQUE",336 },
{ 353705 , "YEAR",477 },
{ 354844 , "WHERE",342 },
{ 354949 , "USER",338 },
{ 358968 , "HOUR",403 },
{ 359633 , "PRIMARY",320 },
{ 360603 , "FALSE",398 },
{ 361460 , "UNKNOWN",468 },
{ 361544 , "CLOSE",273 },
{ 361545 , "EXISTS",288 },
{ 361654 , "CROSS",375 },
{ 362282 , "FIRST",399 },
{ 363164 , "LEFT",416 },
{ 363432 , "CONNECT",369 },
{ 363586 , "ROWS",446 },
{ 363778 , "CURSOR",279 },
{ 364220 , "WRITE",476 },
{ 365445 , "MONTH",422 },
{ 365777 , "PREPARE",438 },
{ 366419 , "CAST",361 },
{ 366428 , "LAST",414 },
{ 367774 , "NEXT",427 },
{ 368089 , "MODULE",308 },
{ 368811 , "VALUE",472 },
{ 369847 , "GROUP",298 },
{ 370045 , "INPUT",408 },
{ 370139 , "VALUES",339 },
{ 370272 , "COLUMN",368 },
{ 370561 , "MINUTE",421 },
{ 375270 , "VIEW",340 },
{ 381112 , "CURRENT",278 },
{ 381494 , "EXTRACT",397 },
{ 383708 , "SESSION",449 },
{ 385327 , "ONLY",431 },
{ 386745 , "PARTIAL",436 },
{ 387480 , "FORTRAN",293 },
{ 391360 , "NATURAL",425 },
{ 400167 , "BETWEEN",268 },
{ 400167 , "BETWEEN",354 },
{ 406159 , "VARYING",474 },
{ 496618 , "END-EXEC",392 },
{ 591266 , "DEFERRABLE",383 },
{ 592774 , "RELATIVE",442 },
{ 594132 , "CASCADED",359 },
{ 597622 , "DESCRIBE",385 },
{ 598713 , "NAMES",325 },
{ 599039 , "INTERSECT",410 },
{ 599302 , "DEFERRED",384 },
{ 602246 , "DISCONNECT",388 },
{ 613825 , "LANGUAGE",306 },
{ 615028 , "DEALLOCATE",382 },
{ 629072 , "TRAILING",462 },
{ 630440 , "COALESCE",365 },
{ 634843 , "INTERVAL",411 },
{ 634871 , "EXTERNAL",396 },
{ 637127 , "TIMESTAMP",459 },
{ 637239 , "PRECISION",319 },
{ 645027 , "EXCEPTION",394 },
{ 649041 , "ASSERTION",352 },
{ 649556 , "ALLOCATE",349 },
{ 650893 , "NATIONAL",424 },
{ 651517 , "ABSOLUTE",346 },
{ 654906 , "PROCEDURE",322 },
{ 657556 , "ROLLBACK",326 },
{ 659078 , "CHARACTER",271 },
{ 662564 , "POSITION",437 },
{ 663767 , "CONNECTION",370 },
{ 664014 , "INDICATOR",300 },
{ 664037 , "DESCRIPTOR",386 },
{ 665045 , "PRESERVE",439 },
{ 665650 , "IMMEDIATE",405 },
{ 666055 , "SQLSTATE",453 },
{ 671068 , "CONTINUE",276 },
{ 675842 , "COLLATION",367 },
{ 676680 , "ISOLATION",412 },
{ 679733 , "CONSTRAINT",371 },
{ 683502 , "PRIVILEGES",321 },
{ 688464 , "INSENSITIVE",409 },
{ 693372 , "WHENEVER",341 },
{ 694527 , "SMALLINT",330 },
{ 696027 , "INITIALLY",406 },
{ 697739 , "DIAGNOSTICS",387 },
{ 697950 , "SUBSTRING",454 },
{ 699596 , "TRANSLATE",464 },
{ 700981 , "CONSTRAINTS",372 },
{ 702572 , "TEMPORARY",456 },
{ 712041 , "CHAR_LENGTH",363 },
{ 716555 , "OVERLAPS",434 },
{ 720832 , "TRANSLATION",465 },
{ 725058 , "BIT_LENGTH",356 },
{ 725613 , "IDENTITY",404 },
{ 728964 , "RESTRICT",443 },
{ 729085 , "DISTINCT",285 },
{ 762779 , "SYSTEM_USER",455 },
{ 852240 , "TRANSACTION",463 },
{ 926593 , "OCTET_LENGTH",430 },
{ 966130 , "TIMEZONE_MINUTE",461 },
{ 977247 , "TIMEZONE_HOUR",460 },
{ 1043069 , "CORRESPONDING",374 },
{ 1050319 , "AUTHORIZATION",267 },
{ 1073820 , "CURRENT_TIME",377 },
{ 1075468 , "CURRENT_DATE",376 },
{ 1125181 , "CURRENT_USER",379 },
{ 1127777 , "SESSION_USER",450 },
{ 1280308 , "CHARACTER_LENGTH",364 },
{ 1407359 , "CURRENT_TIMESTAMP",378 }
};
int parser_flex_gluer(char *,int);
int lineno=1;
    static int lexemeoffset=0,offset=0;
void yyerror(char *s);
#undef YY_INPUT
#define YY_INPUT(buf,result,max) (result= parser_flex_gluer(buf,max))
/* literal keyword tokens */
%}
%e1200
%%



=|<>|<|>|<=|>=   { if (yytext[offset+1]=='>' || yytext[offset+1]=='=')
                        offset++;
                   offset++;
                        return COMPARISON; }

'[^'\n]*' {
     int c=input();
     unput(c);
     if(c != '\'') { 
        offset+=2;
        return STRING;
     }
     else
     {
        offset++;
        yymore();
     }
}

[A-Za-z][-0-9A-Za-z_]*("."[A-Za-z][0-9A-Za-z]*)? {
    int index;
    hash=0;
    for (;lexemeoffset<yyleng;lexemeoffset++) {   
    switch (lexemeoffset %4){
       case 0:
                hash+= toupper(yytext[lexemeoffset]);
                break;
       case 1:
                hash += toupper(yytext[lexemeoffset]) << 4;
                break;
       case 2:
                hash += toupper(yytext[lexemeoffset])  << 8 ;
                break;
       case 3:
                hash += toupper(yytext[lexemeoffset])  << 12 ;
                break;
     }
     lprintf ("hash=%d,offset=%d,lexemeoffset=%d,yytext=%s",hash,offset,lexemeoffset,yytext);
    }
       if (hash < 23000)
          index =0;
       else if (hash < 303000)
          index = 25;
       else if (hash < 318000)
          index =47;
       else if (hash < 346000)
          index =81;
       else if (hash < 354000 )
           index = 96;
       else if (hash < 370100 )
           index = 120;
       else if ( hash < 655000 )
           index = 144;
       else 
           index = 181;

       offset += lexemeoffset+1;
       for (;index < sizeof (hashedKeyWords)/sizeof(HashedWord);index++) {
          /*lprintf ("index: %d,current token %d,current hash %d",index,
                  hashedKeyWords[index].token,hashedKeyWords[index].Hash);*/
          if (hashedKeyWords[index].Hash== hash) {
              /*lprintf ("the hash matches ... %d",hash);*/
              if (strncasecmp(hashedKeyWords[index].words,yytext,strlen(hashedKeyWords[index].words))==0) {
                  lprintf ("matched keyword %s",hashedKeyWords[index].words);
                  return hashedKeyWords[index].token;
               }
          }else if (hashedKeyWords[index].Hash > hash)
             {
             char * tempP=NULL;
             lprintf ("[%s]",yytext);
             tempP=strchr(yytext,' ');
             if (tempP==NULL)
                tempP=strchr(yytext,',');
             lprintf ("[%s]distance is %d.\n",yytext,strlen(yytext));
             yylval=(char*) malloc(64/*strlen(yytext)+8*/);
             if (tempP)
                 strncpy(yylval,yytext,strlen(yytext));
             else
                 strncpy(yylval,yytext,tempP-yytext);
                 
             lprintf ("Returning reference:yytext=<%s>\n",yytext);
             return NAME;
             }
         }
        return NAME; 
 }
[-+*/:(),.;] { hash=0;offset++;return yytext[0]; }
[0-9]+ |
[0-9]+"."[0-9]* |
"."[0-9]* { return INTNUM; }

[0-9]+[eE][+-]?[0-9]+ |
[0-9]+"."[0-9]*[eE][+-]?[0-9]+ |
"."[0-9]*[eE][+-]?[0-9]+ { return APPROXNUM; }

\n              lineno++;
[ \t\r]+       { lexemeoffset=0;offset++;hash=0;}
"--".*         ;
.               yyerror("invalid character");  

%%
  void
yyerror(char *string) 
{
    lprintf ("%d: %s at %s\n",lineno,string,yytext);

}

int yywrap()
{
  return 1;
}

/*

*/


