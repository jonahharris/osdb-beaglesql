static const char  rcsfile []= "$Header: /home/magrasjc/test/src/RCS/parse.c,v 0.87.2.1 2000/02/05 06:13:36 magrasjc Exp $";
/*
      
 parse.c
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


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define DELIMITER 1
#define VARIABLE  2
#define NUMBER    3

#include "berror.h"
#include "mymalloc.h"

struct clist {
   char token[MAXIDSIZE];       /* token from the list */
   void *value;
   int type;                    /* data type */
   struct clist *next;
};

#include "beagle.h"
#include "filesys.h"

char *prog;
char token[80];
char tok_type;
struct clist *tokptr=NULL, *tp=NULL;
   typedef char *YYSTYPE;
/*   typedef union{
  int intval[3];
  double floatval;
  char *strval;
  struct SQLvalue *nextP;
  char semString[16];
} YYSTYPE;*/
  YYSTYPE yylval;


struct clist *parse_tokens (char *s);
void free_tokens (struct clist *tokens);
int TOKENlen (char *s, char *sep);
void TOKENstore (struct clist *q);
int parser_flex_gluer(char *, int);
/* functions for the BOOLEAN expression parser */
int  BOOLEAN_get_exp (struct clist *tokens);
void BOOLEAN_level2(char *result); 
void BOOLEAN_level3(char *result);
void BOOLEAN_level4(char *result); 
void BOOLEAN_arith(char *o, char *r, char *h); 
void BOOLEAN_get_token();


/* functions for the ARITHMETIC expression parser */
int  ARITHMETIC_get_exp (struct clist *tokens);
void ARITHMETIC_level2(char *result); 
void ARITHMETIC_level3(char *result);
void ARITHMETIC_level4(char *result); 
void ARITHMETIC_arith(char *o, char *r, char *h); 
void ARITHMETIC_get_token();

char *strstripstr (char *s1, char *s2);

struct clist *parse_tokens (char *s)
{
   char *p;
   extern char *yytext;
   int len,lextoken=-1;
   unsigned int pstack[16],pstackI=0,tokenLen;
   extern int yyleng;
   struct clist *ptr=NULL, *new=NULL;
   typedef char *YYSTYPE;
/*   typedef union{
  int intval[3];
  double floatval;
  char *strval;
  struct SQLvalue *nextP;
  char semString[16];
} YYSTYPE;*/
  char labelspace[128];
  YYSTYPE yylval;

   parser_flex_gluer(s,-1);

   TOKENstore (NULL);  /* initialize the last pointer for the list */
   lprintf ("still going");
   /* separate Query String into tokens 
      for (p=s; *p != '\0' ;) {*/

   labelspace[0]=0;
   while ((lextoken  =yylex()) || pstackI) {
       lprintf ("lexer returns %d state %d",lextoken,pstackI);
       /*if (lextoken==46) {
           strcat(labelspace,"."); 
           ++tokenLen;
	   lprintf ("an extended token");
           continue;
       }
       else if (lextoken==258 && !pstackI) {
           ++pstackI;
           strcpy(labelspace,yytext);
           tokenLen=yyleng;
	    lprintf ("extended token %s",labelspace);
           continue;
       }
       else if (lextoken==258 && pstackI) {
            strncat(labelspace,yytext,yyleng);
            tokenLen+=yyleng;
            yytext[tokenLen]=0;
	    lprintf ("multipart extended token %s",labelspace);
            continue;
            
       } else {
            if (pstackI==1) {
                lprintf ("handling label backlog");
                new = (struct clist *) mymalloc (new, sizeof (struct clist));
                strncpy(new->token,labelspace,tokenLen);
                new->token[tokenLen]='\0';
                new->value=NULL;
                new->type=0;
                new->next=NULL;
                TOKENstore (new);
                if (ptr==NULL) ptr=new;
                pstackI=0;
                if (lextoken==0) return ptr;
            }*/ 
            pstackI=0;
            new = (struct clist *) mymalloc (new, sizeof (struct clist));
            tokenLen=yyleng;
       
     /* len = TOKENlen (p, " \t(),\0");*/
    

      lprintf ("lexer returns %d, %d long aka %s",lextoken,yyleng,yytext);
      /* if (!isspace (*p)) {
         if (*p == '\'') len = TOKENlen (p+1, "'") + 2; */

         if (new == NULL)
            return NULL;

         if (ptr == NULL) ptr = new;   /* save the head of the list */
	 /* strncpy (new->token, p, len);
	    new->token [len] = '\0';*/
            strncpy(new->token,yytext,yyleng);
            new->token[yyleng]='\0';

         new->value=NULL;
         new->type=0;
         new->next=NULL;
         TOKENstore (new);
	 /* new=NULL;*/
	 /* }
	  }
	    p += len;*/
   }
   return ptr;
}


void free_tokens (struct clist *tokens)
{
   struct clist *t;

   /* free nodes in token list */
   for (t=tokens; t!=NULL;) {
      tokens = t->next;
      myfree (t);
      t=tokens;
   }
   tokens=NULL;
}

int parser_flex_gluer(char * buffer,int max)
{
   static char input[2048];
   static int  offset=0;
   unsigned int inLength,copyLength;

   if (max==-1) {
      strcpy(input,buffer);
      strcat(input," ");
      lprintf ("lexer inited with -%s-",buffer);
      return 0;
   }

   inLength=strlen(input)-offset;
   lprintf ("inlength= %d",inLength);
   if (inLength <= 0 ) {
      lprintf("lexer detected end of file");
      input[0]=0;
      offset=0;
      return 0;   

   }
   else if ( inLength >= max) {
      copyLength= max - 1;
      return 0;
   } else  
      copyLength = inLength;

   if (inLength > 0) {
      memcpy(buffer,input+offset,copyLength);
      offset ++;
   }
   /*
   lprintf ("returning offset= %d,copylength = %d,max=%d",offset,copyLength,max);
   */
   if (max > strlen(input)) {
       input[0]=0;
       offset = 0; 
    }
   return copyLength;
}

int TOKENlen (char *s, char *sep)
{
   int len;

   len = (int) strcspn (s, sep);  /* find the length of the first token */
   if (!len) len = 1;       /* if zero than '*s' is in the list 'sep' */
   return len;
}



void TOKENstore (struct clist *q)
{
   static struct clist *last=NULL;

   if (q==NULL) {
      last=NULL;
      return;
   }

   if (last==NULL) last=q;
   else last->next=q;
   q->next=NULL;
   last=q;
}


/* parser entry point */
int BOOLEAN_get_exp (struct clist *tokens)
{
   char temp[80];

   tp = tokptr = tokens;   /* parse the list into tokens */
   BOOLEAN_get_token();            /* start the expresion parser */

   if (!*token) {
      /* No expression present */
      return ERROR;
   }
   BOOLEAN_level2 (temp);
   return atoi (temp);
}

/* logical and & or */
void BOOLEAN_level2 (char *result)
{
   char op[80];
   char hold[80];

   BOOLEAN_level3 (result);
   while ( !strcmp (strcpy (op, token), "and") || !strcmp (op, "or") ) {
      BOOLEAN_get_token();
      BOOLEAN_level3 (hold);
      BOOLEAN_arith (op, result, hold);
   }
}

/* equalities */
void BOOLEAN_level3 (char *result)
{
   char op[80];
   char hold[80];

   BOOLEAN_level4 (result);
   while ( !strcmp (strcpy (op, token), "=") || 
           !strcasecmp (op, "contains") || 
           !strcasecmp (op, "begins") || 
           !strcmp (op, "<>") || 
           !strcmp (op, "<") || 
           !strcmp (op, "<=") || 
           !strcmp (op, ">=") || 
           !strcmp (op, ">")) {
      BOOLEAN_get_token();
      BOOLEAN_level4 (hold);
      BOOLEAN_arith (op, result, hold);
   }
}
   
/* parenthesized expression */
void BOOLEAN_level4 (char *result)
{
   if (!strcmp (token, "(") && (tok_type == DELIMITER)) {
      BOOLEAN_get_token();
      BOOLEAN_level2 (result);
      if (strcmp (token, ")"))
         /* unbalanced parentheses */ ;
      BOOLEAN_get_token();
   }
   else {
      strcpy (result, token);
      BOOLEAN_get_token();
   }
}
#define CMPEQTIME  atol(r) == atol(h)
#define CMPNETIME  atol(r) != atol(h)
#define CMPLTTIME  atol(r) < atol(h)
#define CMPGTTIME  atol(r) > atol(h)
#define CMPGETIME  atol(r) >= atol(h)
#define CMPLETIME  atol(r) <= atol(h)
/* perform the indicated arithmetic */
void BOOLEAN_arith (char *o, char *r, char *h)
{
   char *p;
   int type=FTYPE_CHAR, length;

   if ((p = strstr (r, "|~|")) != NULL)
      type = atoi(p+3);
   lprintf ("%s to %s",r,h); 
   if (!strcasecmp (o, "or"))
      sprintf (r, "%d", atoi(r) || atoi(h));
   else if (!strcasecmp (o, "and"))
      sprintf (r, "%d", atoi(r) && atoi(h));
   else if (isalpha (*r) || isalpha (*h))  /* check for variables */
      sprintf (r, "1");   /* evaluate all joins to yes */
   else if (!strcmp (o, "=")) {
      if (type==FTYPE_INT || type==FTYPE_OID)
         sprintf (r, "%d", atol(r) == atol(h));
      else if (type==FTYPE_TIME||type==FTYPE_DATE||type==FTYPE_TIMESTAMP )
         sprintf (r, "%d", CMPEQTIME);
      else if (type==FTYPE_BLOB ) {
      }else /* assume FTYPE_CHAR */
         sprintf (r, "%d", !strcmp (r, h));
   }
   else if (!strcasecmp (o, "contains"))
      sprintf (r, "%d", strstripstr (r, h) ? 1 : 0);
   else if (!strcasecmp (o, "begins")) {
      length = strlen(h)-1;
      if ((p = strstr (h, "|~|")) != NULL)
         length = p - h - 1;
      sprintf (r, "%d", !strncmp (r, h, length) ? 1 : 0);
   }
   else if (!strcmp (o, "<>")) {
      if (type==FTYPE_INT || type==FTYPE_OID)
         sprintf (r, "%d", atol(r) != atol(h));
      else if ( type==FTYPE_TIME||type==FTYPE_DATE||type==FTYPE_TIMESTAMP )
         sprintf (r, "%d", CMPNETIME);
      else if (type==FTYPE_BLOB ) {
      }
      else /* assume FTYPE_CHAR */
         sprintf (r, "%d", strcmp (r, h) ? 1 : 0);
   }
   else if (!strcmp (o, ">=")) {
      if (type==FTYPE_INT || type==FTYPE_OID)
         sprintf (r, "%d", atol(r) >= atol(h));
      else if (type==FTYPE_TIME||type==FTYPE_DATE||type==FTYPE_TIMESTAMP )
         sprintf (r, "%d", CMPGETIME); 
      else if (type==FTYPE_BLOB ) {
      }
      else /* assume FTYPE_CHAR */
         sprintf (r, "%d", strcmp (r, h) >= 0 ? 1 : 0);
   } else if (!strcmp (o, "<=")) {
      if (type==FTYPE_INT || type==FTYPE_OID)
         sprintf (r, "%d", atol(r) <= atol(h));
      else if (type==FTYPE_TIME||type==FTYPE_DATE||type==FTYPE_TIMESTAMP )
         sprintf (r, "%d", CMPLETIME); 
      else if (type==FTYPE_BLOB ) {
      }
      else /* assume FTYPE_CHAR */
         sprintf (r, "%d", strcmp (r, h) <= 0 ? 1 : 0);
   } else if (!strcmp (o, "<")) {
      if (type==FTYPE_INT || type==FTYPE_OID)
         sprintf (r, "%d", atol(r) < atol(h));
      else if (type==FTYPE_TIME||type==FTYPE_DATE||type==FTYPE_TIMESTAMP )
         sprintf (r, "%d", CMPLTTIME);
      else if (type==FTYPE_BLOB ) {
      }
      else /* assume FTYPE_CHAR */
         sprintf (r, "%d", strcmp (r, h) < 0 ? 1 : 0);
   }
   else if (!strcmp (o, ">")) {
      if (type==FTYPE_INT || type==FTYPE_OID)
         sprintf (r, "%d", atol(r) > atol(h));
      else if (type==FTYPE_TIME||type==FTYPE_DATE||type==FTYPE_TIMESTAMP )
         sprintf (r, "%d", CMPGTTIME);
      else if (type==FTYPE_BLOB ) {
      }
      else /* assume FTYPE_CHAR */
         sprintf (r, "%d", strcmp (r, h) > 0 ? 1 : 0);
   }

}


void BOOLEAN_get_token()
{
   tok_type=0;
   strcpy (token, "");

   if (tp!=NULL) {

      if (strstr ("and or <> = ( ) <= >=", tp->token) ||
          !strcasecmp (tp->token, "and") ||
          !strcasecmp (tp->token, "or") ||
          !strcasecmp (tp->token, "contains") ||
          !strcasecmp (tp->token, "begins") ) {
         strcpy (token, tp->token);
         tok_type=DELIMITER;
      }
      else if (isdigit ( *(tp->token) )) {
         sprintf (token, "%s|~|%d", tp->token, FTYPE_INT);
         /*strcpy (token, tp->token);*/
         tok_type=NUMBER;
      }
      else {
         if (tp->value != NULL) {
            if (tp->type == FTYPE_INT || tp->type == FTYPE_OID)
               sprintf (token, "%ld|~|%d", *((long *)tp->value), tp->type);
            else if (tp->type==FTYPE_TIME||tp->type==FTYPE_DATE||tp->type==FTYPE_TIMESTAMP )
               sprintf (token, "%s|~|%d",(char *)tp->value,tp->type ); 
           
            else  /* assume FTYPE_CHAR */
               sprintf (token, "%s|~|%d", (char *)tp->value, tp->type);
               /*strcpy (token, tp->value);*/
         }
         else if (!strcmp(tp->token,"TIME") ||
                  !strcmp(tp->token,"DATE") ||
                  !strcmp(tp->token,"TIMESTAMP")) {
            tp=tp->next;
            sprintf (token, "%s|~|%d", tp->token, tp->type);
	 } else if (!strcmp(tp->token,"BLOB"))
            tp=tp->next;
         else
            sprintf (token, "%s|~|%d", tp->token, tp->type);
            /*strcpy (token, tp->token);*/
         tok_type=VARIABLE;
      }
      tp = tp->next;
   }
}



/* parser entry point */
int ARITHMETIC_get_exp (struct clist *tokens)
{
   char temp[80];

   tp = tokptr = tokens;   /* parse the list into tokens */
   ARITHMETIC_get_token();            /* start the expresion parser */

   if (!*token) {
      /* No expression present */
      return ERROR;
   }
   ARITHMETIC_level2 (temp);
   return atoi (temp);
}

/* logical and & or */
void ARITHMETIC_level2 (char *result)
{
   char op[80];
   char hold[80];

   ARITHMETIC_level3 (result);
   while ( !strcmp (strcpy (op, token), "and") || !strcmp (op, "or") ) {
      ARITHMETIC_get_token();
      ARITHMETIC_level3 (hold);
      ARITHMETIC_arith (op, result, hold);
   }
}

/* equalities */
void ARITHMETIC_level3 (char *result)
{
   char op[80];
   char hold[80];

   ARITHMETIC_level4 (result);
   while ( !strcmp (strcpy (op, token), "=") || 
           !strcasecmp (op, "contains") || 
           !strcasecmp (op, "begins") || 
           !strcmp (op, "<>") || 
           !strcmp (op, "<") || 
           !strcmp (op, ">")) {
      ARITHMETIC_get_token();
      ARITHMETIC_level4 (hold);
      ARITHMETIC_arith (op, result, hold);
   }
}
   
/* parenthesized expression */
void ARITHMETIC_level4 (char *result)
{
   if (!strcmp (token, "(") && (tok_type == DELIMITER)) {
      ARITHMETIC_get_token();
      ARITHMETIC_level2 (result);
      if (strcmp (token, ")"))
         /* unbalanced parentheses */ ;
      ARITHMETIC_get_token();
   }
   else {
      strcpy (result, token);
      ARITHMETIC_get_token();
   }
}

/* perform the indicated arithmetic */
void ARITHMETIC_arith (char *o, char *r, char *h)
{
   char *p;
   int type=FTYPE_CHAR, length;

   if ((p = strstr (r, "|~|")) != NULL)
      type = atoi(p+3);
   
   if (!strcasecmp (o, "or"))
      sprintf (r, "%d", atoi(r) || atoi(h));
   else if (!strcasecmp (o, "and"))
      sprintf (r, "%d", atoi(r) && atoi(h));
   else if (isalpha (*r) || isalpha (*h))  /* check for variables */
      sprintf (r, "1");   /* evaluate all joins to yes */
   else if (!strcmp (o, "=")) {
      if (type==FTYPE_INT || type==FTYPE_OID)
         sprintf (r, "%d", atol(r) == atol(h));
      else if (type==FTYPE_TIME||type==FTYPE_DATE||type==FTYPE_TIMESTAMP )
         sprintf (r, "%d", CMPEQTIME);
      else if (type==FTYPE_BLOB ) {}
      else /* assume FTYPE_CHAR */
         sprintf (r, "%d", !strcmp (r, h));
   }
   else if (!strcasecmp (o, "contains"))
      sprintf (r, "%d", strstripstr (r, h) ? 1 : 0);
   else if (!strcasecmp (o, "begins")) {
      length = strlen(h)-1;
      if ((p = strstr (h, "|~|")) != NULL)
         length = p - h - 1;
      sprintf (r, "%d", !strncmp (r, h, length) ? 1 : 0);
   }
   else if (!strcmp (o, "<>")) {
      if (type==FTYPE_INT || type==FTYPE_OID)
         sprintf (r, "%d", atol(r) != atol(h));
      else if (type==FTYPE_TIME||type==FTYPE_DATE||type==FTYPE_TIMESTAMP )
         sprintf (r, "%d", CMPNETIME);
      else if (type==FTYPE_BLOB ){ }
      else /* assume FTYPE_CHAR */
         sprintf (r, "%d", strcmp (r, h) ? 1 : 0);
   }
   else if (!strcmp (o, "<")) {
      if (type==FTYPE_INT || type==FTYPE_OID)
         sprintf (r, "%d", atol(r) < atol(h));
      else if (type==FTYPE_TIME||type==FTYPE_DATE||type==FTYPE_TIMESTAMP )
         sprintf (r, "%d", CMPLTTIME);
      else if (type==FTYPE_BLOB ) {}
      else /* assume FTYPE_CHAR */
         sprintf (r, "%d", strcmp (r, h) < 0 ? 1 : 0);
   }
   else if (!strcmp (o, ">")) {
      if (type==FTYPE_INT || type==FTYPE_OID)
         sprintf (r, "%d", atol(r) > atol(h));
      else if (type==FTYPE_TIME||type==FTYPE_DATE||type==FTYPE_TIMESTAMP )
         sprintf (r, "%d", CMPGTTIME);
      else if (type==FTYPE_BLOB ) {}
      else /* assume FTYPE_CHAR */
         sprintf (r, "%d", strcmp (r, h) > 0 ? 1 : 0);
   }
   else if (!strcmp (o, ">=")) {
      if (type==FTYPE_INT || type==FTYPE_OID)
         sprintf (r, "%d", atol(r) >= atol(h));
      else if (type==FTYPE_TIME||type==FTYPE_DATE||type==FTYPE_TIMESTAMP )
         sprintf (r, "%d", CMPGETIME);
      else if (type==FTYPE_BLOB ) {}
      else /* assume FTYPE_CHAR */
         sprintf (r, "%d", strcmp (r, h) >= 0 ? 1 : 0);
   }
   else if (!strcmp (o, "<=")) {
      if (type==FTYPE_INT || type==FTYPE_OID)
         sprintf (r, "%d", atol(r) <= atol(h));
      else if (type==FTYPE_TIME||type==FTYPE_DATE||type==FTYPE_TIMESTAMP )
         sprintf (r, "%d", CMPLETIME);
      else if (type==FTYPE_BLOB ) {}
      else /* assume FTYPE_CHAR */
         sprintf (r, "%d", strcmp (r, h) <= 0 ? 1 : 0);
   }
}


void ARITHMETIC_get_token()
{
   tok_type=0;
   strcpy (token, "");

   if (tp!=NULL) {

      if (strstr ("and or <> = ( ) <= >=", tp->token) ||
          !strcasecmp (tp->token, "and") ||
          !strcasecmp (tp->token, "or") ||
          !strcasecmp (tp->token, "contains") ||
          !strcasecmp (tp->token, "begins") ) {
         strcpy (token, tp->token);
         tok_type=DELIMITER;
      }
      else if (isdigit ( *(tp->token) )) {
         sprintf (token, "%s|~|%d", tp->token, FTYPE_INT);
         /*strcpy (token, tp->token);*/
         tok_type=NUMBER;
      }
      else {
         if (tp->value != NULL) {
            if (tp->type == FTYPE_INT || tp->type == FTYPE_OID)
               sprintf (token, "%ld|~|%d", *((long *)tp->value), tp->type);
            else if (tp->type == FTYPE_TIME || tp->type==FTYPE_DATE||tp->type==FTYPE_TIMESTAMP)
               sprintf (token, "%ld|~|%d", *(time_t *)tp->value, tp->type);
            else if (tp->type==FTYPE_BLOB ) {}
            else  /* assume FTYPE_CHAR */
               sprintf (token, "%s|~|%d", (char *)tp->value, tp->type);
               /*strcpy (token, tp->value);*/
         }
         else
            sprintf (token, "%s|~|%d", tp->token, tp->type);
            /*strcpy (token, tp->token);*/
         tok_type=VARIABLE;
      }
      tp = tp->next;
   }
}


/* strip quotes from string for comparision */
char *strstripstr (char *s1, char *s2)
{
   int l1, l2;

   l2 = strlen(s2);
   if (!l2)
      return (char *) s1;
   l1 = strlen(s1);
   while (l1 >= l2) {
      l1--;
      /* s2+1 & s1+1 = skip opening quote  l2-2 = skip closing quote */
      if (!strncmp(s1+1,s2+1,l2-2))
        return (char *) s1;
      s1++;
   }
   return NULL;
}
