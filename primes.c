// primes.c
// Řešení IJC-DU1, příklad b), 21.3.2022
// Autor: Nikita Kotvitskiy, FIT
// Přeloženo: gcc 9.4.04

#include "bitset.h"
#include "erat.h"
#include <stdio.h>
#include <time.h>

#define SET_SIZE 300000000

bitset_create(setGlobal, SET_SIZE);

int main()
{
    bitset_alloc(setDynamic, SET_SIZE);
    clock_t start = clock();
    Eratosthenes(setGlobal);
    fprintf(stderr, "Time=%.3g\n", (double)(clock()-start)/CLOCKS_PER_SEC);
    bitset_free(setDynamic);
}