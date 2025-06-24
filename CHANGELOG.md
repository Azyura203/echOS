# CHANGELOG

## [v1.4.0-beta] - 2025-06-24
### Added
- Basic Shell Interface: Minimal input loop
- Keyboard input handling (scancode to ASCII)
- Shell command system scaffold (echo, help)

## [v1.3.0] - 2025-06-24
### Added
- Physical memory detection using Multiboot
- Bump allocator (`kmalloc`)
- Physical memory manager (`pmm_init`, `pmm_alloc`, `pmm_free`)
- Free memory count display

## [v1.2.0] - 2025-06-23
### Added
- Multiboot-compliant bootloader using NASM
- Basic VGA driver: clear screen, text output
- Kernel entry in C receives Multiboot info
- Printed memory map manually (no `stdlib`)

### Fixed
- Boot.asm pushed wrong register order (fixed)
- `.multiboot` section missing in linker (fixed)
- GRUB magic number error resolved
- Bootloop fixed!

