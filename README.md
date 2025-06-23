# echOS 🔧🧠

> echOS v1.0.0 - A minimal OS bootloader and kernel written from scratch in Assembly and C

## 🚀 Boot Process
- GRUB loads multiboot-compliant boot.asm
- Kernel written in C prints message to video memory
- Fully bootable `.iso` built with `grub-mkrescue`

## ✅ Version: 1.0.0
- Assembly: `boot.asm` loads the kernel
- Kernel: `kernel.c` prints to VGA memory
- Custom linker: `linker.ld`
- Build system: `Makefile`

## 🐛 Fixes
- grub.cfg not generated ➜ fixed with Makefile target
- toolchain errors ➜ solved by installing `nasm`, `xorriso`, `grub-mkrescue`
- cleaned up Makefile formatting and build output

## 💡 Next Plans
- Add keyboard input
- Cursor movement
- Basic memory map

✅ echOS v1.2.0 - "The Awakening"

Release Date: 2025-06-23
🚀 Features

    Implemented Multiboot-compliant bootloader using NASM.

    Set up proper linker.ld with correct multiboot alignment.

    Basic VGA driver: screen clearing and text output working.

    Kernel entry (C) now receives Multiboot info properly.

    Printed memory map with basic number formatting (no stdlib 🛠️).

🐛 Fixes

    Fixed boot.asm parameter order (🤦 pushed eax, ebx → should be ebx, eax).

    Fixed linker section .multiboot not appearing.

    Fixed multiboot magic number mismatch.

    No longer stuck in the bootloop (hallelujah 🙏).

🔧 Notes

    grub-file --is-x86-multiboot ✅ passes

    Next up: paging, heap, IDT, or drivers 👀



