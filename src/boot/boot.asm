; boot.asm - Bootloader pour le noyau Multiboot

[bits 32]               ; Mode protégé 32 bits
[extern kernel_entry]    ; Déclaration de l'entrée du noyau

section .multiboot_header
    align 4
    dd 0x1BADB002        ; Magic number pour Multiboot
    dd 0                 ; Flags
    dd - (0x1BADB002 + 0) ; Checksum (doit être nul)

section .text
    global _start

_start:
    ; Le bootloader initialise la mémoire, l'écran, etc.
    
    ; Charger le noyau à l'adresse 0x100000
    mov ebx, 0x100000      ; Charger l'adresse du noyau dans ebx
    mov ecx, 0             ; Pas d'arguments à passer
    mov edx, 0             ; Pas de "mod" pour l'instant
    call kernel_entry      ; Appel du noyau (en mode protégé)
    
    ; Si le noyau échoue, boucle infinie
hang:
    jmp hang

section .data
    ; Les sections de données (non utilisées dans ce cas)

section .bss
    ; Les sections de données non initialisées