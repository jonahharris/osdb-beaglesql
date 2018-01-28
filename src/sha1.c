static const char  rcsfile []= "$Header: /home/magrasjc/test/src/RCS/sha1.c,v 0.87.2.1 2000/02/05 06:13:41 magrasjc Exp $";
/****************************************************************************
*																			*
*						  SHA-1 Message Digest Algorithm 					*
*						Copyright Peter Gutmann 1992-1997					*
*																			*
****************************************************************************/
#include <string.h>
#if defined( CRYPTLIB)
#if defined( INC_ALL )
  #include "crypt.h"
  #include "sha.h"
#elif defined( INC_CHILD )
  #include "../crypt.h"
  #include "clink.h"
  #include "sha.h"
#else
  #include "crypt.h"
  #include "hash/clink.h"
  #include "hash/sha.h"
#endif /* Compiler-specific includes */
#else
#include "beagle.h"
#endif /*CRYPTLIB*/
/* SHA initial values */

#include "sha.h"
#define h0init	0x67452301UL
#define h1init	0xEFCDAB89UL
#define h2init	0x98BADCFEUL
#define h3init	0x10325476UL
#define h4init	0xC3D2E1F0UL

#define SHA_INFO struct sha_info
#define TRUE 1
#define FALSE 0
/****************************************************************************
*																			*
*							SHA Support Routines							*
*																			*
****************************************************************************/

/* Initialize the SHA values */

void sha1Initial( SHA_INFO *shaInfo )
	{
	/* Clear all fields */
	memset( shaInfo, 0, sizeof( struct sha_info ) );

	/* Set the h-vars to their initial values */
	shaInfo->digest[ 0 ] = h0init;
	shaInfo->digest[ 1 ] = h1init;
	shaInfo->digest[ 2 ] = h2init;
	shaInfo->digest[ 3 ] = h3init;
	shaInfo->digest[ 4 ] = h4init;

	/* Initialise bit count */
	shaInfo->countLo = shaInfo->countHi = 0;
	}

/* Update SHA for a block of data */
void sha1Update( struct sha_info *shaInfo, unsigned char *buffer, int count )
	{
	LONG tmp;
	int dataCount;

	/* Update bitcount */
	tmp = shaInfo->countLo;
	if ( ( shaInfo->countLo = tmp + ( ( LONG ) count << 3 ) ) < tmp )
		shaInfo->countHi++;				/* Carry from low to high */
	shaInfo->countHi += count >> 29;

	/* Get count of bytes already in data */
	dataCount = ( int ) ( tmp >> 3 ) & 0x3F;

	/* Handle any leading odd-sized chunks */
	if( dataCount )
		{
#define BYTE unsigned char
#ifdef _BIG_WORDS
		BYTE *p = shaInfo->dataBuffer + dataCount;
#else
		BYTE *p = ( BYTE * ) shaInfo->data + dataCount;
#endif /* _BIG_WORDS */

		dataCount = SHA_DATASIZE - dataCount;
		if( count < dataCount )
			{
			memcpy( p, buffer, count );
			return;
			}
		memcpy( p, buffer, dataCount );
#if defined( _BIG_WORDS )
		copyToBLong( shaInfo->data, shaInfo->dataBuffer, SHA_DATASIZE );
#elif !defined( ASM_X86 )
		bigToLittleLong( shaInfo->data, SHA_DATASIZE );
#endif /* _BIG_WORDS */
		SHA1Transform( shaInfo->digest, shaInfo->data );
		buffer += dataCount;
		count -= dataCount;
		}

	/* Process data in SHA_DATASIZE chunks */
	while( count >= SHA_DATASIZE )
		{
#if defined( _BIG_WORDS )
		memcpy( shaInfo->dataBuffer, buffer, SHA_DATASIZE );
		copyToBLong( shaInfo->data, shaInfo->dataBuffer, SHA_DATASIZE );
		SHA1Transform( shaInfo->digest, shaInfo->data );
#elif defined( LITTLE_ENDIAN ) && !defined( ASM_X86 )
		memcpy( shaInfo->data, buffer, SHA_DATASIZE );
		bigToLittleLong( shaInfo->data, SHA_DATASIZE );
		SHA1Transform( shaInfo->digest, shaInfo->data );
#else
		SHA1Transform( shaInfo->digest, ( LONG * ) buffer );
#endif /* Endianness and word-size dependant data moves */
		buffer += SHA_DATASIZE;
		count -= SHA_DATASIZE;
		}

	/* Handle any remaining bytes of data. */
#ifdef _BIG_WORDS
	memcpy( shaInfo->dataBuffer, buffer, count );
#else
	memcpy( shaInfo->data, buffer, count );
#endif /* _BIG_WORDS */
	}

/* Final wrapup - pad to SHA_DATASIZE-byte boundary with the bit pattern
   1 0* (64-bit count of bits processed, MSB-first) */

void sha1Final( SHA_INFO *shaInfo )
	{
	int count;
	BYTE *dataPtr;

	/* Compute number of bytes mod 64 */
	count = ( int ) shaInfo->countLo;
	count = ( count >> 3 ) & 0x3F;

	/* Set the first char of padding to 0x80.  This is safe since there is
	   always at least one byte free */
#ifdef _BIG_WORDS
	dataPtr = shaInfo->dataBuffer + count;
#else
	dataPtr = ( BYTE * ) shaInfo->data + count;
#endif /* _BIG_WORDS */
	*dataPtr++ = 0x80;

	/* Bytes of padding needed to make 64 bytes */
	count = SHA_DATASIZE - 1 - count;

	/* Pad out to 56 mod 64 */
	if( count < 8 )
		{
		/* Two lots of padding:  Pad the first block to 64 bytes */
		memset( dataPtr, 0, count );
#if defined( _BIG_WORDS )
		copyToBLong( shaInfo->data, shaInfo->dataBuffer, SHA_DATASIZE );
#elif !defined( ASM_X86 )
		bigToLittleLong( shaInfo->data, SHA_DATASIZE );
#endif /* _BIG_WORDS */
		SHA1Transform( shaInfo->digest, shaInfo->data );

		/* Now fill the next block with 56 bytes */
#ifdef _BIG_WORDS
		memset( shaInfo->dataBuffer, 0, SHA_DATASIZE - 8 );
#else
		memset( shaInfo->data, 0, SHA_DATASIZE - 8 );
#endif /* _BIG_WORDS */
		}
	else
		/* Pad block to 56 bytes */
		memset( dataPtr, 0, count - 8 );
#ifdef _BIG_WORDS
	copyToBLong( shaInfo->data, shaInfo->dataBuffer, SHA_DATASIZE );
#endif /* _BIG_WORDS */

	/* Append length in bits and transform */
	shaInfo->data[ 14 ] = shaInfo->countHi;
	shaInfo->data[ 15 ] = shaInfo->countLo;

#if !defined( _BIG_WORDS )
  #ifdef ASM_X86
	/* The length count has to be in big-endian format when we feed it to the
	   asm SHATransform() */
	bigToLittleLong( shaInfo->data + 14, 8 );
  #else
	bigToLittleLong( shaInfo->data, SHA_DATASIZE - 8 );
  #endif /* ASM_X86 */
#endif /* !_BIG_WORDS */
	SHA1Transform( shaInfo->digest, shaInfo->data );

	shaInfo->done = TRUE;
	}
