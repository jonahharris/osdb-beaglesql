static const char  rcsfile []= "$Header: /home/magrasjc/test/src/RCS/malloc_stats.c,v 0.87.2.1 2000/02/05 06:13:30 magrasjc Exp $";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
   FILE *fp1, *fp2;
   char line[256], *p, *q;
   long malloced, freed;
   int nullfrees=0;
   int nonnull=0;

   if (argc < 2) {
      printf ("\nSyntax: malloc_stats [log file name]\n\n");
      exit (0);
   }
   if ((fp1 = fopen (argv[1], "r")) == NULL)
      printf ("Can't open file '%s'", argv[1]);
   else {
      fp2 = fopen (argv[1], "r");
      while (fgets (line, 255, fp1)!=NULL) {
         if ((p=strstr (line, "malloc() Location :")) == NULL)
            continue; 
         printf (p);
         p+=19;
         malloced = atol(p);
         rewind (fp2);
         while (fgets (line, 255, fp2)!=NULL) {
            if ((q=p=strstr (line, "free() Location :")) == NULL)
               continue;
            p+=17;
            freed = atol(p);
            if (malloced==freed) {
               printf (q);
               break;
            }
         }
         if(malloced!=freed)
            printf ("Memory was NOT free'd\n");
      }
      rewind (fp2);
      while (fgets (line, 255, fp2)!=NULL) {
        p=strstr (line, "free() Location :");
        if (p!=NULL) {
           p+=17;
           freed = atol(p);
           if (freed==0L) nullfrees++;
        }
        p=strstr (line, "Warning, malloc()'ing a non-NULL pointer");
        if (p!=NULL) 
           nonnull++;
      }
      fclose (fp1);
      fclose (fp2);
   }

   printf ("\nThe program tried to free() a NULL pointer %d time(s)\n", nullfrees);
   printf ("\nThe program malloc()'d non-NULL pointers %d time(s)\n", nonnull);
}
