
/**
 * @file bits.h
 * @author François Cayre <francois.cayre@grenoble-inp.fr>
 * @date Sat Nov  2 18:48:44 2013
 * @brief Bit twiddling.
 *
 * Bit twiddling.
 */

#ifndef _BITS_H_
#define _BITS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "types.h"

unsigned int get_host_endianness( void );
byte *__flip_endianness( byte * block, uint sz );

word wrd_good_endianness(word in);
Half_word hwd_good_endianness(Half_word in);



typedef enum endianness { 
	BIG_E, LITTLE_E, LITTLE_E_ALIGNED
 } Endianness;

 

int change_word_endianness(word *mot, Endianness in, Endianness out);

int change_endianness(byte *tab, int size, Endianness in, Endianness out);
int to_good_endianness(char **binstr, int taille);

int cmp_mask(word mask1, word mask2);

int masklen(word mot);


#define FLIP_ENDIANNESS( x ) __flip_endianness( (byte*)&(x), sizeof(x) )


#define CLR_BIT( b, n ) ( b &= 0xFF-(1<<(n)) )
#define SET_BIT( b, n ) ( b |= 1<<(n) )
#define GET_BIT( b, n ) (  b & 1<<(n) )


#define SET_BITS( b, i, j ) ( b |= (((1 << (j-i)) - 1) << i) )
#define GET_BITS( b, i, j ) ( b & (((1 << (j-i)) - 1) << i ) )


#ifdef __cplusplus
}
#endif

#endif /* _BITS_H_ */
