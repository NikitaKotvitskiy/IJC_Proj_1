// ppm.h
// Řešení IJC-DU1, příklad b), 21.3.2022
// Autor: Nikita Kotvitskiy, FIT
// Přeloženo: gcc 9.4.04
// Hlavičkový soubor pro deklaraci funkcí z ppm.c

#ifndef PPM_H
#define PPM_H

struct ppm
{
    unsigned xsize;
    unsigned ysize;
    char data[3];    // RGB bajty, celkem 3*xsize*ysize
};
extern struct ppm * ppm_read(const char * filename);
extern void ppm_free(struct ppm *p);
extern unsigned long ppm_size(const char * filename);

#endif