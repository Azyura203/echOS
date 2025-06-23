section .text.multiboot
align 4

multiboot_header:
    dd 0x1BADB002
    dd 0x0
    dd -(0x1BADB002 + 0x0)

global _start
extern kernel_main
extern stack_top

_start:
    mov esp, stack_top
    push ebx
    push eax
    call kernel_main

.hang:
    jmp .hang

section .bss
align 16
stack_bottom:
    resb 16384
stack_top:
