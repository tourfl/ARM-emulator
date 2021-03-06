/**
 * @file bits.c
 * @author François Cayre & Raph
 * @date 2015
 * @brief Bit twiddling.
 *
 * Bit twiddling.
 */

#include "elf/bits.h"

 #include <string.h> // strlen
 #include <stdlib.h> // calloc
 #include <stdio.h> // printf
 #include "inter/notify.h" // here
 #include <math.h> // pow


/**
 * Simple way of guessing the endianness of the machine on which this code is executed
 * @return The endianness type
 * @see types.h
 */

unsigned int get_host_endianness( void )
{
    unsigned int var = 0x000000FF;
    return ((((unsigned char*) &var)[0]) == 0xFF)?LSB:MSB;
}

/**
 * takes blocks of memory and swaps the content of each block of sz bytes.
 * For instance :
 *     __flip_endianness(p, 2): swaps every pair of bytes
 *     __flip_endianness(p, 4): swaps every 4-byte block
 *     __flip_endianness(p, 1): has no effect
 * @param blocks the memory space to swap
 * @param sz the size (in byte) of each block to swap
 * @return the address of the swapped blocks (which is not changed by the function)
 */
byte * __flip_endianness( byte * blocks, uint sz ) {
    uint i;

    for ( i= 0; i< sz/2; i++ )
    {
        byte tmp = blocks[i];
        blocks[i] = blocks[sz-1-i];
        blocks[sz-1-i] = tmp;
    }

    return blocks;
}



word wrd_good_endianness(word in)
{
    word out = 0;
    Half_word hwd = 0;



    hwd = hwd_good_endianness((Half_word) in);
    out = (word) hwd;

    hwd = hwd_good_endianness((Half_word) (in >> 16));
    out += ((word) hwd) << 16;

    return out;
}






Half_word hwd_good_endianness(Half_word in)
{
    Half_word out = 0;



    out = (in >> 8) + (in << 8);

    return out;
}








int to_good_endianness(char **binstr, int taille)
{
    char *newstr = NULL;
    int i;

    newstr = calloc(taille + 1, sizeof(char)); // Un de plus pour le caractère de fin

    if(newstr == NULL)
        return 1;

    for (i = 0 ; (*binstr)[i] != 0 && i < taille; i++)
    {
        newstr[taille - 1 - i] = (*binstr)[i];
    }

    free(*binstr);

    *binstr = newstr;

    return 0;
}




int change_word_endianness(word *mot, Endianness in, Endianness out)
{
    word w= *mot << 16;


    if( (in == LITTLE_E_ALIGNED && out == LITTLE_E)
          || (in == LITTLE_E && out == LITTLE_E_ALIGNED) )
    {
        *mot = *mot >> 16;
        *mot += w;
    }

    return 0;
}






int change_endianness(byte *tab, int size, Endianness in, Endianness out)
{
    int i;
    byte b1=0, b2=0;




    if(size % 2 != 0) // On ne peut pas changer l'endianness dans ces conditions
        return 30;



    if( (in == BIG_E && out == LITTLE_E)
     || (in == LITTLE_E && out == BIG_E) )
    {
        change_endianness(tab, size, in, LITTLE_E_ALIGNED);
        change_endianness(tab, size, LITTLE_E_ALIGNED, out);
    }
    
    else if( (in == LITTLE_E_ALIGNED && out == LITTLE_E)
          || (in == LITTLE_E && out == LITTLE_E_ALIGNED) )
    {
        for (i = 0; i < size; i += 4)
        {
            b1 = tab[i];
            b2 = tab[i + 1];

            tab[i] = tab[i+2];
            tab[i+1] = tab[i+3];

            tab[i+2] = b1;
            tab[i+3] = b2;
        }
    }

    else if( (in == BIG_E && out == LITTLE_E_ALIGNED)
          || (out == BIG_E && in == LITTLE_E_ALIGNED) )
    {
        for (i = 0; i < size - 1; i += 2)
        {
            b1 = tab[i];
            tab[i] = tab[i + 1];
            tab[i+1] = b1;
        }
    }

    return 0;
}





int masklen(word mot)
{
    int l=0;


    // algorithme astucieux trouvé sur internet
    while(mot > 0)
    {
        l++;

        mot = mot & (mot-1);
    }

    return l;
}


// retourne n tq
// si n=0, le mask et la référence sont de même taille
// si n>0, le mask est plus long que la référence
// si n<0, le mask est plus court que la référence

int cmp_mask(word ref, word mask)
{
    int lref = masklen(ref), l = masklen(mask);


    // printf("ref: %08x, word: %08x, lref = %u, l = %u\n", ref, mask, lref, l);

    return l - lref;
}


