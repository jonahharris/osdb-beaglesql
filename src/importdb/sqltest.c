#include <stdio.h>

extern FILE* yyin;
main(int argc,char *argv[])
{
  if (argc>1) 
    {

      FILE *file;
      file= fopen(argv[1],"r");
      if (!file)
	{
            printf ("open error.\n");
            exit(1);
        }
      yyin=file;
      yyparse();
     
    }

}
