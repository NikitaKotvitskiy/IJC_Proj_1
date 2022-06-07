// steg-decode.c
// Řešení IJC-DU1, příklad b), 21.3.2022
// Autor: Nikita Kotvitskiy, FIT
// Přeloženo: gcc 9.4.04

#include "error.h"
#include <stdio.h>
#include "ppm.h"
#include "bitset.h"
#include <limits.h>
#include "erat.h"
#include <stdbool.h>

#define START_FROM 29

int main(int argc, char * argv[])
{
    if (argc < 2)                                                   //FILE NAME CHECK EXISTENCE
        error_exit("File name is missing\n");
    struct ppm* img = ppm_read(argv[1]);                            //READING PPM FILE
    if (img == NULL)
        error_exit("File read error\n");

    unsigned long pixelSize = ppm_size(argv[1]);                    //CREATING ALL NECCESSARY VARIABLES      
    bitset_alloc(bitset, pixelSize * 3 * CHAR_BIT);
    char *secret = malloc(0);
    if (secret == NULL)
        error_exit("Allocation error\n");
    int secretSize = 0;
    int bit = 0;
    char byte = 0;

    eratosthenes_not_print(bitset);                                 //FINDING PRIME NUMBERS
    bool secretIsFound = false;
    for (bitset_index_t i = START_FROM; i < pixelSize * 3; i++)     //CHECKING EACH COLOR BYTE OF IMAGE
    {
        if (bitset_getbit(bitset, i))                               //IF INDEX ISN'T A PRIME - SKIP
            continue;
        int pixel = i / 3;                                          //FIND OUT THE INDEX OF PIXEL, WHERE IS NEEDED BYTE
        int ofset = i % 3;
        char neededByte = img[pixel].data[ofset];                   //STORING NEEDED BYTE
        neededByte &= (char)(1);                                    //GETTING LSB BIT OF NEEDED BYTE
        if (neededByte)
        {
            neededByte = neededByte << (bit);                       //MOVING BIT ON IT'S POSITION
            byte |= neededByte;                                     //ADD THE BIT IN FORMING BYTE
        }
        bit++;
        if (bit == CHAR_BIT)                                        //IF BYTE IS READY ADD IT TO THE MASSIVE
        {
            secret = realloc(secret, ++secretSize);
            if (secret == NULL)
                error_exit("Reallocation error\n");
            secret[secretSize - 1] = byte;
            if (byte == '\0')                                       //CHECKING OF THE BYTE WAS THE LAST
            {
                secretIsFound = true;
                break;
            }
            byte = 0;
            bit = 0;
        }
    }
    if (secretIsFound)
        fprintf(stdout, "%s\n", secret);
    else
        error_exit("Secret is not found\n");

    free(secret);
    ppm_free(img);
    bitset_free(bitset);
}