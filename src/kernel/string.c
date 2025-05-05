#include "string.h"
#include "stddef.h"  // Pour size_t
#include "memory.h"  // Inclure memory.h pour malloc

int strcmp(const char *s1, const char *s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return *(unsigned char *)s1 - *(unsigned char *)s2;
}

int strncmp(const char *s1, const char *s2, size_t n) {
    while (n--) {
        if (*s1 != *s2) {
            return *(unsigned char *)s1 - *(unsigned char *)s2;
        }
        if (*s1 == '\0') {
            break;
        }
        s1++;
        s2++;
    }
    return 0;
}

// Fonction strchr pour trouver un caractère dans une chaîne
char *strchr(const char *s, int c) {
    while (*s != '\0') {
        if (*s == c) {
            return (char *)s;  // Retourner l'adresse du caractère trouvé
        }
        s++;
    }
    return NULL;  // Si le caractère n'est pas trouvé, retourner NULL
}

// Fonction strdup (copie une chaîne de caractères)
char *strdup(const char *s) {
    size_t len = 0;
    while (s[len] != '\0') {
        len++;
    }

    // Allocation mémoire pour la chaîne dupliquée
    char *dup = (char *)malloc(len + 1);
    if (dup == NULL) {
        return NULL;  // Échec de l'allocation
    }

    // Copier la chaîne dans la mémoire allouée
    for (size_t i = 0; i < len; i++) {
        dup[i] = s[i];
    }
    dup[len] = '\0';  // Terminer la chaîne

    return dup;
}

// Fonction strndup (copie les n premiers caractères d'une chaîne)
char *strndup(const char *s, size_t len) {
    char *dup = (char *)malloc(len + 1);
    if (dup == NULL) {
        return NULL;  // Échec de l'allocation
    }

    // Copier jusqu'à len caractères
    for (size_t i = 0; i < len && s[i] != '\0'; i++) {
        dup[i] = s[i];
    }
    dup[len] = '\0';  // Terminer la chaîne

    return dup;
}

size_t strlen(const char *str) {
    size_t length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

// Cette variable statique gardera la position actuelle dans la chaîne à découper
static char *strtok_ptr = NULL;

char *strtok(char *str, const char *delim) {
    if (str == NULL) {
        str = strtok_ptr; // Utiliser la chaîne restante de la dernière utilisation
    }

    // Si la chaîne est vide ou que l'on est arrivé à la fin, on retourne NULL
    if (str == NULL || *str == '\0') {
        return NULL;
    }

    // Chercher la première position où un délimiteur est trouvé
    char *token_start = str;
    
    // Avancer le pointeur jusqu'à rencontrer un délimiteur ou la fin de la chaîne
    while (*str && !strchr(delim, *str)) {
        str++;
    }

    // Si on a trouvé un délimiteur, on le remplace par un caractère nul '\0'
    if (*str) {
        *str = '\0';
        strtok_ptr = str + 1; // Mettre à jour le pointeur pour le prochain appel
    } else {
        strtok_ptr = NULL; // Aucun délimiteur trouvé, marquer la fin de la chaîne
    }

    return token_start;
}

// Fonction pour convertir un entier en chaîne de caractères
char* itoa(int num, char* str, int base) {
    int i = 0;
    int isNegative = 0;

    // Gérer le cas spécial pour 0
    if (num == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }

    // Gérer le cas pour les entiers négatifs
    if (num < 0 && base == 10) {
        isNegative = 1;
        num = -num;
    }

    // Convertir l'entier en chaîne
    while (num != 0) {
        int rem = num % base;
        str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
        num = num / base;
    }

    // Ajouter le signe négatif pour les entiers négatifs
    if (isNegative) {
        str[i++] = '-';
    }

    str[i] = '\0';  // Ajouter le caractère de fin de chaîne

    // Inverser la chaîne
    int start = 0;
    int end = i - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }

    return str;
}