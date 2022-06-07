// error.c
// Řešení IJC-DU1, příklad b), 21.3.2022
// Autor: Nikita Kotvitskiy, FIT
// Přeloženo: gcc 9.4.04

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

static void warning(char *fmt, va_list ap)
{
    fprintf(stderr, "ERROR: ");
    vfprintf(stderr, fmt, ap);
}

void warning_msg(char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    warning(fmt, ap);
    va_end(ap);
}
void error_exit(char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    warning(fmt, ap);
    va_end(ap);
    exit(1);
}