#include "keyboard.h"
#include "io.h"  // Inclure le fichier contenant inb et outb

const char scancode_table_azerty[128] = {
    0, 27, '&', '2', '"', '\'', '(', '-', 'e', '_', 'c', 'a', ')', '=', '\b', '\t',
    'a', 'z', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '^', '$', '\n', 0, 'q', 's',
    'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', 'u', '*', 0, '<', 'w', 'x', 'c', 'v',
    'b', 'n', ',', ';', ':', '!', 0, '*', 0, ' ', 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, '7', '8', '9', '-', '4', '5', '6', '+',
    '1', '2', '3', '0', '.', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

char get_char() {
    while ((inb(0x64) & 1) == 0);  // Attendre qu'un caractère soit disponible
    unsigned char scancode = inb(0x60);  // Lire le scancode du clavier
    if (scancode < 128) {
        return scancode_table_azerty[scancode];  // Convertir le scancode en caractère
    }
    return 0;  // Retourner 0 si scancode invalide
}