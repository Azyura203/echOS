#include "shell.h"
#include "vga.h"
#include "keyboard.h"  // we'll assume this handles input buffer
#include <stddef.h>
#include "memory.h"

// Basic input buffer
#define SHELL_BUFFER_SIZE 128
static char input_buffer[SHELL_BUFFER_SIZE];
static size_t buffer_index = 0;

void shell_prompt() {
    vga_write("\necho> ");
    buffer_index = 0;
    memset(input_buffer, 0, SHELL_BUFFER_SIZE);
}

void shell_handle_command(const char* cmd) {
    if (strcmp(cmd, "help") == 0) {
        vga_write("Available commands:\n- help\n- clear\n");
    } else if (strcmp(cmd, "clear") == 0) {
        vga_clear();
    } else {
        vga_write("Unknown command: ");
        vga_write(cmd);
        vga_write("\n");
    }
}

void shell_run() {
    vga_write("\nWelcome to echOS Shell v1.4.0 beta\n");
    shell_prompt();

    while (1) {
        char c = keyboard_getchar(); // you’ll need to implement this

        if (c == '\n') {
            input_buffer[buffer_index] = '\0';
            vga_write("\n");
            shell_handle_command(input_buffer);
            shell_prompt();
        } else if (c == '\b' && buffer_index > 0) {
            buffer_index--;
            // handle backspace visually (optional)
        } else if (buffer_index < SHELL_BUFFER_SIZE - 1) {
            input_buffer[buffer_index++] = c;
            char str[2] = { c, '\0' };
            vga_write(str);
        }
    }
}
