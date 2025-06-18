/* Linker.ld - Layout for echOS kernel binary */

ENTRY(_start)

SECTIONS {
	/* Load everything at 1 MB (judt above real-mode memory)
	.=1M;

	/* Code section */
	.text : {
	   *(.multiboot)	/*Multiboot header*/
	   *(.text*)		/*Bootloader + kernel code*/
	}
	
	/* Read-only data */
	.rodata : {
	   *(.rodata*)
	}

	/* Initialized data */
	.data : {
	   *(.data*)
	}

	/* Uninitialized data (e.g., .bss, our stack) */
	.bss : {
	   *(.bss*)
	   *(COMMON)
	}
}
