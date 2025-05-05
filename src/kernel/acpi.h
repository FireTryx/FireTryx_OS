#ifndef ACPI_H
#define ACPI_H

#include "stdint.h"
#include "string.h"

// Définitions de base
#define ACPI_RSDP_SIGNATURE "RSD PTR "
#define ACPI_FACP_SIGNATURE "FACP"

// Structures de données
struct rsdp {
    char signature[8];
    uint8_t checksum;
    char oem_id[6];
    uint8_t revision;
    uint32_t rsdt_address;
    uint32_t length;
    uint64_t xsdt_address;
    uint8_t extended_checksum;
    uint8_t reserved[3];
};

struct facp {
    char signature[4];
    uint32_t length;
    // ... autres champs ...
    uint32_t pm1a_cnt_blk;
    uint32_t pm1b_cnt_blk;
    // ... autres champs ...
};

// Fonctions
struct rsdp *acpi_find_rsdp(void);
struct facp *acpi_find_facp(struct rsdp *rsdp);
void acpi_shutdown(void);

#endif // ACPI_H