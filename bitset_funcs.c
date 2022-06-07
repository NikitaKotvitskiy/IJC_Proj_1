// bitset_funcs.c
// Řešení IJC-DU1, příklad a), 21.3.2022
// Autor: Nikita Kotvitskiy, FIT
// Přeloženo: gcc 9.4.04
// V tomto zdrojaku jsou funkce které jsou analogem maker v hlavičkovém souboru bitset.h
// Kvůli úplně nejasným pro mě důvodům tyto funkce nefungují jako inline, což je dobře vidět v ASM kódu.
// To způsobí zpoždění o ~1.5 sekundy při hledání prvočísel do 300 000 000

#ifdef USE_INLINE

#include "bitset.h"
#include <stdlib.h>
#include <assert.h>
#include <limits.h>

inline bitset_t bitset_size(bitset_t * set)
{
    return set[0];
} 
inline void bitset_free(bitset_t * set)
{
    free(set);
} 
inline void bitset_setbit(bitset_t * set, bitset_index_t index, int val)
{
    assert(index < set[0]);
    const int segment_size = sizeof(bitset_t) * CHAR_BIT;
    val ? 
        (set[(index + 1) / (segment_size) + 1] |= ((bitset_t)(1) << (segment_size - 1 - (index % segment_size))))
        : (set[(index + 1) / (segment_size) + 1] &= ~((bitset_t)(1) << (segment_size - 1 - (index % segment_size))));
}
inline int bitset_getbit(bitset_t * set, bitset_index_t index)
{
    //bitset_t segment = set[(index + 1) / (sizeof(bitset_t) * CHAR_BIT) + 1];
    //bitset_t oper = (bitset_t)(1) << (sizeof(bitset_t) * CHAR_BIT - 1 - (index % (sizeof(bitset_t) * CHAR_BIT)));
    //  segment                                                   oper
    return ((set[(index + 1) / (sizeof(bitset_t) * CHAR_BIT) + 1]) & ((bitset_t)(1) << (sizeof(bitset_t) * CHAR_BIT - 1 - (index % (sizeof(bitset_t) * CHAR_BIT))))) ?
    1 : 0;
}

#endif