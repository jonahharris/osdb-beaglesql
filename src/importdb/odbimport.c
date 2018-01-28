#include <stdio.h>


main (int argc, char * argv[])
{
   extern FILE *yyin;
   FILE *inputF;
   if (argc==2 )
   {
      inputF=fopen(argv[1],"r");
      yyin= inputF;
      yyparse();
   }

}
