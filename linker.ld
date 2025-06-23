OUTPUT_FORMAT(elf32-i386)
ENTRY(_start)

SECTIONS {
    . = 1M;

    .text : {
        KEEP(*(.text.multiboot))   /* Multiboot header — must be early */
        *(.text*)                  /* Rest of code */
    }

    .rodata : { *(.rodata*) }
    .data   : { *(.data*) }
    .bss    : { *(.bss*) *(COMMON) }
}
