#ifndef IO_H
#define IO_H

// Fonction pour écrire dans un port donné
static inline void outb(unsigned char value, unsigned short port) {
    __asm__ volatile ("outb %0, %1" : : "a" (value), "Nd" (port));
}

// Fonction pour lire depuis un port donné
static inline unsigned char inb(unsigned short port) {
    unsigned char result;
    __asm__ volatile ("inb %1, %0" : "=a" (result) : "Nd" (port));
    return result;
}

#endif