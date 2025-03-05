#ifndef STRING_H
#define STRING_H
#include "stddef.h"

// Définition de NULL si non définie
#ifndef NULL
#define NULL ((void*)0)
#endif

int strcmp(const char *s1, const char *s2);
char *strchr(const char *s, int c);
char *strdup(const char *s);
char *strndup(const char *s, size_t len);
size_t strlen(const char *str);
char *strtok(char *str, const char *delim);
char* itoa(int num, char* str, int base);

#endif