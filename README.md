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

---
