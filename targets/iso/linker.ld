ENTRY(_start)

SECTIONS {
    . = 0x100000; /* Adresse de départ modifiée */

    .text : {
        *(.text)
    }

    .data : {
        *(.data)
    }

    .bss : {
        *(.bss)
    }
}