#ifndef MULTIBOOT_H
#define MULTIBOOT_H

#include <stdint.h>

typedef struct multiboot_info {
    uint32_t flags;

    // Available memory from BIOS
    uint32_t mem_lower;
    uint32_t mem_upper;

    // "boot device" - not used here
    uint32_t boot_device;

    // Kernel command line
    uint32_t cmdline;

    // Boot modules
    uint32_t mods_count;
    uint32_t mods_addr;

    // ELF section header table
    uint32_t num;
    uint32_t size;
    uint32_t addr;
    uint32_t shndx;

    // Memory map (actual regions info)
    uint32_t mmap_length;
    uint32_t mmap_addr;

    // Drives, config table, boot loader name, APM table, VBE, etc.
    uint32_t drives_length;
    uint32_t drives_addr;
    uint32_t config_table;
    uint32_t boot_loader_name;
    uint32_t apm_table;
    uint32_t vbe_control_info;
    uint32_t vbe_mode_info;
    uint32_t vbe_mode;
    uint32_t vbe_interface_seg;
    uint32_t vbe_interface_off;
    uint32_t vbe_interface_len;
} __attribute__((packed)) multiboot_info_t;

typedef struct multiboot_memory_map {
    uint32_t size;
    uint64_t addr;
    uint64_t len;
    uint32_t type;
} __attribute__((packed)) multiboot_memory_map_t;


#endif
