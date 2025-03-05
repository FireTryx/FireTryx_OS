#include "../kernel/memory.h"
#include "../kernel/print.h"
#include "../kernel/string.h"
#include "echo.h"

#define MAX_ARG_LENGTH 256

void echo_command(const char *args) {
    if (args == NULL || strlen(args) == 0) {
        print("Error: No arguments provided to echo.\n");
        return;
    }

    char buffer[MAX_ARG_LENGTH];
    int i = 0;

    // Créer une copie modifiable de args
    char *args_copy = strdup(args);  // Assure-toi de libérer cette mémoire plus tard

    // Séparer les arguments par espaces
    char *token = strtok(args_copy, " ");

    while (token != NULL) {
        // Copier l'argument dans le buffer
        for (i = 0; i < MAX_ARG_LENGTH - 1 && token[i] != '\0'; i++) {
            buffer[i] = token[i];
        }
        buffer[i] = '\0';  // Terminer la chaîne correctement

        // Afficher l'argument
        print(buffer);
        print(" ");  // Ajouter un espace entre les arguments

        token = strtok(NULL, " ");  // Passer à l'argument suivant
    }

    print("\n");  // Finir avec une nouvelle ligne
    free(args_copy);
}