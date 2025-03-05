#include "../kernel/kernel.h"
#include "../kernel/string.h"
#include "../kernel/memory.h"
#include "../kernel/print.h"
#include "commands.h"
#include "clear.h"
#include "echo.h"
#include "halt.h"
#include "help.h"

Command command_list[] = {
    {"clear", clear_command},
    {"echo", echo_command},
    {"halt", halt_command},
    {"help", help_command},
};

// Nombre de commandes dans le tableau
int num_commands = sizeof(command_list) / sizeof(Command);

// Fonction qui gère l'exécution des commandes
void handle_command(const char *command) {
    // Vérifier si la commande est vide
    if (command == NULL || strlen(command) == 0) {
        kernel_prompt();
        return;
    }

    // Trouver la position du premier espace (séparant la commande des arguments)
    char *space_pos = strchr(command, ' ');
    char *command_name;
    char *args = NULL;

    if (space_pos != NULL) {
        // Si un espace est trouvé, séparer la commande et les arguments
        command_name = strndup(command, space_pos - command);
        args = space_pos + 1;  // Les arguments commencent après l'espace
    } else {
        command_name = strdup(command);  // Si pas d'espace, toute la chaîne est le nom de la commande
    }

    // Recherche de la commande dans la liste
    for (int i = 0; i < num_commands; i++) {
        if (strcmp(command_name, command_list[i].name) == 0) {
            // Exécuter la fonction associée à la commande, en passant les arguments
            command_list[i].func(args);
            free(command_name);  // Libérer la mémoire allouée pour le nom de la commande
            kernel_prompt();
            return;
        }
    }

    // Commande inconnue
    print("Commande inconnue\n");
    kernel_prompt();
    free(command_name);
}