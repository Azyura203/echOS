#include "vga.h"
#include "memory.h"
#include "multiboot.h"

// Minimal number printing to VGA
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

    // Print in reverse
    for (int j = i - 1; j >= 0; j--) {
        char temp[2] = { str[j], '\0' };
        vga_write(temp);
    }
}

void kernel_main(uint32_t magic, uint32_t addr) {
    vga_clear();

    const char *msg = "echOS: memory online!";
    char buffer[80];
    memset(buffer, 0, sizeof(buffer));
    memcpy(buffer, msg, strlen(msg));

    vga_write("Welcome to echOS, New Operating System\n");
    vga_write("---------------------------------------\n");
    vga_write(buffer);
    vga_write("\nThis is a minimal kernel setup.\n");
    vga_write("Time to build something powerful.\n");

    vga_write("\n\nMemory Map Info:\n");

    multiboot_info_t* mb = (multiboot_info_t*) addr;

    if (magic != 0x2BADB002) {
        vga_write("Invalid multiboot magic number!\n");
	print_number(magic);
	vga_write("\n");
        return;
    }

    if (mb->flags & 0x1) {
        vga_write("Lower: ");
        print_number(mb->mem_lower);
        vga_write(" KB\n");

        vga_write("Upper: ");
        print_number(mb->mem_upper);
        vga_write(" KB\n");
    } else {
        vga_write("No memory info available.\n");
    }
}

