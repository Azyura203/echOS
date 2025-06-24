# Makefile - echOS v1.2.0 Build System

ARCH    = i686-elf
AS      = $(ARCH)-as
CC      = $(ARCH)-gcc
LD      = $(ARCH)-ld
CFLAGS  = -ffreestanding -O2 -Wall -Wextra
LDFLAGS = -T linker.ld

OBJ     = src/boot.o src/kernel.o src/vga.o src/memory.o src/pmm.o src/keyboard.o src/shell.o
ISO_DIR = iso
ISO     = $(ISO_DIR)/echOS.iso
KERNEL  = kernel.elf
GRUB_CFG= $(ISO_DIR)/boot/grub/grub.cfg

all: $(ISO)

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

src/%.o: src/%.asm
	nasm -f elf32 $< -o $@

$(KERNEL): $(OBJ)
	$(LD) $(LDFLAGS) -o $@ $^

$(ISO): $(KERNEL) $(GRUB_CFG)
	mkdir -p $(ISO_DIR)/boot/grub
	cp $(KERNEL) $(ISO_DIR)/boot/kernel.elf
	grub-mkrescue -o $@ $(ISO_DIR)

$(GRUB_CFG):
	mkdir -p $(@D)
	echo 'set timeout=0'                    >  $@
	echo 'set default=0'                    >> $@
	echo 'menuentry "echOS" {'              >> $@
	echo '  multiboot /boot/kernel.elf'     >> $@
	echo '  boot'                           >> $@
	echo '}'                                >> $@

run: $(ISO)
	qemu-system-i386 -cdrom $<

clean:
	rm -rf src/*.o *.elf $(ISO_DIR) *.iso

