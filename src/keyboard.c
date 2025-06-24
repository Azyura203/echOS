#include "keyboard.h"
#include "vga.h"
#include <stdint.h>
#include <stdbool.h>

#define KEYBOARD_DATA_PORT 0x60

static const char scancode_table[128] = {
    0,  27, '1','2','3','4','5','6','7','8','9','0','-','=', '\b', // Backspace
    '\t', // Tab
    'q','w','e','r','t','y','u','i','o','p','[',']','\n',    // Enter
    0,    // Control
    'a','s','d','f','g','h','j','k','l',';','\'','`',
    0,    // Left Shift
    '\\','z','x','c','v','b','n','m',',','.','/',
    0,    // Right Shift
    '*',
    0,    // Alt
    ' ',  // Space
    0,    // Caps Lock
    // ... (rest can be extended as needed)
};

static inline uint8_t inb(uint16_t port) {
    uint8_t ret;
    __asm__ volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

char keyboard_getchar() {
    static uint8_t last_scancode = 0xFF;
    uint8_t scancode;

    while (1) {
        scancode = inb(KEYBOARD_DATA_PORT);

        if (scancode != last_scancode && !(scancode & 0x80)) {
            last_scancode = scancode;
            return scancode_table[scancode];
        }

        // Update last_scancode only when released
        if (scancode & 0x80) {
            last_scancode = 0xFF;
        }
    }
}
void keyboard_init() {
    vga_write("Keyboard initialized.\n");
}

