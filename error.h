// error.h
// Řešení IJC-DU1, příklad b), 21.3.2022
// Autor: Nikita Kotvitskiy, FIT
// Přeloženo: gcc 9.4.04
// Hlavičkový soubor pro deklaraci funkcí z error.c

#ifndef ERROR_H
#define ERROR_H

extern void warning_msg(char *fmt, ...);
extern void error_exit(char *fmt, ...);

#endif