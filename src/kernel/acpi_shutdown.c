#include "acpi.h"
#include "print.h"
#include "io.h"

// Fonction pour rechercher le RSDP
struct rsdp *acpi_find_rsdp(void) {
    uint8_t *addr;

    // Recherche dans la plage 0xE0000-0xFFFFF
    for (addr = (uint8_t *)0xE0000; addr < (uint8_t *)0xFFFFF; addr += 16) {
        if (strncmp((char *)addr, "RSD PTR ", 8) == 0) {
            return (struct rsdp *)addr;
        }
    }

    // Recherche dans la mémoire de base (640 Ko)
    for (addr = (uint8_t *)0x000E0000; addr < (uint8_t *)0x000FFFFF; addr += 16) {
        if (strncmp((char *)addr, "RSD PTR ", 8) == 0) {
            return (struct rsdp *)addr;
        }
    }

    return NULL;
}

// Fonction pour localiser la FACP
struct facp *acpi_find_facp(struct rsdp *rsdp) {
    uint32_t *addr;
    uint32_t length;

    if (rsdp->revision == 0) { // RSDT
        addr = (uint32_t *)rsdp->rsdt_address;
        length = *((uint32_t *)addr);
        addr += 1; // Passer l'en-tête de la table
        while ((uint8_t *)addr < (uint8_t *)rsdp->rsdt_address + length) {
            if (strncmp((char *)*addr, "FACP", 4) == 0) {
                return (struct facp *)*addr;
            }
            addr++;
        }
    } else if (rsdp->revision > 0) { // XSDT
        uint64_t *addr64 = (uint64_t *)rsdp->xsdt_address;
        length = *((uint32_t *)addr64);
        addr64 += 1; // Passer l'en-tête de la table
        while ((uint8_t *)addr64 < (uint8_t *)rsdp->xsdt_address + length) {
            if (strncmp((char *)*addr64, "FACP", 4) == 0) {
                return (struct facp *)*addr64;
            }
            addr64++;
        }
    }
    return NULL;
}

// Fonction pour l'arrêt ACPI
void acpi_shutdown(void) {
    struct rsdp *rsdp;
    struct facp *facp;

    rsdp = acpi_find_rsdp();
    if (!rsdp) {
        print("ACPI: RSDP not found\n");
        return;
    }

    facp = acpi_find_facp(rsdp);
    if (!facp) {
        print("ACPI: FACP not found\n");
        return;
    }

    if (facp->pm1a_cnt_blk) {
        outw(0x2000, facp->pm1a_cnt_blk); // S5
        print("ACPI: Shutdown command sent to PM1a_CNT_BLK\n");
    } else if (facp->pm1b_cnt_blk) {
        outw(0x2000, facp->pm1b_cnt_blk); // S5
        print("ACPI: Shutdown command sent to PM1b_CNT_BLK\n");
    } else {
        print("ACPI: PM1a_CNT_BLK and PM1b_CNT_BLK not found\n");
    }
}