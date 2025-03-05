#include "../kernel/print.h"
#include "halt.h"

void halt_command() {
    print("\nArret du systeme...\n\n");
    print("\nVous pouvez eteindre l'ordinateur...\n");
    // En mode bare-metal, l'instruction HLT stoppe le processeur
    asm volatile("hlt");
}