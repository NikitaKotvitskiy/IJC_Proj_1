// ppm.c
// Řešení IJC-DU1, příklad b), 21.3.2022
// Autor: Nikita Kotvitskiy, FIT
// Přeloženo: gcc 9.4.04

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "error.h"
#include "ppm.h"

#define PPM_FORMAT "P6"

#define MAX_XSIZE 8000
#define MAX_YSIZE 8000
#define COLOR 255
#define COLOR_DIMS 3

#define MAX_SIZE_STRING_LENGTH 5

void readFragment(FILE *img, char *buf, int *bufCurs, int *c)   //IS USED FOR READING FORMAT, SIZE AND COLOR INTERVAL
{
    while (!isspace(*c = fgetc(img)))
    {
        buf[*bufCurs] = *c;
        (*bufCurs)++;
    }
    buf[*bufCurs] = '\0';
}
void skipSpaces(FILE *img, char *buf, int *bufCurs, int *c)     //IS USED FOR SKIPPING UNKNOWN COUNT OF WHITESPACES
{
    while (isspace(*c))
        *c = fgetc(img);
    buf[*bufCurs] = *c;
    (*bufCurs)++;
}

struct ppm * ppm_read(const char * filename)
{
    FILE *img = fopen(filename, "r");               //OPENING THE FILE
    if (img == NULL)
        error_exit("File open failure");
    char buf[10];
    int bufCurs = 0;
    int c;

    readFragment(img, buf, &bufCurs, &c);           //READ MAGIC NUMBER
    if (strcmp(PPM_FORMAT, buf))                    //CHECK MAGIC NUMBER
    {
        warning_msg("Wrong image format\n");
        return NULL;
    };
    bufCurs = 0;
    skipSpaces(img, buf, &bufCurs, &c);             //SKIP SPACES
    readFragment(img, buf, &bufCurs, &c);           //READING X SIZE
    int xSize = atoi(buf);
    bufCurs = 0;
    skipSpaces(img, buf, &bufCurs, &c);             //SKIP SPACES
    readFragment(img, buf, &bufCurs, &c);           //READING Y SIZE
    int ySize = atoi(buf);
    bufCurs = 0;
    if (xSize > MAX_YSIZE || ySize > MAX_YSIZE)     //CHECKING SIZE VALUES
    {
        warning_msg("Wrong image size\n");
        return NULL;
    }
    skipSpaces(img, buf, &bufCurs, &c);             //SKIP SPACES
    readFragment(img, buf, &bufCurs, &c);           //READING COLOR
    int color = atoi(buf);
    bufCurs = 0;
    if (color != COLOR)                             //CHECKING COLOR VALUE
    {
        warning_msg("Wrong image color\n");
        return NULL;
    }
    //skipSpaces(img, buf, &bufCurs, &c);             //SKIP SPACES

    struct ppm * imgData = malloc(sizeof(struct ppm) * xSize * ySize); //PIXEL ARRAY ALLOCATION
    if (imgData == NULL)
        error_exit("Allocation failure");

    for (int i = 0; i < xSize * ySize; i++)
    {
        imgData[i].xsize = i % xSize + 1;
        imgData[i].ysize = i / xSize + 1;
        imgData[i].data[0] = fgetc(img);
        imgData[i].data[1] = fgetc(img);
        imgData[i].data[2] = fgetc(img);
    }
    fclose(img);
    return imgData;
}

unsigned long ppm_size(const char * filename) //IS USED FOR FINDING PICTURE SIZE
{
    FILE *img = fopen(filename, "r");
    if (img == NULL)
        error_exit("File open failure");
    char buf[10];
    int bufCurs = 0;
    int c;

    readFragment(img, buf, &bufCurs, &c);           //READ MAGIC NUMBER
    if (strcmp(PPM_FORMAT, buf))                    //CHECK MAGIC NUMBER
    {
        error_exit("Wrong image format\n");
        return 0;
    };
    bufCurs = 0;
    skipSpaces(img, buf, &bufCurs, &c);             //SKIP SPACES
    readFragment(img, buf, &bufCurs, &c);           //READING X SIZE
    int xSize = atoi(buf);
    bufCurs = 0;
    skipSpaces(img, buf, &bufCurs, &c);             //SKIP SPACES
    readFragment(img, buf, &bufCurs, &c);           //READING Y SIZE
    int ySize = atoi(buf);
    bufCurs = 0;

    fclose(img);
    return xSize * ySize;
}

void ppm_free(struct ppm *p)
{
    free(p);
}