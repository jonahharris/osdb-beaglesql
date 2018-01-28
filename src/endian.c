static const char  rcsfile []= "$Header: /home/magrasjc/test/src/RCS/endian.c,v 0.87.2.1 2000/02/05 06:13:13 magrasjc Exp $";
/* This is a lowest-common-denominator program which should compile under
   the default cc on any system, no matter how primitite (even the SunOS
   one - note the use of 1970's-vintage octal escapes).  This is necessary
   because it's compiled before we can try and select a decent compiler via
   the makefile */

#include <stdio.h>
#include <stdlib.h>

int main()
	{
	if( *( long * ) "\200\0\0\0\0\0\0\0" < 0 )
		printf( "-DBIG_ENDIAN" );
	else
		printf( "-DLITTLE_ENDIAN" );

	return( 0 );
	}
