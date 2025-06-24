#include <stdint.h>
#include "vga.h"
#include "memory.h"
#include "multiboot.h"
#include "pmm.h"
#include "keyboard.h"
#include "shell.h"

#define MAX_USABLE_REGIONS 32

typedef struct {
    uint32_t base_addr;
    uint32_t length;
} UsableRegion;

UsableRegion usable_memory[MAX_USABLE_REGIONS];
int usable_region_count = 0;

// Basic number printing to VGA
void print_number(uint32_t num) {
    char str[16];
    int i = 0;

    if (num == 0) {
        vga_write("0");
        return;
    }

    while (num > 0) {
        str[i++] = '0' + (num % 10);
        num /= 10;
    }

    for (int j = i - 1; j >= 0; j--) {
        char temp[2] = { str[j], '\0' };
        vga_write(temp);
    }
}

void detect_usable_memory(multiboot_info_t* mb) {
    if (!(mb->flags & (1 << 6))) {
        vga_write("\nNo memory map available.\n");
        return;
    }

    multiboot_memory_map_t* mmap = (multiboot_memory_map_t*) mb->mmap_addr;
    while ((uint32_t)mmap < mb->mmap_addr + mb->mmap_length && usable_region_count < MAX_USABLE_REGIONS) {
        if (mmap->type == 1) { // Available RAM
            usable_memory[usable_region_count].base_addr = (uint32_t)(mmap->addr & 0xFFFFFFFF);
            usable_memory[usable_region_count].length = (uint32_t)(mmap->len & 0xFFFFFFFF);
            usable_region_count++;
        }
        mmap = (multiboot_memory_map_t*)((uint32_t)mmap + mmap->size + sizeof(mmap->size));
    }
}

void kernel_main(uint32_t magic, uint32_t addr) {
    vga_clear();
    vga_write("Welcome to echOS, New Operating System\n");
    vga_write("---------------------------------------\n");
    vga_write("echOS: memory online!\n");

    if (magic != 0x2BADB002) {
        vga_write("Invalid multiboot magic number!\n");
        print_number(magic);
        return;
    }

    multiboot_info_t* mb = (multiboot_info_t*) addr;
    detect_usable_memory(mb);

    // Setup memory allocator
    if (usable_region_count > 1) {
        init_allocator(usable_memory[1].base_addr, usable_memory[1].length);
        pmm_init(usable_memory[0].base_addr, usable_memory[0].length);
    } else if (usable_region_count > 0) {
        init_allocator(usable_memory[0].base_addr, usable_memory[0].length);
        pmm_init(usable_memory[0].base_addr, usable_memory[0].length);
    } else {
        vga_write("No usable memory regions found!\n");
        return;
    }

    // Test alloc (for debug)
    void* test = kmalloc(64);
    vga_write("Allocated 64 bytes at: ");
    print_number((uint32_t)test);
    vga_write("\n");

    // Shell System
    keyboard_init();
    shell_run();
}
