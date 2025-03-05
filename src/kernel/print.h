#ifndef PRINT_H
#define PRINT_H

extern int cursor_x;
extern int cursor_y;

extern int KERNEL_LINES;

void put_char(char c);          // Afficher un seul caractère
void print(const char *str);    // Afficher une chaîne de caractères
void kernel_prompt();            // Afficher le prompt
void move_cursor(int x, int y); // Déplacer le curseur à une position donnée

#endif