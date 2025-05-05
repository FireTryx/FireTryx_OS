#include "../kernel/print.h"
#include "halt.h"

void halt_command() {
    print("Arret du systeme...\n");
    acpi_shutdown();
    print("Arret echoue.\n");
}