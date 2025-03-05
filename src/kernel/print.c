#include "kernel.h"
#include "io.h"
#include "string.h"

int cursor_x = 0;
int cursor_y = 0;

int KERNEL_LINES = 0;
const int PROMPT_LENGTH = 14;
int enter = 0;

void move_cursor(int x, int y) {
    unsigned short position = (y * SCREEN_WIDTH) + x;
    outb(0x0F, 0x03D4);
    outb(position & 0xFF, 0x03D5);
    outb(0x0E, 0x03D4);
    outb((position >> 8) & 0xFF, 0x03D5);
}

void put_char(char c) {
    volatile char *video = (volatile char*) VIDEO_MEMORY;

    if (c == '\n') {
        cursor_x = 0;
        cursor_y++;
        if (enter > 0) {
            KERNEL_LINES += enter + 1;
            enter = 0;
        } else {
            KERNEL_LINES++;
        }
    } else if (c == '\b') {
        if (cursor_y > KERNEL_LINES || (cursor_y == KERNEL_LINES && cursor_x > PROMPT_LENGTH)) {
            if (cursor_x > 0) {
                cursor_x--;
            } else if (cursor_y > 0) {
                cursor_y--;
                cursor_x = SCREEN_WIDTH - 1;
                enter--;
            }

            int pos = (cursor_y * SCREEN_WIDTH + cursor_x) * 2;
            video[pos] = ' ';
            video[pos + 1] = 0x0F;
        }
    } else {
        int pos = (cursor_y * SCREEN_WIDTH + cursor_x) * 2;
        video[pos] = c;
        video[pos + 1] = 0x0F;
        cursor_x++;

        if (cursor_x >= SCREEN_WIDTH) {
            cursor_x = 0;
            cursor_y++;
            enter++;
        }
    }

    if (cursor_y >= SCREEN_HEIGHT) {
        for (int i = 0; i < (24 * SCREEN_WIDTH * 2); i++) {
            video[i] = video[i + (SCREEN_WIDTH * 2)];
        }
        for (int i = (24 * SCREEN_WIDTH * 2); i < (25 * SCREEN_WIDTH * 2); i += 2) {
            video[i] = ' ';
            video[i + 1] = 0x0F;
        }
        cursor_y = 24;
        KERNEL_LINES--;

    }

    move_cursor(cursor_x, cursor_y);
}

void print(const char *str) {
    while (*str) {
        put_char(*str++);
    }
}

void kernel_prompt() {
    print("FireTryx OS > ");
}