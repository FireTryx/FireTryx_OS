#include "kernel.h"
#include "keyboard.h"
#include "print.h"
#include "clear.h"
#include "../commands/commands.h"

void kernel_entry() {
    clear_screen();
    print("=== Bienvenue sur FireTryx OS ===\n\n");
    print("Chargement du systeme\n");

    print("\n\n");

    print("Systeme pret.\n\n");
    print("FireTryx OS > ");

    char command_buffer[256];
    int command_index = 0;

    while (1) {
        char c = get_char();  // Lecture du caractère entré
        if (c) {
            if (c == '\b') {  // Gestion de la touche Backspace
                if (command_index > 0) {
                    command_index--;
                    put_char('\b');
                }
            } else if (c == '\n') {  // Gestion de la touche Entrée
                put_char('\n');
                command_buffer[command_index] = '\0';  // Fin de la commande
                handle_command(command_buffer);  // Appel de la fonction de traitement de la commande
                command_index = 0;  // Réinitialiser le buffer pour la prochaine commande
            } else {  // Si c'est un autre caractère
                if (command_index < 255) {  // Eviter de dépasser la taille du buffer
                    command_buffer[command_index++] = c;
                    put_char(c);  // Affichage du caractère
                }
            }
        }
    }
}