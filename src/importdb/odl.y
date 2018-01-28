%{



#define DATATYPEP struct descriptor *
#define DATASIZE  sizeof(struct descriptor)

struct descriptor
{
   struct descriptor *nextP;

};
%}

%union {
  double floatval;
  unsigned long uLongVal;
  signed long   LongVal ;
  char * stringP;
  struct descriptor *nextP;
}

%token SEMICOLON DBLCOLON COLON OPCURLBRKT CLCURLBRKT CONST COMMA 
%token EQUALS OPSQBRKT CLSQBRKT OPPAREN CLPAREN CLASS EXTENDS
%token XOR_OP OR_OP AND_OP SHRITE_OP SHLEFT_OP
%token INTERFACE CONTEXT IN OUT INOUT VOID RELATIONSHIP INVERSE
%token ONEWAY RAISES EXCEPTION STRUCT UNION SWITCH READONLY
%token ATTRIBUTE KEY KEYS SET LIST BAG DICTIONARY
%token ARRAY SEQUENCE LESSTHAN GREATERTHAN
%token INTERVAL LONG SHORT UNSIGNED INT FLOAT DOUBLE OCTET STRING
%token TIME DATE TIMESTAMP BOOLEAN TYPEDEF TRUE FALSE CHAR ANY
%token CASE DEFAULT ENUM EXTENT STRING_LITERAL  CHARACTER_LITERAL
%token IDENTIFIER MODULE FLOATING_PT_LITERAL STRING_LITERAL

%type <nextP> unary_operator unary_expr primary_expr mult_expr add_expr
%type <nextP> shift_expr and_expr xor_expr or_expr const_expr
%type <nextP> definition specification type_dcl except_dcl interface
%type <nextP> module class interface_header interface_decl forward_decl
%type <nextP>interface_body  scoped_name inheritance_spec 
%type <nextP> type_property_list interface_body  
%type <nextP> integer_type char_type boolean_type floating_pt_type
%type <nextP> string_type 
%type <nextP> inverse_traversal_path
%type <nextP> rel_collection_type
%type <nextP> coll_spec
%type <nextP> attribute_name
%type <nextP> key_spec
%type <nextP> scoped_name_list target_of_path export
%type <nextP> switch_type_spec
%type <nextP> unsigned_int
%type <nextP> signed_long_int
%type <nextP> signed_int
%type <nextP> coll_type template_type_spec
%type <nextP> base_type_spec
%type <nextP> simple_type_spec
%type <nextP> op_type_spec
%type <nextP> domain_type
%type <nextP> type_spec
%type <nextP> positive_int_const
%type <nextP> op_dcl
%type <nextP> element_spec
%type <nextP> member
%type <nextP> member_list
%type <nextP> const_type
%type <nextP> type_declarator
%type <nextP> unsigned_short_int

%%
specification:
     definition
    | definition specification
    ;
definition:
     type_dcl    SEMICOLON
     | except_dcl SEMICOLON
     | interface SEMICOLON
     | module    SEMICOLON
     | class     SEMICOLON
     ;

interface:
     interface_decl
    |forward_decl
     ;

interface_decl:
     interface_header
     OPCURLBRKT interface_body CLCURLBRKT
     ;

module:
     MODULE IDENTIFIER OPCURLBRKT specification CLCURLBRKT
      { $$=(DATATYPEP)malloc ( DATASIZE); } ;

forward_decl:
     INTERFACE IDENTIFIER
      { $$=(DATATYPEP)malloc ( DATASIZE); } ;

interface_header:
      interface IDENTIFIER inheritance_spec  { $$=(DATATYPEP)malloc ( DATASIZE); }
     | interface IDENTIFIER { $$=(DATATYPEP)malloc ( DATASIZE); }
     ;

class:
     class_header OPCURLBRKT interface_body CLCURLBRKT
      { $$=(DATATYPEP)malloc ( DATASIZE); }
     ;

class_header:
     CLASS IDENTIFIER
     | CLASS IDENTIFIER EXTENDS scoped_name
     | CLASS IDENTIFIER EXTENDS scoped_name inheritance_spec
     | CLASS IDENTIFIER EXTENDS scoped_name inheritance_spec type_property_list
     ;

inheritance_spec:
     scoped_name
     | scoped_name COMMA  inheritance_spec
     ;

const_dcl:
       CONST const_type IDENTIFIER EQUALS const_expr
     ;

const_type: integer_type     { $$=(DATATYPEP)malloc ( DATASIZE); }
     | char_type            { $$=(DATATYPEP)malloc ( DATASIZE); }
     | boolean_type        { $$=(DATATYPEP)malloc ( DATASIZE); }
     | floating_pt_type   { $$=(DATATYPEP)malloc ( DATASIZE); }
     | string_type   { $$=(DATATYPEP)malloc ( DATASIZE); }
     | scoped_name  { $$=(DATATYPEP)malloc ( DATASIZE); }
     ;

const_expr:
     or_expr
     ;

or_expr:
     xor_expr
     | or_expr OR_OP  xor_expr
     ;

xor_expr:
     and_expr
     | xor_expr XOR_OP and_expr
     ;

and_expr:
     shift_expr
     | and_expr AND_OP shift_expr
     ;

shift_expr:
     add_expr
     | shift_expr SHRITE_OP add_expr
     | shift_expr SHLEFT_OP add_expr
     ;

add_expr:
     mult_expr
     | add_expr '+' mult_expr
     | add_expr '-' mult_expr
     ;

mult_expr:
      unary_expr
     | mult_expr '*' unary_expr
     | mult_expr '/' unary_expr
     | mult_expr '%' unary_expr
     ;

unary_expr:
      unary_operator primary_expr
     | primary_expr
     ;

unary_operator:
      '-'      { $$=(DATATYPEP)malloc ( DATASIZE); }
     | '+'     { $$=(DATATYPEP)malloc ( DATASIZE); }
     | '~'    { $$=(DATATYPEP)malloc ( DATASIZE); }
     ;

primary_expr:
      scoped_name
     | literal  { $$=(DATATYPEP)malloc ( DATASIZE); }
     | OPPAREN const_expr CLPAREN
           { $$=(DATATYPEP)malloc ( DATASIZE); }
     ;

literal:
     STRING_LITERAL
     | CHARACTER_LITERAL
     | FLOATING_PT_LITERAL
     | boolean_literal
     ;

boolean_literal:
     TRUE | FALSE
     ;

positive_int_const: const_expr  { $$=(DATATYPEP)malloc ( DATASIZE); }
     ;

type_dcl:
      TYPEDEF type_declarator  { $$=(DATATYPEP)malloc ( DATASIZE); }
     | struct_type    { $$=(DATATYPEP)malloc ( DATASIZE); }
     | union_type     { $$=(DATATYPEP)malloc ( DATASIZE); }
     | enum_type     { $$=(DATATYPEP)malloc ( DATASIZE); }
     ;

type_declarator:
      type_spec declarators
         { $$=(DATATYPEP)malloc ( DATASIZE); }
     ;

type_spec:
      simple_type_spec
      | constr_type_spec   { $$=(DATATYPEP)malloc ( DATASIZE); }
     ;

simple_type_spec:
      base_type_spec
     | template_type_spec
     | scoped_name       { $$=(DATATYPEP)malloc ( DATASIZE); }
     ;

base_type_spec:
     floating_pt_type
     | integer_type   { $$=(DATATYPEP)malloc ( DATASIZE); }
     | char_type     { $$=(DATATYPEP)malloc ( DATASIZE); }
     | boolean_type { $$=(DATATYPEP)malloc ( DATASIZE); }
     | octet_type  { $$=(DATATYPEP)malloc ( DATASIZE); }
     | any_type     { $$=(DATATYPEP)malloc ( DATASIZE); }
     | date_type        { $$=(DATATYPEP)malloc ( DATASIZE); }
     | time_type        { $$=(DATATYPEP)malloc ( DATASIZE); }
     | interval_type    { $$=(DATATYPEP)malloc ( DATASIZE); }
     | timestamp_type  { $$=(DATATYPEP)malloc ( DATASIZE); }
     ;

date_type: DATE
     ;

time_type: TIME
     ;

interval_type: INTERVAL
     ;

timestamp_type:
      TIMESTAMP
     ;

template_type_spec:
     array_type     { $$=(DATATYPEP)malloc ( DATASIZE); }
     | string_type  { $$=(DATATYPEP)malloc ( DATASIZE); }
     | coll_type
       { $$=(DATATYPEP)malloc ( DATASIZE); }
     ;

coll_type:
     coll_spec LESSTHAN simple_type_spec GREATERTHAN   { $$=(DATATYPEP)malloc ( DATASIZE); }
     | DICTIONARY LESSTHAN simple_type_spec COMMA simple_type_spec GREATERTHAN
         { $$=(DATATYPEP)malloc ( DATASIZE); }
     ;

coll_spec:
      SET     { $$=(DATATYPEP)malloc ( DATASIZE); }
     | LIST   { $$=(DATATYPEP)malloc ( DATASIZE); }
     | BAG   { $$=(DATATYPEP)malloc ( DATASIZE); }
     ;

rel_collection_type:
      SET    { $$=(DATATYPEP)malloc ( DATASIZE); }
     | LIST  { $$=(DATATYPEP)malloc ( DATASIZE); }
     | BAG  { $$=(DATATYPEP)malloc ( DATASIZE); }
     ;

constr_type_spec: 
     struct_type
     | union_type
     | enum_type
     ;

declarators:
      declarator
     | declarator COMMA declarators
     ;
declarator:
     simple_declarator
     | complex_declarator
     ;

simple_declarator:
     IDENTIFIER
     ;

complex_declarator:
     array_declarator
     ;

floating_pt_type:
     FLOAT   { $$=(DATATYPEP)malloc ( DATASIZE); }
     | DOUBLE  { $$=(DATATYPEP)malloc ( DATASIZE); }
     ;

integer_type:
     signed_int
     | unsigned_int   { $$=(DATATYPEP)malloc ( DATASIZE); }
     ;
unsigned_int:
     unsigned_long_int   { $$=(DATATYPEP)malloc ( DATASIZE); }
     | unsigned_short_int  { $$=(DATATYPEP)malloc ( DATASIZE); }
     ;

signed_int: signed_long_int
     | signed_short_int  { $$=(DATATYPEP)malloc ( DATASIZE); }
     ;

signed_long_int:
      LONG { $$=(DATATYPEP)malloc ( DATASIZE); }
     ;

signed_short_int:
      SHORT
     ;

unsigned_long_int:
       UNSIGNED LONG
     ;

unsigned_short_int:
      UNSIGNED SHORT
       { $$=(DATATYPEP)malloc ( DATASIZE); }
     ;

char_type:
      CHAR  { $$=(DATATYPEP)malloc ( DATASIZE); }
     ;

boolean_type:
      BOOLEAN  { $$=(DATATYPEP)malloc ( DATASIZE); }
     ;

octet_type:
      OCTET
     ;

any_type:
      ANY
     ;

struct_type:
      STRUCT IDENTIFIER OPCURLBRKT member_list CLCURLBRKT
     ;

member_list:
     member
     | member member_list
       { $$=(DATATYPEP)malloc ( DATASIZE); }
     ;
member:
     type_spec declarators
          { $$=(DATATYPEP)malloc ( DATASIZE); }
     ;

union_type: UNION IDENTIFIER SWITCH OPPAREN switch_type_spec CLPAREN OPCURLBRKT switch_body CLCURLBRKT
     ;

switch_type_spec:
     integer_type
     | char_type
     | boolean_type  { $$=(DATATYPEP)malloc ( DATASIZE); }
     | enum_type     { $$=(DATATYPEP)malloc ( DATASIZE); }
     | scoped_name  { $$=(DATATYPEP)malloc ( DATASIZE); }
     ;

switch_body: 
     case
     | case switch_body
     ;

case:
     case_label_list element_spec
     ;

case_label_list:
     case_label
     | case_label case_label_list
     ;

case_label:
     CASE const_expr COLON
     | DEFAULT COLON
     ;

element_spec: 
     type_spec declarator
         { $$=(DATATYPEP)malloc ( DATASIZE); }
      ;

enum_type:
     ENUM IDENTIFIER OPCURLBRKT enumerator_list OPCURLBRKT
     ;

enumerator_list:
     enumerator 
     | enumerator COMMA enumerator_list
     ;

enumerator:
     IDENTIFIER
     ;

array_type:
     array_spec LESSTHAN simple_type_spec COMMA positive_int_const GREATERTHAN
     | array_spec LESSTHAN simple_type_spec GREATERTHAN
     ;

array_spec:
     ARRAY
     | SEQUENCE
     ;
string_type:
      STRING LESSTHAN positive_int_const GREATERTHAN { $$=(DATATYPEP)malloc ( DATASIZE); } 
     | STRING  { $$=(DATATYPEP)malloc ( DATASIZE); }
     ;

array_declarator:
      IDENTIFIER array_size_list
     ;

array_size_list: 
     fixed_array_size
     | fixed_array_size array_size_list
     ;

fixed_array_size:
     OPSQBRKT positive_int_const CLSQBRKT
     ;

type_property_list:
      OPPAREN CLPAREN  { $$=(DATATYPEP)malloc ( DATASIZE); }
     | OPPAREN extent_spec CLPAREN  { $$=(DATATYPEP)malloc ( DATASIZE); }
     | OPPAREN extent_spec key_spec CLPAREN { $$=(DATATYPEP)malloc ( DATASIZE); }
     ;

char_type: CHAR { $$=(DATATYPEP)malloc ( DATASIZE); }
     ;

extent_spec: 
       EXTENT STRING_LITERAL
     ;

key_spec:
      KEY key_list  { $$=(DATATYPEP)malloc ( DATASIZE); }
     | KEYS key_list  { $$=(DATATYPEP)malloc ( DATASIZE); }
     ;

key_list:
       key
     | key COMMA key_list
     ;

key:
       property_name
     | OPPAREN property_list CLPAREN
     ;

property_list:
       property_name
     | property_name COMMA property_list
     ;

property_name:
       IDENTIFIER
      ;

scoped_name:
      IDENTIFIER  { $$=(DATATYPEP)malloc ( DATASIZE); }
      | DBLCOLON IDENTIFIER  { $$=(DATATYPEP)malloc ( DATASIZE); }
      | scoped_name DBLCOLON IDENTIFIER  { $$=(DATATYPEP)malloc ( DATASIZE); }
      ;

interface_body:
       export  { $$=(DATATYPEP)malloc ( DATASIZE); }
      | export interface_body  { $$=(DATATYPEP)malloc ( DATASIZE); }
      ;

export:
       type_dcl SEMICOLON
      | const_dcl SEMICOLON  { $$=(DATATYPEP)malloc ( DATASIZE); }
      | except_dcl SEMICOLON
      | attr_dcl SEMICOLON  { $$=(DATATYPEP)malloc ( DATASIZE); }
      | rel_dcl SEMICOLON  { $$=(DATATYPEP)malloc ( DATASIZE); }
      | op_dcl SEMICOLON  { $$=(DATATYPEP)malloc ( DATASIZE); }
      ;


attr_dcl:
     ATTRIBUTE domain_type attribute_name fixed_array_size
      |READONLY ATTRIBUTE domain_type attribute_name  fixed_array_size
      |ATTRIBUTE domain_type attribute_name 
      |READONLY ATTRIBUTE domain_type attribute_name 
      ;

attribute_name: STRING_LITERAL { $$=(DATATYPEP)malloc ( DATASIZE); }

domain_type:
      simple_type_spec  { $$=(DATATYPEP)malloc ( DATASIZE); }
      |struct_type       { $$=(DATATYPEP)malloc ( DATASIZE); }
      |enum_type        { $$=(DATATYPEP)malloc ( DATASIZE); }
      ;    

rel_dcl:
       RELATIONSHIP target_of_path IDENTIFIER INVERSE inverse_traversal_path
       ;

target_of_path:
       IDENTIFIER  { $$=(DATATYPEP)malloc ( DATASIZE); }
       | rel_collection_type IDENTIFIER { $$=(DATATYPEP)malloc ( DATASIZE); }
       ;

inverse_traversal_path:
       IDENTIFIER DBLCOLON IDENTIFIER  { $$=(DATATYPEP)malloc ( DATASIZE); }
       ;

op_dcl:
        op_type_spec IDENTIFIER paramater_dcls
        | op_type_spec IDENTIFIER paramater_dcls raises_expr context_expr  { $$=(DATATYPEP)malloc ( DATASIZE); }
        | op_type_spec IDENTIFIER paramater_dcls context_expr { $$=(DATATYPEP)malloc ( DATASIZE); }
        | op_type_spec IDENTIFIER paramater_dcls raises_expr  { $$=(DATATYPEP)malloc ( DATASIZE); }

        |op_attribute op_type_spec IDENTIFIER paramater_dcls  { $$=(DATATYPEP)malloc ( DATASIZE); }
        |op_attribute op_type_spec IDENTIFIER paramater_dcls raises_expr context_expr 
           { $$=(DATATYPEP)malloc ( DATASIZE); }
        | op_attribute op_type_spec IDENTIFIER paramater_dcls context_expr  { $$=(DATATYPEP)malloc ( DATASIZE); }
        | op_attribute op_type_spec IDENTIFIER paramater_dcls raises_expr   { $$=(DATATYPEP)malloc ( DATASIZE); }
        ;

except_dcl:
        EXCEPTION IDENTIFIER OPCURLBRKT member_list OPCURLBRKT  { $$=(DATATYPEP)malloc ( DATASIZE); }
        | EXCEPTION IDENTIFIER OPCURLBRKT OPCURLBRKT  { $$=(DATATYPEP)malloc ( DATASIZE); }
        ;
          
op_attribute: ONEWAY
        ;

op_type_spec: 
           simple_type_spec  { $$=(DATATYPEP)malloc ( DATASIZE); }
        | VOID  { $$=(DATATYPEP)malloc ( DATASIZE); }
         ;

paramater_dcls:
          OPPAREN param_dcl_list CLPAREN
        ;
param_dcl_list:
          param_dcl
        | param_dcl COMMA param_dcl_list
        ;

param_dcl:
         param_attribute simple_type_spec declarator
       ;
param_attribute:
        IN 
       | OUT
       | INOUT
       ;

raises_expr:
        RAISES OPPAREN scoped_name_list CLPAREN
       ;

context_expr:
        CONTEXT OPPAREN string_literal_list CLPAREN
       ;

scoped_name_list:
        scoped_name  { $$=(DATATYPEP)malloc ( DATASIZE); }
       |scoped_name COMMA scoped_name_list { $$=(DATATYPEP)malloc ( DATASIZE); }
       ;

string_literal_list:
        STRING_LITERAL
       | STRING_LITERAL COMMA string_literal_list
       ;

%%
