#include "memory.h"

// Définir une taille de zone mémoire et un pointeur pour le gestionnaire de mémoire
#define HEAP_SIZE 0x10000  // Par exemple, 64 Ko pour le heap
static char heap[HEAP_SIZE];
static size_t heap_index = 0;  // Pointeur vers la prochaine position libre

// Allocation de mémoire
void *malloc(size_t size) {
    if (heap_index + size > HEAP_SIZE) {
        return NULL;  // Pas assez de place pour l'allocation
    }

    void *ptr = &heap[heap_index];
    heap_index += size;  // Déplacer l'index du heap

    return ptr;
}

// Libération de mémoire (ce gestionnaire simple ne libère pas réellement la mémoire)
void free(void *ptr) {
    // Ici, la gestion de la mémoire est très simplifiée et ne gère pas la libération réelle.
    // Si tu veux une gestion plus complexe, tu devras implémenter un système de "free list".
}