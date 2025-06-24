
![Uploading echOS](https://github.com/Azyura203/echOS/blob/e4ecd5e214ddb811843029c0bafee7beb7168398/echOS.png)
# echOS 🔧🧠


> A minimal OS bootloader and kernel written from scratch in Assembly and C.

---

## 🚀 Boot Process
- GRUB loads a multiboot-compliant `boot.asm`
- `kernel.c` (written in C) is loaded and prints messages to VGA memory
- Built with `grub-mkrescue` to generate `.iso`

---

## ✅ Current Version: `v1.4.0-beta`

### Architecture
- Assembly Bootloader
- C Kernel
- Multiboot-compliant with GRUB
- Basic shell & memory management

### Files
- `boot.asm` - GRUB-compatible assembly bootloader
- `kernel.c` - Main kernel logic
- `linker.ld` - Linker script
- `Makefile` - Build instructions

---

## 📦 Requirements
- `nasm`
- `xorriso`
- `grub-mkrescue`
- Cross Compiler (`i686-elf-*`)

---

## 🐛 Fixes in Early Versions
- Fixed `grub.cfg` not generating
- Fixed multiboot magic mismatch
- Cleaned up Makefile and VGA bugs

---

## 💡 Upcoming
- Paging
- Dynamic heap allocator
- Interrupt handling (IDT)
- Basic filesystem

---

## 🧠 Fun Fact
> echOS uses zero dependencies. Pure C and Assembly. From bits to boot. 💥



