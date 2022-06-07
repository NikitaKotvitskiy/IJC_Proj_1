// eratosthenes.c
// Řešení IJC-DU1, příklad a), 21.3.2022
// Autor: Nikita Kotvitskiy, FIT
// Přeloženo: gcc 9.4.04
// Obsahuje funkce pro vypočet a tisk prvočísel

#include "bitset.h"
#include <stdio.h>

#define TEN 10

void eratosthenes_not_print(bitset_t * pole)
{
    bitset_setbit(pole, 0, 1);
    bitset_setbit(pole, 1, 1);
    for (bitset_index_t i = 2; i * i < bitset_size(pole); i++)
    {
        if (bitset_getbit(pole, i))
            continue;
        for (unsigned long j = i * i; j < bitset_size(pole); j += i)
            bitset_setbit(pole, j, 1);
    }
}

void Eratosthenes(bitset_t * pole)
{
    eratosthenes_not_print(pole);
    bitset_index_t last_ten[TEN];
    for (unsigned long i = TEN - 1, j = bitset_size(pole) - 1; i < TEN; j--)
    {
        if (bitset_getbit(pole, j))
            continue;
        last_ten[i] = j;
        i--;
    }
    for (int i = 0; i < TEN; i++)
    {
        printf("%lu\n", last_ten[i]);
    }
}