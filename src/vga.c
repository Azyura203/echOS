#include "vga.h"
#include <stddef.h>

static uint16_t* const VGA_MEMORY = (uint16_t*) 0xB8000;
static uint8_t vga_color = 0;
static size_t terminal_row = 0;
static size_t terminal_col = 0;

uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) {
    return fg | bg << 4;
}

uint16_t vga_entry(unsigned char uc, uint8_t color) {
    return (uint16_t) uc | (uint16_t) color << 8;
}

void vga_clear() {
    vga_color = vga_entry_color(COLOR_LIGHT_GREY, COLOR_BLACK);
    for (size_t y = 0; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            const size_t index = y * VGA_WIDTH + x;
            VGA_MEMORY[index] = vga_entry(' ', vga_color);
        }
    }
    terminal_row = 0;
    terminal_col = 0;
}

void vga_put_char(char c) {
    if (c == '\n') {
        terminal_row++;
        terminal_col = 0;
        return;
    }

    const size_t index = terminal_row * VGA_WIDTH + terminal_col;
    VGA_MEMORY[index] = vga_entry(c, vga_color);
    terminal_col++;
    if (terminal_col >= VGA_WIDTH) {
        terminal_col = 0;
        terminal_row++;
    }
    if (terminal_row >= VGA_HEIGHT) {
        terminal_row = 0;
    }
}

void vga_write(const char* str) {
    for (size_t i = 0; str[i] != '\0'; i++) {
        vga_put_char(str[i]);
    }
}

