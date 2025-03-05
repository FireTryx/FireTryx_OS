#ifndef KERNEL_H
#define KERNEL_H

#include "stddef.h"

#define VIDEO_MEMORY 0xB8000
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25

// Fonction principale
void kernel_entry();

#endif