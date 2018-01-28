static const char  rcsfile []= "$Header: /home/magrasjc/test/src/RCS/mymalloc.c,v 0.87.2.1 2000/02/05 06:13:34 magrasjc Exp $";
#include <stdio.h>
#include <stdlib.h>

#include "log.h"

void *mymalloc (void *ptr, size_t size);
void *myrealloc (void *ptr, size_t size);
void myfree (void *ptr);

void *mymalloc (void *ptr, size_t size)
{
   void *ptr2;

   ptr2 = malloc (size);
   if (ptr!=NULL)
      lprintf ("MALLOC DEBUG: Warning, malloc()'ing a non-NULL pointer");
   lprintf ("MALLOC DEBUG: malloc() Location :%ld  Size: %ld", (long) ptr2, (long) size);
   return ptr2;
}


void *myrealloc (void *ptr, size_t size)
{
   if (ptr==NULL) 
      return mymalloc (ptr, size);
   else 
      return realloc (ptr, size);
}

void myfree (void *ptr)
{
   lprintf ("MALLOC DEBUG: free() Location :%ld", (long) ptr);
   if (ptr==NULL) return;
   free (ptr);
}
