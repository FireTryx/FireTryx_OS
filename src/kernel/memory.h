#ifndef MEMORY_H
#define MEMORY_H

#include "stddef.h"  // Pour size_t

#ifndef NULL
#define NULL ((void*)0)
#endif

void *malloc(size_t size);
void free(void *ptr);

#endif