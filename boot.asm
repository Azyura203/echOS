;boot.asm - First code GRUB runs
;	  - NASM syntax, 32-bit protected mode

;1. Multiboot header (tells GRUB this is multiboot-compliant)
;------------------------------------------------------------------

section .multiboot
multiboot_header:
	dd 0x1BADB002			;magic
	dd 0x00				;flags (no special request)
	dd - (0x1BADB002 + 0x00)	;checksum = -(magic + flags)

;2. Reserve a stack 
;-------------------------------------------------------
section .bss
align 16
stack_bottom:
	resb 16384			;16KB
stack_top:

;3. Code entry point - GRUB jumps here
;------------------------------------------------------
section .text
global _start
_start:
	;set up the stack pointer
	mov esp, stack_top

	;call our C function (declare in kernel.c)
	extern kernel_main
	call kernel_main

.hang:
	jmp .hang			;if kernel_main returns, hang
