%{
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
%}

%union{
  int intval[3];
  double floatval;
  char *strval;
  struct SQLvalue *nextP;
  char semString[16];
}

%token NAME
%token STRING
%token INTNUM APPROXNUM

%left OR
%left AND
%left NOT
%left COMPARISON
%left '+' '-'
%left '*' '/'
%nonassoc UMINUS

%token ADA ALL AND AVG AMMSC MIN MAX SUM COUNT ANY AS ASC
%token AUTHORIZATION BETWEEN BY C CHARACTER CHECK CLOSE COBOL
%token COMMIT CONTINUE CREATE CURRENT CURSOR DECIMAL DECLARE
%token DEFAULT DELETE DESC DISTINCT DOUBLE DROP ESCAPE EXISTS FETCH
%token FLOAT FOR FOREIGN FORTRAN FOUND FROM GOTO GRANT GROUP
%token HAVING INDEX INDICATOR INSERT INTEGER INTO IS KEY LANGUAGE
%token LIKE MODULE NOT NULLX NUMERIC OF ON OPEN OPTION OR ORDER PARAMETER
%token PASCAL PLI PRECISION PRIMARY PRIVILEGES PROCEDURE
%token PUBLIC REAL REFERENCES ROLLBACK SCHEMA SELECT SET
%token SMALLINT SOME SQLCODE SQLERROR TABLE TO UNION UNIQUE UPDATE USER
%token USING VALUES VIEW WHENEVER WHERE WITH WORK
%token VARYING VARCHAR NATIONAL CHAR NCHAR BIT

%type <strval> STRING 
%type <strval> USER
%type <floatval> APPROXNUM FLOAT
%type <intval[0]> INTNUM
%type <strval> NAME PARAMETER
%type <intval[0]> SELECT
%type <nextP>  sql_list
%type <nextP>  sql
%type <nextP>  schema
%type <nextP>  opt_schema_element_list
%type <nextP>  schema_element_list
%type <nextP>  schema_element
%type <nextP>  base_table_def
%type <nextP>  base_table_element_commalist
%type <nextP>  base_table_element
%type <nextP>  column_def
%type <nextP>  column_def_opt_list
%type <nextP>  column_def_opt
%type <nextP>  column_commalist
%type <nextP>  opt_column_commalist
%type <nextP>  privilege_def
%type <intval[0]>  opt_with_grant_option
%type <nextP>  privileges
%type <nextP>  operation_commalist
%type <nextP>  operation
%type <nextP>  grantee_commalist
%type <nextP>  grantee
%type <nextP>  cursor_def

%type <nextP>  manipulative_statement
%type <nextP>  close_statement
%type <nextP>  commit_statement
%type <nextP>  delete_statement_positioned
%type <nextP>  delete_statement_searched
%type <nextP>  fetch_statement
%type <nextP>  insert_statement
%type <nextP>  values_or_query_spec
%type <nextP>  insert_atom_commalist
%type <nextP>  insert_atom
%type <nextP>  open_statement
%type <nextP>  rollback_statement
%type <nextP>  create_idx_statement

%type <intval[0]>  opt_all_distinct
%type <nextP>  update_statement_positioned
%type <nextP>  assignment_commalist
%type <nextP>  assignment
%type <nextP>  update_statement_searched
%type <nextP>  target_commalist
%type <nextP>  target
%type <nextP>  opt_where_clause
%type <nextP>  query_exp
%type <nextP>  query_term
%type <nextP>  query_spec
%type <nextP>  selection
%type <nextP>  table_exp
%type <nextP>  from_clause
%type <nextP>  table_ref_commalist
%type <nextP>  table_ref
%type <nextP>  where_clause
%type <nextP>  opt_group_by_clause
%type <nextP>  column_ref_commalist
%type <nextP>  opt_having_clause
%type <nextP>  search_condition
%type <nextP>  predicate
%type <nextP>  comparison_predicate
%type <nextP>  between_predicate
%type <nextP>  like_predicate
%type <nextP>  opt_escape
%type <nextP>  test_for_null
%type <nextP>  in_predicate
%type <nextP>  atom_commalist
%type <nextP>  all_or_any_predicate
%type <intval[0]>  any_all_some
%type <nextP>  existance_test
%type <nextP>  subquery
%type <nextP>  scalar_exp
%type <nextP>  scalar_exp_commalist
%type <nextP>  atom
%type <nextP>  parameter_ref
%type <nextP>  function_ref
%type <nextP>  literal
%type <nextP>  table
%type <nextP>  column_ref
%type <nextP>  data_type
%type <nextP>  column
%type <nextP>  cursor
%type <nextP>  parameter
%type <strval>  range_variable
%type <strval>  user
%type <strval>  index
%type <nextP>  schema_name

%%

sql_list:
       sql  ';'
     | sql_list sql ';'

sql:
       schema ;

schema:
         CREATE SCHEMA schema_name AUTHORIZATION user opt_schema_element_list
      {
         $$=$6;
      }
   ;

opt_schema_element_list:
      /* empty */ { }
   |  schema_element_list
     {
       $$=$1;
     }

schema_element_list:
      schema_element
   | schema_element_list schema_element
   ;

schema_element:
     base_table_def
     {
       $$=$1;
     }
   | privilege_def 
     {
       $$=$1;
     }

   ;

base_table_def:
     CREATE TABLE table '(' base_table_element_commalist ')' {
      lprintf("base_table_def <-- CREATE TABLE table '(' base_table_element_commalist ')'");
     $$=$3;
     }
   ;

base_table_element_commalist:
     base_table_element {
       $$=$1;
       lprintf ("base_table_element_commalist <-- base_table_element");
     } 
     | base_table_element_commalist ',' base_table_element {
       lprintf ("base_table_element_commalist <-- base_table_element_commalist ',' base_table_element");
    }
   ;

base_table_element:
   column_def 
   {
      lprintf ("base_table_element <-- column_def");
      $$=$1;
    }
/*   |   table_constraint_def */
   ;


column_def:
   column data_type column_def_opt_list {
        $$->subtok=eCOLUMN;
        lprintf ("column_def <--  column data_type column_def_opt_list");
   }
   ;

column_def_opt_list:
   /* empty */ { }
   | column_def_opt_list column_def_opt { 
       $$=$1;
       lprintf ("column_def_opt_list <-- column_def_opt_list column_def_opt"); 
    }
   ;

column_def_opt:
      NOT NULLX         
      {
         lprintf ("column_def_opt <-- NOT NULLX");
         $$=(struct SQLvalue *)malloc(sizeof(struct SQLvalue));
         $$->subtok=eNNULLTEST;
      }
   |  NOT NULLX UNIQUE
     {
         lprintf ("column_def_opt <-- NOT NULLX UNIQUE"); 
         $$=(struct SQLvalue *)malloc(sizeof(struct SQLvalue));
         $$->subtok=eNNULLTEST|eUNIQUE;
     }
   | NOT NULLX PRIMARY KEY
    {
         lprintf ("column_def_opt <-- NOT NULLX PRIMARY KEY");
         $$=(struct SQLvalue *)malloc(sizeof(struct SQLvalue));
         $$->subtok=eNNULLTEST|ePRIMARY;
     }
   | DEFAULT literal
     { 
         lprintf ("column_def_opt <-- DEFAULT literal"); 
         $$=(struct SQLvalue *)malloc(sizeof(struct SQLvalue));
         $$->subtok=eDEFAULT|$2->subtok;
         $$->value.intval   =$2->value.intval;
         $$->value.floatval =$2->value.floatval;
         $$->value.strval   =$2->value.strval;
         $$->value.dimensions[0]=$2->value.dimensions[0];
         $$->value.dimensions[1]=$2->value.dimensions[1];
         $$->value.dimensions[2]=$2->value.dimensions[2];
     }
   |  DEFAULT NULLX        {
         lprintf ("column_def_opt <-- DEFAULT NULLX"); 
         $$=(struct SQLvalue *)malloc(sizeof(struct SQLvalue));
         $$->subtok=eDEFAULT|eNULL;
     }
   | DEFAULT USER          { 
         lprintf ("column_def_opt <-- DEFAULT USER"); 
         $$=(struct SQLvalue *)malloc(sizeof(struct SQLvalue));
         $$->subtok=eDEFAULT|eUSER;
         $$->value.strval=$2;
     }
/*   | CHECK '(' search_condition ')'      {
         lprintf ("column_def_opt <-- CHECK '(' search_condition ')'");
         $$=(struct SQLvalue *)malloc(sizeof(struct SQLvalue));
         strcpy($$,"CH:"); 
     }
   | REFERENCES table                    {
         lprintf ("column_def_opt <-- REFERENCES table"); 
         $$=(struct SQLvalue *)malloc(sizeof(struct SQLvalue));

     }
   | REFERENCES table '(' column_commalist ')'   {
        lprintf ("column_def_opt <--  REFERENCES table '(' column_commalist ')' "); 
         $$=(struct SQLvalue *)malloc(sizeof(struct SQLvalue));
     }
    */
   ;


column_commalist:
       column {
         $$=$1;
         lprintf ("column_commalist <-- column");
       }
   |   column_commalist ',' column 
      {
         $$=$1;
         $$->nextP=$3;
	 
         lprintf ("column_commalist <-- column_commalist ',' column");
      }
   ;


opt_column_commalist:
      /* empty */ { }
    | '(' column_commalist ')' 
     {
         $$=$2;
     }
    ;

privilege_def:
     GRANT privileges ON table TO grantee_commalist opt_with_grant_option 
     {
        $$->subtok=eSECURITY;
        $$->value.intval=$7;
      }
    ;

opt_with_grant_option:
     /* empty */ { }
    |  WITH GRANT OPTION 
     {
       $$=128;
     }
    ;

privileges:
      ALL PRIVILEGES
      {
       $$->subtok=opALL;
      }
    | ALL
      {
       $$->subtok=opALL;
      }
    |  operation_commalist
       {
         $$=$1;
       }
    ;


operation_commalist:
       operation
      {
        $$->subtok=$1->subtok;
      }
    | operation_commalist ',' operation
{

        $$->subtok=$1->subtok|$3->subtok;
}
    ;

operation:
      SELECT {
        $$=(struct SQLvalue*)malloc(sizeof(struct SQLvalue));
        $$->subtok=opSELECT;
       lprintf ("operation <-- SELECT");
       }
    | INSERT {
        $$=(struct SQLvalue*)malloc(sizeof(struct SQLvalue));

        $$->subtok=opINSERT;
       lprintf ("operation <-- INSERT");
    }
    | DELETE {
        $$=(struct SQLvalue*)malloc(sizeof(struct SQLvalue));
        $$->subtok=opDELETE;
       lprintf ("operation <-- DELETE");
    }

    | DROP {
        $$=(struct SQLvalue*)malloc(sizeof(struct SQLvalue));
        $$->subtok=opDELETE;
       lprintf ("operation <-- DELETE");
     }
    /*    | REFERENCES opt_column_commalist*/
    ;


grantee_commalist:
    grantee{
      lprintf ("grantee_commalist <--   grantee");
      $$=(struct SQLvalue*)mymalloc(sizeof(struct SQLvalue));
      $$->value.strval=$1->value.strval;
      $$->nextP=NULL;
    }
    | grantee_commalist ',' grantee {
      struct SQLvalue *lastP=NULL,*searchP=$3;
      lprintf ("grantee_commalist <--  grantee_commalist ',' grantee ");

       while (searchP) {
          lastP=searchP;
          searchP=searchP->nextP; 
       }   
       lastP->nextP=(struct SQLvalue*)mymalloc(sizeof(struct SQLvalue));
       lastP->nextP->value.strval=$3->value.strval;
       lastP->nextP->nextP=NULL;
       memcpy(lastP->nextP,$3,sizeof(struct SQLvalue));
    }
    ; 

grantee:
    PUBLIC {
      lprintf ("grantee <--  PUBLIC");
      $$->value.strval=(char*)malloc(7);
      strcpy($$->value.strval,"PUBLIC");
       }
    | user {
      lprintf ("grantee <--  user ");
      $$->value.strval=$1;
    }
     ; 

sql: cursor_def
     {
      $$=$1;
     }

     ;

cursor_def:
DECLARE cursor CURSOR FOR query_exp 
     {
       /*opt_order_by_clause*/
        $$=(struct SQLvalue*)malloc(sizeof(struct SQLvalue));
        $$->subtok=eCURSOR;
        $$->nextP=$5;
     }
     ;


sql:
     manipulative_statement{
       $$=$1;
      lprintf ("sql <-- manipulative_statement");
     }
     ; 

manipulative_statement:
      close_statement
{
   $$=$1;
}
   |
    create_idx_statement 
   {
     $$=$1;
   }
    | commit_statement
{
   $$=$1;
}
    | delete_statement_positioned
{
   $$=$1;
}
    | delete_statement_searched
{
   $$=$1;
}
    | fetch_statement
{
   $$=$1;
}
    | insert_statement{
        lprintf ("manipulative_statement <--  insert_statement");
         $$=$1;
      }
    | open_statement 
{
   $$=$1;
}
    | rollback_statement
{
   $$=$1;
}
| query_spec {/*select_statement*/
      $$=$1;
      lprintf ("manipulative_statement <--  select_statement");
    }
    | update_statement_positioned 
{
   $$=$1;
}
    | update_statement_searched 
{
   $$=$1;
}

    ;   

close_statement:
       CLOSE cursor
       {
           $$=(struct SQLvalue*)malloc (sizeof(struct SQLvalue));
           $$->subtok=eCURSOR;         
           $$->value.strval=$2->value.strval;
       }
     ;

commit_statement:
       COMMIT WORK
        {
           $$->subtok=eNULL;
        }
     ;

delete_statement_positioned:
       DELETE FROM table WHERE CURRENT OF cursor  
      {
          $$=(struct SQLvalue*)malloc(sizeof(struct SQLvalue));
          $$->value.strval=$3->value.strval;
          $$->nextP=(struct SQLvalue*)malloc(sizeof(struct SQLvalue));
          $$->value.strval=$7->value.strval;
          $$->subtok=opDELETE;
          $$->nextP->subtok=eCURSOR;
          $$->nextP->nextP=NULL;
          
      }
      ;

delete_statement_searched:
       DELETE FROM table opt_where_clause 
     {
        $$=$4;
     }
      ;


fetch_statement:
      FETCH cursor INTO target_commalist    
     {
        $$=$4;
     }
   ;

insert_statement:
      INSERT INTO table opt_column_commalist values_or_query_spec{
      lprintf ("insert_statement <-- INSERT INTO table opt_column_commalist values_or_query_spec");
        $$=$4;
      }
     ; 

values_or_query_spec:
      VALUES '(' insert_atom_commalist ')'{
      lprintf ("values_or_query_spec <--   VALUES '(' insert_atom_commalist ')'");
          $$=$3;
      }
      | query_spec {
          $$=$1;
      lprintf ("values_or_query_spec <--  query_spec ");
}
     ; 

insert_atom_commalist:
      insert_atom{
      lprintf ("insert_atom_commalist <--   insert_atom");
        $$=$1;
        $$->nextP=NULL;
      }
      | insert_atom_commalist ',' insert_atom {
       struct SQLvalue *lastP=NULL,*searchP=$3;
      lprintf ("insert_atom_commalist <--  insert_atom_commalist ',' insert_atom ");
       while (searchP) {
          lastP=searchP;
          searchP=searchP->nextP; 
       }   
       lastP->nextP=(struct SQLvalue*)mymalloc(sizeof(struct SQLvalue));
       lastP->nextP->nextP=NULL;
       memcpy(lastP->nextP,$3,sizeof(struct SQLvalue));
      }
     ; 

insert_atom:
       atom{
      lprintf ("insert_atom <--   atom");
      
         $$=$1;
       }
      | NULLX {
      lprintf (" insert_atom <--  NULLX ");
        $$=(struct SQLvalue*)malloc(sizeof(struct SQLvalue));
        $$->subtok=eNULL;
      }
     ; 

open_statement:
     OPEN cursor
     {
       $$->value.strval=$2->value.strval;
       $$->subtok=eCURSOR;
     }
     ;


rollback_statement:
       ROLLBACK WORK
      {
       $$->subtok=eCURSOR;
      }
     ;

query_spec:
     SELECT opt_all_distinct selection FROM table_exp
     {
        lprintf ("query_spec <--    SELECT opt_all_distinct selection FROM table_exp");
     }
     ;

create_idx_statement:
     CREATE INDEX index ON table USING opt_column_commalist
     {
         lprintf("create_idx_statement <-- CREATE INDEX name ON table '(' opt_column_commalist ')'");
         $$=$7;
     }
     ;

opt_all_distinct:
       /* empty */ { }
      | ALL {
         lprintf ("opt_all_distinct <--  ALL");
         $$=opALL;

         }
      | DISTINCT {
         $$=opDISTINCT;
         lprintf ("opt_all_distinct <--  DISTINCT ");
      }
      ; 

update_statement_positioned:
       UPDATE table SET assignment_commalist  WHERE CURRENT OF cursor
        {
           $$=$4;
        }
     ;

assignment_commalist:
	/* empty */ { }
       | assignment 
          {

           $$=$1; 

          }
       | assignment_commalist ',' assignment
          {
           struct SQLvalue *searchP=$3,*lastP=NULL;
           lprintf ("target_commalist <--  target_commalist ',' target");
            while (searchP) {
               lastP=searchP;
               searchP=searchP->nextP; 
            }   
           lastP->nextP=(struct SQLvalue *)mymalloc(sizeof(struct SQLvalue));
           lastP->nextP->nextP=NULL;
           lastP->nextP->subtok=$3->subtok;
           lastP->nextP->value.strval=$3->value.strval;

          }
       ;

assignment:
         column '=' scalar_exp
       {

            $$=(struct SQLvalue*)malloc(sizeof(struct SQLvalue));
            $$->subtok=eNULL;
            $$->value.strval=$1->value.strval;
            $$->value.intval=eCOLUMN;
            $$->nextP=$3;
       }
      | column '=' NULLX
         {  
            $$=(struct SQLvalue*)malloc(sizeof(struct SQLvalue));
            $$->subtok=eNULL;
            $$->value.strval=$1->value.strval;
            $$->value.intval=eCOLUMN;
            $$->nextP=NULL;
         }
      ;

update_statement_searched:
        UPDATE table SET assignment_commalist opt_where_clause
         {
            $$=$4;
         }
      ;

target_commalist:
     target
        {
        lprintf ("target_commalist <--   target");
        $$=$1;
        $$->nextP=NULL;
        }
     | target_commalist ',' target
        {

       struct SQLvalue *searchP=$3,*lastP=NULL;
       $$=$1; 
      lprintf ("target_commalist <--  target_commalist ',' target");
       while (searchP) {
          lastP=searchP;
          searchP=searchP->nextP; 
       }   
       lastP->nextP=(struct SQLvalue *)mymalloc(sizeof(struct SQLvalue));
       lastP->nextP->nextP=NULL;
       lastP->nextP->subtok=$3->subtok;
       lastP->nextP->value.strval=$3->value.strval;
       }
     ; 

target:
	parameter_ref
      {
        $$=(struct SQLvalue*)malloc(sizeof(struct SQLvalue));
        $$->subtok=$1->subtok;
      }
     ;

opt_where_clause:
      /*empty*/ { }
     | where_clause
         {
           $$=$1;
         }
      ;

query_exp:
        query_term
   {
     $$=$1;
   }
	/*
      |  query_exp UNION query_term
      |  query_exp EXCEPT query_term
        */
     ;

query_term:
     query_spec
      {
        $$=$1;
      }
     | '(' query_exp ')'
      {
        $$=$2;
       }
     ;



selection:
        scalar_exp_commalist {
      lprintf ("selection <--  scalar_exp_commalist ");
        $$=$1;
        }
     | '*' {
      lprintf ("selection <--  '*' ");
       $$=(struct SQLvalue*)malloc(sizeof(struct SQLvalue));
       $$->subtok=ALL;
     }
     ; 


table_exp:
     from_clause  opt_where_clause  opt_group_by_clause opt_having_clause{
      $$=$1;
      lprintf ("table_exp <--  from_clause  opt_where_clause  opt_group_by_clause opt_having_clause");
       
     }
     ;  

from_clause:
       table_ref_commalist 
      {
      lprintf ("from_clause <-- table_ref_commalist ");
        $$=$1;
      
      }
     ; 

table_ref_commalist:
      table_ref{
      lprintf ("table_ref_commalist <--    table_ref");
        $$=(struct SQLvalue*)mymalloc(sizeof(struct SQLvalue));
        $$->value.strval=$1->value.strval;
        $$->subtok=eTABLE;
        $$->nextP=NULL;
        $$=$1;
      }
      | table_ref_commalist ',' table_ref{ 
      struct SQLvalue *searchP=$3,*lastP=NULL;
      $$=$1;
      lprintf ("table_ref_commalist <--  table_ref_commalist ',' table_ref");
       while (searchP) {
          lastP=searchP;
          searchP=searchP->nextP; 
       }   
       lastP->nextP=(struct SQLvalue*)mymalloc(sizeof(struct SQLvalue));
       lastP->nextP->nextP=NULL;
       lastP->nextP->subtok=eTABLE;
       lastP->nextP->value.strval=$3->value.strval;
       $$->nextP=$3;
      }
     ; 

table_ref:
      table {
         lprintf ("table_ref <--    table");
          $$=(struct SQLvalue*)malloc(sizeof(struct SQLvalue));
          $$->value.strval=$1->value.strval;
          $$->subtok=eTABLE;
         $$->nextP=NULL;
        }
     |  table range_variable 
        {
          $$=(struct SQLvalue*)malloc(sizeof(struct SQLvalue));
          $$->value.strval=$1->value.strval;
          $$->subtok=eTABLE;
          $$->nextP=(struct SQLvalue*)malloc(sizeof(struct SQLvalue));
          $$->nextP->subtok=eRANGE;
          $$->nextP->value.strval=$2;
        }   
     ;

where_clause:
         WHERE search_condition
    {
      lprintf ("where_clause <-- WHERE search_condition ");
           $$=$2;

     }
     ;

opt_group_by_clause:
    /*empty*/ 
     {
     }

      | GROUP BY column_ref_commalist
       {
         lprintf ("opt_group_by_clause <--  GROUP BY column_ref_commalist");
         $$=$3;  
         $$->subtok=eGROUP;
       }
     ; 

column_ref_commalist:
     column_ref {
      lprintf ("column_ref_commalist <--   column_ref");
       $$=(struct SQLvalue*)malloc(sizeof(struct SQLvalue));
       $$->nextP=NULL;
       $$->subtok=eCOLUMN;
       $$->value.strval=$1->value.strval;
     }
     | column_ref_commalist ',' column_ref {
       struct SQLvalue *lastP=NULL,*searchP=$1;
       lprintf ("column_ref_commalist <--  column_ref_commalist ',' column_ref ");
       while (searchP) {
          lastP=searchP;
          searchP=searchP->nextP; 
       }   
       lastP->nextP=(struct SQLvalue*)mymalloc(sizeof(struct SQLvalue));
       lastP->nextP->nextP=NULL;
       $$->subtok=eCOLUMN;
       $$->value.strval=$3->value.strval;

     }
     ; 

opt_having_clause:
     /*empty */ {}

     | HAVING search_condition
        {
           $$=$2;
          lprintf ("opt_having_clasue <-- HAVING search_condition ");

        }
     ;

search_condition:
      search_condition OR search_condition {
        lprintf ("search_condition <-- search_condition OR search_condition ");
        $$=(struct SQLvalue*)malloc(sizeof(struct SQLvalue));
        $$->subtok=opOR;
        $$->leftP=$1;
        $$->rightP=$3;
     }
| search_condition AND search_condition 
    {
      lprintf ("search_condition <-- search_condition AND search_condition  ");
      $$=(struct SQLvalue*)malloc(sizeof(struct SQLvalue));
      $$->subtok=opAND;
      $$->leftP=$1;
      $$->rightP=$3;

    }
| NOT search_condition 
   {
      lprintf ("search_condition <-- NOT search_condition  ");
      $$=(struct SQLvalue*)malloc(sizeof(struct SQLvalue));
      $$->subtok=opNOT;
      $$->nextP=$2;

   }
|  '(' search_condition ')' 
   {
      lprintf ("search_condition <-- '(' search_condition ')' ");
       $$=$2;
       $$->nextP=NULL;
   }
| predicate 
  {
      lprintf ("search_condition <-- predicate ");
       $$=$1;

  }
     ; 

predicate:
       comparison_predicate
        { 
          $$=$1;
        }
     | between_predicate
        { 
          $$=$1;
        }
     | like_predicate
        { 
          $$=$1;
        }
     | test_for_null
        { 
          $$=$1;
        }
     | in_predicate
        { 
          $$=$1;
        }
     | all_or_any_predicate
        { 
          $$=$1;
        }
     | existance_test
        { 
          $$=$1;
        }
     ;

comparison_predicate:
        scalar_exp COMPARISON scalar_exp
        { 
          lprintf ("comparison_predicate <-- scalar_exp COMPARISON scalar_exp");
	  
          $$=$1;
        }
     |  scalar_exp COMPARISON subquery
        { 
          lprintf ("comparison_predicate <-- scalar_exp COMPARISON subquery");
          $$=$1;
        }
     ;

between_predicate:
        scalar_exp NOT BETWEEN scalar_exp AND scalar_exp
        { 
          $$=$1;
        }
     |  scalar_exp BETWEEN scalar_exp AND scalar_exp
        { 
          $$=(struct SQLvalue*)malloc(sizeof(struct SQLvalue));
          $$->subtok=eBETWEEN;
          $$->rightP=(struct SQLvalue*)malloc(sizeof(struct SQLvalue ));
          memcpy($$->rightP,$3,sizeof(struct SQLvalue));
          $$->leftP=(struct SQLvalue*)malloc(sizeof(struct SQLvalue));
          memcpy($$->leftP,$5,sizeof(struct SQLvalue));
        }
     ;

like_predicate:
        column_ref NOT LIKE atom opt_escape
        { 
           $$=(struct SQLvalue*) malloc(sizeof(struct SQLvalue));
           $$->subtok=eNLIKE;
           $$->value.intval=$1->value.intval;
           $$->value.strval=$1->value.strval;
           $$->nextP=$4;
        }
     |  column_ref LIKE atom opt_escape
        { 
           $$=(struct SQLvalue*) malloc(sizeof(struct SQLvalue));
           $$->subtok=eLIKE;
           $$->value.intval=$1->value.intval;
           $$->value.strval=$1->value.strval;
           $$->nextP=$3;
        }
     ;

opt_escape:
        /* empty */ { }
     |  ESCAPE atom
        { 
          $$=(struct SQLvalue*)malloc(sizeof(struct SQLvalue));
          $$->subtok=eESCAPE;
          $$->nextP=$2;
        }
     ;

test_for_null:
          column_ref IS NOT NULLX
        {
           $$=(struct SQLvalue*) malloc(sizeof(struct SQLvalue));
           $$->subtok=eNNULLTEST;
           $$->value.intval=$1->value.intval;
           $$->value.strval=$1->value.strval;
	}
     |   column_ref IS NULLX    
        {
	  /* column_ref semantics are in "value" 
             by strval for the name and intval has eCOLUMN*/
           $$=(struct SQLvalue*) malloc(sizeof(struct SQLvalue));
           $$->subtok=eNULLTEST;
           $$->value.intval=$1->value.intval;
           $$->value.strval=$1->value.strval;
        }
      ;

in_predicate:
        scalar_exp NOT INTO '(' subquery ')'
        { 
          $$=$1;
        }
     |  scalar_exp INTO '(' subquery ')'
        { 
          $$=$1;
        }
     |  scalar_exp NOT INTO '(' atom_commalist ')'
        { 
          $$=$1;
        }
     |  scalar_exp  INTO '(' atom_commalist ')'
       {
          $$=$1;
       }   
     ;

atom_commalist:
      atom {
         lprintf ("atom_commalist <--    atom ");
        
         $$=$1; 
         $$->nextP=NULL;
      }
      | atom_commalist ',' atom {
          struct SQLvalue *lastP=NULL,*searchP=$1;
          lprintf ("atom_commalist <--  atom_commalist ',' atom ");
          while (searchP) {
              lastP=searchP;
              searchP=searchP->nextP;
          }
          lastP->nextP=(struct SQLvalue*)mymalloc(sizeof(struct SQLvalue));
          memcpy(lastP->nextP,$3,sizeof(struct SQLvalue));
          lastP->nextP->nextP=NULL;
      }
      ; 

all_or_any_predicate:
     scalar_exp COMPARISON any_all_some subquery
     {
         $$=$1;
         $$->nextP=(struct SQLvalue*)malloc(sizeof(struct SQLvalue));
         $$->nextP->subtok=$3;
         $$->nextP->nextP=$4;
     }
     ;

any_all_some:
     ANY {
       lprintf ("data_type <--  ANY");
        $$=opANY;
     }
    |  ALL {
      lprintf ("data_type <--  ALL ");
      $$=opALL;
    }
    |  SOME {
      lprintf ("data_type <--  SOME ");
      $$=opSOME;
    }
    ; 

existance_test:
      EXISTS subquery
      {
         $$=$2;
      }
     ;

subquery:
       '(' SELECT opt_all_distinct selection FROM table_exp ')'
      {
         $$=$4;
      }
    ;

scalar_exp:
       scalar_exp '+' scalar_exp
        {
          lprintf ("scalar_exp <-- scalar_exp '+' scalar_exp");
	  
          $$=(struct SQLvalue*) malloc(sizeof(struct SQLvalue));
          $$->subtok=opAdd;
          $$->nextP=$1;
          $$->nextP->nextP=$3;
          $$->nextP->nextP->nextP=NULL;
        }
     | scalar_exp '-' scalar_exp
        {
          lprintf ("scalar_exp <-- scalar_exp '-' scalar_exp");
          $$=(struct SQLvalue*) malloc(sizeof(struct SQLvalue));
          $$->subtok=opSubtract;
          $$->nextP=$1;
          $$->nextP->nextP=$3;
          $$->nextP->nextP->nextP=NULL;
        }
     | scalar_exp '*' scalar_exp
        {
          lprintf ("scalar_exp <-- scalar_exp '*' scalar_exp");
          $$=(struct SQLvalue*)malloc(sizeof(struct SQLvalue));
          $$->subtok=opMultiply;
          $$->nextP=$1;
          $$->nextP->nextP=$3;
          $$->nextP->nextP->nextP=NULL;
        }
     | scalar_exp '/' scalar_exp
        {
          lprintf ("scalar_exp <-- scalar_exp '/' scalar_exp");
          $$=(struct SQLvalue*)malloc(sizeof(struct SQLvalue));
          $$->subtok=opDivide;
          $$->nextP=$1;
          $$->nextP->nextP=$3;
          $$->nextP->nextP->nextP=NULL;
        }
     | '+' scalar_exp %prec UMINUS { $$=$2;}

     | '-' scalar_exp %prec UMINUS { $$=$2;}
     | atom {
          lprintf ("scalar_exp <--  atom");
          if ($1->subtok==eUSER) {
             lprintf ("Illegal reference to user %s", $1->value.strval);
             yyerror("Illegal reference to user");
          }
          $$=$1;
       }
     | column_ref {
         /*
          intval:eCOLUMN,strval:name
            */
          lprintf ("scalar_exp <-- column_ref");
          $$=(struct SQLvalue*) malloc(sizeof(struct SQLvalue));
          $$->nextP=NULL;
          $$->subtok=eCOLUMN;
          $$->value.strval=$1->value.strval;
     }
     | function_ref 
        {
          $$=$1;
        }
     | '(' scalar_exp ')'
         {
          lprintf ("scalar_exp <--  '(' scalar_exp ')'");
            $$=$2;
         }

     ;

scalar_exp_commalist:
         scalar_exp
         {
           $$=$1;
           $$->nextP=NULL;
         }
     |   scalar_exp_commalist ',' scalar_exp
         {
           void * temp;
           $$=$1;
           temp = $$->nextP;
           $$->nextP=(struct SQLvalue*) malloc(sizeof(struct SQLvalue));

           memcpy($$->nextP,$3,sizeof(struct SQLvalue));
           $$->nextP->nextP=temp;
         }

     ;

atom:
      parameter_ref 
       {
          $$=(struct SQLvalue*)malloc(sizeof(struct SQLvalue));
          $$->nextP=NULL;
          $$->subtok=$1;
	   /* paramater_ref is just a subtok */
           lprintf ("atom <--  parameter_ref");
       }
      | literal 
      {
	/* lhs is a nextP user */
        lprintf ("atom <-- literal ");
        $$=$1;
      }
          
      | USER {
        $$=(struct SQLvalue*)malloc(sizeof(struct SQLvalue));
        lprintf ("atom <--  USER");
        $$->subtok=eUSER; 
      }
     ;


parameter_ref:
    parameter
      {
        $$=$1;
      }   
     | parameter parameter
      {
          $$=$1;
      }
    /*  | parameter INDICATOR parameter*/
     ;

function_ref:
       AMMSC '(' '*' ')' /* count(*) */
        {
           $$=(struct SQLvalue*)malloc(sizeof(struct SQLvalue));
           $$->subtok=opALL;

        }
     | AMMSC '(' DISTINCT column_ref ')'
        {
           $$=(struct SQLvalue*)malloc(sizeof(struct SQLvalue));
           $$->value.intval=opDISTINCT;
           $$->subtok=eCOLUMN;
           $$->value.strval=$4->value.strval;
        }
     | AMMSC '(' ALL scalar_exp ')'
        {
           $$=(struct SQLvalue*)malloc(sizeof(struct SQLvalue));
           $$->subtok=opALL;
           $$->value.intval=eCOLUMN;
           $$->nextP=$4;
        }
     | AMMSC '(' scalar_exp ')'
        {
           $$=$3;
        }
     ;
  
literal:
       STRING{
          lprintf ("literal <--     STRING");
          $$=(struct SQLvalue*)malloc(sizeof(struct SQLvalue));
          $$->value.strval=(char*)mymalloc(sizeof(char)*(strlen($1)+1)) ;
          strcpy($$->value.strval,$1);
          $$->subtok=STRING;
       }
      |     INTNUM {
          $$=(struct SQLvalue*)malloc(sizeof(struct SQLvalue));
          lprintf ("literal <--     INTNUM  ");
          $$->value.intval=$1;
          $$->subtok=INTNUM;
      }
      |   APPROXNUM {
          $$=(struct SQLvalue *)malloc(sizeof(struct SQLvalue));
          lprintf ("data_type <--   APPROXNUM ");
      /* $$.approxnum=atof($1);*/
          $$->value.floatval=$1;
          $$->subtok=APPROXNUM;   
      }
   ; 


column_ref:
     NAME {
      lprintf ("column_ref <-- NAME[%d]\n",strlen($1));
       $$=(struct SQLvalue *)malloc(sizeof(struct SQLvalue));
       $$->nextP=NULL;
       $$->subtok=eCOLUMN;
       $$->value.strval=(char*)malloc(48) ;
       strcpy($$->value.strval,$1);

     }
      | NAME '.' NAME {
       lprintf ("column_ref <-- NAME '.' NAME");
       $$=(struct SQLvalue *)malloc(sizeof(struct SQLvalue));
       $$->value.strval=(char*)mymalloc(sizeof(char)*(strlen($1)+2+strlen($3))) ;
       strcpy($$->value.strval,$1);
       strcat($$->value.strval,".");
       strcat($$->value.strval,$3);
       $$->subtok=eCOLUMN;
      }
      | NAME '.' NAME '.' NAME   /* user.table.column */ {
       lprintf ("column_ref <-- NAME '.' NAME");
       $$=(struct SQLvalue *)malloc(sizeof(struct SQLvalue));
       $$->value.strval=(char*)
         mymalloc(sizeof(char)*
            (strlen($1)+4+strlen($3)+strlen($5))) ;
       strcpy($$->value.strval,$1);
       strcat($$->value.strval,".");
       strcat($$->value.strval,$3);
       strcat($$->value.strval,".");
       strcat($$->value.strval,$5);
       $$->subtok=eCOLUMN;
      }
     ;  

table:
	 NAME {

        lprintf ("table <-- name <%s>\n",$1);
       $$=(struct SQLvalue *)malloc(sizeof(struct SQLvalue));
        $$->nextP=NULL;
       $$->value.strval=
        (char*)mymalloc(strlen($1)+8);
        strcpy($$->value.strval,$1);
        $$->subtok=eTABLE;
    }
    | NAME '.' NAME {
       lprintf ("table <-- NAME '.' NAME");
       $$=(struct SQLvalue *)malloc(sizeof(struct SQLvalue));
       $$->value.strval=
        (char*)mymalloc(sizeof(char)*((strlen($1)+2+strlen($3))));
       strcpy($$->value.strval,$1);
       strcat($$->value.strval,".");
       strcat($$->value.strval,$3);
       $$->subtok=eTABLE;
   }
   ;

data_type:
      CHARACTER {
          $$=(struct SQLvalue *)malloc(sizeof(struct SQLvalue));
          lprintf ("data_type <--  CHARACTER");
          $$->subtok=eCHARTYPE;
          $$->value.dimensions[0]=-1;
          $$->value.dimensions[1]=-1;
          $$->value.dimensions[2]=-1;
          $$->nextP=NULL;
	  
      } 
      |   CHARACTER '(' INTNUM ')' {
          lprintf ("data_type <--  CHARACTER '(' INTNUM ')'");
          $$=(struct SQLvalue *)malloc(sizeof(struct SQLvalue));
          $$->value.dimensions[0]=$3;
          $$->value.dimensions[1]=-1;
          $$->value.dimensions[2]=-1;
          $$->subtok=eCHARTYPE;
          $$->nextP=NULL;
      } 
      |   NUMERIC {
          lprintf ("data_type <--   NUMERIC ");
          $$=(struct SQLvalue *)malloc(sizeof(struct SQLvalue));
          $$->subtok=eNUMERIC;
          $$->value.dimensions[1]=-1;
          $$->value.dimensions[1]=-1;
          $$->value.dimensions[2]=-1;
          $$->value.intval=eCHARTYPE;
          $$->nextP=NULL;
      }
      |   NUMERIC '(' INTNUM ')' {
          lprintf ("data_type <--   NUMERIC '(' INTNUM ')' ");
          $$=(struct SQLvalue *)malloc(sizeof(struct SQLvalue));
          $$->value.dimensions[0]=$3;
          $$->value.dimensions[1]=-1;
          $$->value.dimensions[2]=-1;
          $$->subtok=eNUMERIC;
          $$->nextP=NULL;
      }
      |   NUMERIC '(' INTNUM ',' INTNUM ')' {
          lprintf ("data_type <--   NUMERIC '(' INTNUM ',' INTNUM ')' ");
          $$=(struct SQLvalue *)malloc(sizeof(struct SQLvalue));
          $$->value.dimensions[0]=$3;
          $$->value.dimensions[1]=$5;
          $$->value.dimensions[2]=-1;
          $$->subtok=eNUMERIC;
          $$->nextP=NULL;
      }
      |   DECIMAL {
          lprintf ("data_type <--   DECIMAL ");
          $$=(struct SQLvalue *)malloc(sizeof(struct SQLvalue));
          $$->value.dimensions[0]=-1;
          $$->value.dimensions[1]=-1;
          $$->value.dimensions[2]=-1;
          $$->subtok=eDECIMAL;
          $$->nextP=NULL;
      }
      |   DECIMAL  '(' INTNUM ')' {
          lprintf ("data_type <--   DECIMAL  '(' INTNUM ')' ");
          $$=(struct SQLvalue *)malloc(sizeof(struct SQLvalue));
          $$->value.dimensions[0]=$3;
          $$->value.dimensions[1]=-1;
          $$->value.dimensions[2]=-1;
          $$->subtok=eDECIMAL;
          $$->nextP=NULL;
      }
      |   DECIMAL  '(' INTNUM ',' INTNUM ')' {
          $$=(struct SQLvalue *)malloc(sizeof(struct SQLvalue));
          lprintf ("data_type <--   DECIMAL  '(' INTNUM ',' INTNUM ')' ");
          $$->value.dimensions[0]=$3;
          $$->value.dimensions[1]=$3;
          $$->value.dimensions[2]=-1;
          $$->subtok=eDECIMAL;
      }
      |   INTEGER {
          $$=(struct SQLvalue *)malloc(sizeof(struct SQLvalue));
          lprintf ("data_type <--   INTEGER ");
          $$->value.dimensions[0]=-1;
          $$->value.dimensions[1]=-1;
          $$->value.dimensions[2]=-1;
          $$->subtok=eINTEGER;
          $$->nextP=NULL;
      }
      |   SMALLINT {
          lprintf ("data_type <--   SMALLINT ");
          $$=(struct SQLvalue *)malloc(sizeof(struct SQLvalue));
          $$->value.dimensions[0]=-1;
          $$->value.dimensions[1]=-1;
          $$->value.dimensions[2]=-1;
          $$->value.intval=eSMALLINT;
          $$->nextP=NULL;
      }
      |   FLOAT {
          $$=(struct SQLvalue *)malloc(sizeof(struct SQLvalue));
          lprintf ("data_type <--   FLOAT ");
          $$->value.floatval=$1;
          $$->subtok=eFLOAT;
          $$->nextP=NULL;
      }
      |   FLOAT '(' INTNUM ')' {
          $$=(struct SQLvalue *)malloc(sizeof(struct SQLvalue));
          $$->value.dimensions[0]=$3;
          $$->value.dimensions[1]=-1;
          $$->value.dimensions[2]=-1;
          lprintf ("data_type <--   FLOAT '(' INTNUM ')' ");
          $$->subtok=eFLOAT;
          $$->nextP=NULL;
      }
      |   REAL {
          lprintf ("data_type <--   REAL ");
          $$->value.dimensions[0]=-1;
          $$->value.dimensions[1]=-1;
          $$->value.dimensions[2]=-1;
          $$->subtok=eREAL;
          $$->nextP=NULL;
      }
      | DOUBLE PRECISION {
          lprintf ("data_type <-- DOUBLE PRECISION ");
          $$->value.dimensions[0]=-1;
          $$->value.dimensions[1]=-1;
          $$->value.dimensions[2]=-1;
          $$->subtok=eDOUBLEPREC;
          $$->nextP=NULL;
      }
      | NCHAR   '(' INTNUM ')' {
          lprintf ("data_type <-- NCHAR ( INTNUM )");
          $$->value.dimensions[0]=$3;
          $$->value.dimensions[1]=-1;
          $$->value.dimensions[2]=-1;
          $$->subtok=eCHARTYPE;
          $$->nextP=NULL;
      }
      | NCHAR VARYING  '(' INTNUM ')' {
          lprintf ("data_type <-- NCHAR VARYING ( int )");
          $$->value.dimensions[0]=$4;
          $$->value.dimensions[1]=-1;
          $$->value.dimensions[2]=-1;
          $$->subtok=eCHARTYPE;
          $$->nextP=NULL;
      }
      | NATIONAL CHAR VARYING  '(' INTNUM ')' {
          lprintf ("data_type <-- NATIONAL CHAR ( int )");
          $$->value.dimensions[0]=$5;
          $$->value.dimensions[1]=-1;
          $$->value.dimensions[2]=-1;
          $$->subtok=eCHARTYPE;
          $$->nextP=NULL;
      }
      | NATIONAL CHARACTER VARYING  '(' INTNUM ')' {
          lprintf ("data_type <-- NCHAR ( int )");
          $$->value.dimensions[0]=$5;
          $$->value.dimensions[1]=-1;
          $$->value.dimensions[2]=-1;
          $$->subtok=eCHARTYPE;
          $$->nextP=NULL;
     }
      |  CHARACTER VARYING  '(' INTNUM ')' {
          lprintf ("data_type <-- CHARACTER VARYING ( int )");
          $$->value.dimensions[0]=$4;
          $$->value.dimensions[1]=-1;
          $$->value.dimensions[2]=-1;
          $$->subtok=eCHARTYPE;
          $$->nextP=NULL;
       }
      | CHAR VARYING  '(' INTNUM ')' {
          lprintf ("data_type <-- CHAR VARYING ( int )");
          $$->value.dimensions[0]=$4;
          $$->value.dimensions[1]=-1;
          $$->value.dimensions[2]=-1;
          $$->subtok=eCHARTYPE;
          $$->nextP=NULL;
      }
      | VARCHAR '(' INTNUM ')' {
          lprintf ("data_type <-- VARCHAR ( int )");
          $$->value.dimensions[0]=$3;
          $$->value.dimensions[1]=-1;
          $$->value.dimensions[2]=-1;
          $$->subtok=eCHARTYPE;
          $$->nextP=NULL;
      }
      | BIT  '(' INTNUM ')' {
          lprintf ("data_type <-- BIT ( int )");
          $$->value.dimensions[0]=$3;
          $$->value.dimensions[1]=-1;
          $$->value.dimensions[2]=-1;
          $$->subtok=eBOOLEAN;
          $$->nextP=NULL;
      }
      | BIT VARYING  '(' INTNUM ')' {
          lprintf ("data_type <-- BIT VARYING ( int )");
          $$->value.dimensions[0]=$4;
          $$->value.dimensions[1]=-1;
          $$->value.dimensions[2]=-1;
          $$->subtok=eBOOLEAN;
          $$->nextP=NULL;
      }


   ; 

column:
   NAME {
      lprintf ("column <- NAME\n"); 
       $$=(struct SQLvalue*)malloc(sizeof(struct SQLvalue));
       $$->subtok=eCOLUMN;
       /*       $$->value.strval =(char*)malloc(strlen($1)+1) ;*/
       $$->value.strval =(char*)malloc(48) ;
       strcpy($$->value.strval,$1);
          $$->nextP=NULL;
   }
   ;

cursor: NAME
     {
       $$=(struct SQLvalue*)malloc(sizeof(struct SQLvalue));
       $$->value.strval=(char*)malloc(strlen($1)+1);
       strcpy($$->value.strval,$1);
       $$->subtok=eCURSOR;
     }
     ;
schema_name: NAME
    {
       $$=(struct SQLvalue*)malloc(sizeof(struct SQLvalue));
       $$->value.strval=(char*)malloc(strlen($1)+1);
       strcpy($$->value.strval,$1);
       $$->subtok=eCURSOR;
     }
     ;

parameter:
    PARAMETER
    {
      $$=(struct SQLvalue*)malloc(sizeof(struct SQLvalue));
      $$->value.strval=(char*)malloc(strlen($1)+1);
      strcpy($$->value.strval,$1);
      $$->subtok=ePARAMATER;
    }
     ;

range_variable:
       NAME
    {
      $$=$1;
    }
     ;


user: NAME {
      lprintf ("user <--  NAME ");
      $$=$1;
    }
   ;     

index: NAME {
     lprintf ("index <--  NAME ");
      $$=$1;
    }
   ;     


%%
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
