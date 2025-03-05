#include "../kernel/print.h"
#include "../kernel/string.h"
#include "commands.h"
#include "help.h"

void help_command() {
    char num_str[20];  // Un tableau pour stocker la chaîne convertie
    print("Nombre de commandes : ");
    print(itoa(num_commands, num_str, 10));  // Convertir num_commands et l'afficher
    print("\n");
    print("Liste des commandes disponibles :\n");
    print("clear - Efface l'ecran\n");
    print("echo - Affiche du texte\n");
    print("halt - Arrete le systeme d'exploitation\n");
    print("help - Affiche cette aide\n");
}
