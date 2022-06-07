// bitset.h
// Řešení IJC-DU1, příklad a), 21.3.2022
// Autor: Nikita Kotvitskiy, FIT
// Přeloženo: gcc 9.4.04
// Tento soubor obsahuje makra pro bitové pole nebo, pokud je zadán argument USE_INLINE, deklaraci funkcí (analogů maker).
// Omezení!!! Makra bitset_create a bitset_alloc nelze používat v cyklech, podminkách a jiných konstrukcích bez závorek.
// Omezení!!! Makro bitset_create nelze používat s lokalními nekonstantními hodnotami size.

#ifndef BITSET_H
#define BITSET_H

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <limits.h>

#define MAX_BITSET_SIZE 3000000000
typedef unsigned long bitset_t;
typedef unsigned long bitset_index_t;

#define bitset_create(name, size)\
    bitset_t (name)[(size) / (sizeof(bitset_t) * CHAR_BIT) + ((size) % (sizeof(bitset_t) * CHAR_BIT) ? 2 : 1)] = { (size), };\
    static_assert(size != 0 && size <= MAX_BITSET_SIZE, "bitset_create: Bitset size error")

#define bitset_alloc(name, size)\
    bitset_t * (name) = calloc(sizeof(bitset_t), (size) / (sizeof(bitset_t) * CHAR_BIT) + ((size) % (sizeof(bitset_t) * CHAR_BIT) ? 2 : 1));\
    assert((size) != 0 && (size) <= MAX_BITSET_SIZE);\
    if ((name) == NULL)\
    {\
        fprintf(stderr, "bitset_alloc: allocation error");\
        exit(EXIT_FAILURE);\
    }\
    (name)[0] = size

#ifndef USE_INLINE

#define bitset_size(name)\
    (name)[0]

#define bitset_free(name)\
    free((name))

#define bitset_setbit(name, index, val)\
    do {\
        assert(index < (name)[0]);\
        const int segment_size = sizeof(bitset_t) * CHAR_BIT;\
        (val) ? \
            ((name)[((index) + 1) / (segment_size) + 1] |= ((bitset_t)(1) << (segment_size - 1 - ((index) % segment_size))))\
            : ((name)[((index) + 1) / (segment_size) + 1] &= ~((bitset_t)(1) << (segment_size - 1 - ((index) % segment_size))));\
    } while(0)

#define bitset_getbit(name, index)\
    ((name)[((index) + 1) / (sizeof(bitset_t) * CHAR_BIT) + 1] & ((bitset_t)(1) << (sizeof(bitset_t) * CHAR_BIT - 1 - ((index) % (sizeof(bitset_t) * CHAR_BIT))))) ? 1 : 0

#else

    extern bitset_t bitset_size(bitset_t * set);
    extern void bitset_free(bitset_t * set);
    extern void bitset_setbit(bitset_t * set, bitset_index_t index, int val);
    extern int bitset_getbit(bitset_t * set, bitset_index_t index); 

#endif
#endif