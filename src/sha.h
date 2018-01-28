#ifndef _SHA_DEFINED

#define _SHA_DEFINED
#include "beagle.h"
/* The SHS block size and message digest sizes, in bytes */

#define SHA_DATASIZE	64
#define SHA_DIGESTSIZE	20
#ifdef _BIG_WORDS
  #define MASK32( x ) ( ( x ) & 0xFFFFFFFFUL )
#else
  #define MASK32( x ) x
#endif /* _BIG_WORDS */



#ifdef LITTLE_ENDIAN
  #define bigToLittleLong( x, y )       longReverse(x,y)
  #define bigToLittleWord( x, y )       wordReverse(x,y)
  #define littleToBigLong( x, y )
  #define littleToBigWord( x, y )
#else
  #define bigToLittleLong( x, y )
  #define bigToLittleWord( x, y )
  #define littleToBigLong( x, y )       longReverse(x,y)
  #define littleToBigWord( x, y )       wordReverse(x,y)
#endif /* LITTLE_ENDIAN */

/* The structure for storing SHA info */

 struct sha_info {
	   LONG digest[ 5 ];			/* Message digest */
           LONG countLo, countHi;		/* 64-bit bit count */
	   LONG data[ 16 ];			/* SHS data buffer */
#ifdef _BIG_WORDS
	   BYTE dataBuffer[ SHA_DATASIZE ];	/* Byte buffer for data */
#endif /* _BIG_WORDS */
	   BOOLEAN done;		/* Whether final digest present */
	   BOOLEAN isSHA;			/* Whether to use SHA */
			   } ;
typedef struct sha_info SHA_INFO;

/* SHA is used as a general internal transformation function by the library 
   so we include a prototype for the shaTransform function for those 
   functions which call it directly */
#if defined( CRYPTLIB )
#if defined( INC_ALL ) || defined( INC_CHILD )
  #include "clink.h"
#else
  #include "hash/clink.h"
#endif /* Compiled-specific include directives */
#endif
/* Message digest functions */

/*
void sha0Initial( struct sha_info *shaInfo );
void sha0Update( struct sha_info *shaInfo, BYTE *buffer, int count );
void sha0Final( struct sha_info *shaInfo );*/
void sha1Initial( struct sha_info *shaInfo );
void sha1Update( struct sha_info *shaInfo, unsigned char *buffer, int count );
void sha1Final( struct sha_info *shaInfo );

#endif /* _SHA_DEFINED */
