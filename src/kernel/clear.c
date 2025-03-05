#include "kernel.h"
#include "clear.h"
#include "print.h"

void clear_screen() {
    volatile char *video = (volatile char*) VIDEO_MEMORY;
    for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT * 2; i += 2) {
        video[i] = ' ';
        video[i + 1] = 0x0F;
    }
    KERNEL_LINES = 0;
    cursor_x = 0;
    cursor_y = 0;
}