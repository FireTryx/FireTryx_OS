# Variables
SRC_DIR := src
BUILD_DIR := build
ISO_DIR := targets/iso
ISO_FILE := dist/kernel.iso
KERNEL_BIN := dist/kernel.bin

# Fichiers source
BOOT_SRC := $(wildcard $(SRC_DIR)/boot/*.asm)
KERNEL_SRC := $(wildcard $(SRC_DIR)/kernel/*.c)
COMMANDS_SRC := $(wildcard $(SRC_DIR)/commands/*.c)

# Fichiers objets
BOOT_OBJ := $(BOOT_SRC:$(SRC_DIR)/boot/%.asm=$(BUILD_DIR)/boot/%.o)
KERNEL_OBJ := $(KERNEL_SRC:$(SRC_DIR)/kernel/%.c=$(BUILD_DIR)/kernel/%.o)
COMMANDS_OBJ := $(COMMANDS_SRC:$(SRC_DIR)/commands/%.c=$(BUILD_DIR)/commands/%.o)

# Cible principale
.PHONY: all build-x86 iso clean

all: build-x86 iso

# Compilation du binaire final
build-x86: $(BOOT_OBJ) $(KERNEL_OBJ) $(COMMANDS_OBJ)
	mkdir -p dist
	i686-elf-ld -T targets/iso/linker.ld -o $(KERNEL_BIN) $(BOOT_OBJ) $(KERNEL_OBJ) $(COMMANDS_OBJ)

# Compilation des fichiers objets pour le boot
$(BUILD_DIR)/boot/%.o: $(SRC_DIR)/boot/%.asm
	mkdir -p $(BUILD_DIR)/boot
	nasm -f elf32 $< -o $@

# Compilation des fichiers objets pour le noyau
$(BUILD_DIR)/kernel/%.o: $(SRC_DIR)/kernel/%.c
	mkdir -p $(BUILD_DIR)/kernel
	i686-elf-gcc -m32 -ffreestanding -c $< -o $@

# Compilation des fichiers objets pour les commandes
$(BUILD_DIR)/commands/%.o: $(SRC_DIR)/commands/%.c
	mkdir -p $(BUILD_DIR)/commands
	i686-elf-gcc -m32 -ffreestanding -c $< -o $@

# Création de l'ISO
iso: build-x86
	mkdir -p $(ISO_DIR)/boot/grub
	cp $(KERNEL_BIN) $(ISO_DIR)/boot/kernel.bin
	cp targets/iso/grub/grub.cfg $(ISO_DIR)/boot/grub/
	grub-mkrescue -o $(ISO_FILE) $(ISO_DIR)

# Nettoyage des fichiers générés
clean:
	rm -rf build dist