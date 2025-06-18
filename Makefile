# Makefile - echOS v1.0.0 Build System

ARCH	= i686-elf
AS	= $(ARCH)-as
CC	= $(ARCH)-gcc
LD	= $(ARCH)-ld
CFLAGS	= -ffreestanding -O2 -Wall -Wextra
LDFLAGS	= -T linker.ld

ISO_DIR=iso
ISO=iso/echOS.iso
KERNEL=kernel.elf
GRUB_CFG=$(ISO_DIR)/boot/grub/grub.cfg

all: $(ISO)

boot.o: boot.asm
	nasm -f elf32 $< -o $@

kernel.o: kernel.c
	$(CC) $(CFLAGS) -c $< -o $@

$(KERNEL): boot.o kernel.o
	$(LD) $(LDFLAGS) -o $@ $^

$(ISO): $(KERNEL) $(GRUB_CFG)
	mkdir -p $(ISO_DIR)/boot/grub
	cp $(KERNEL) $(ISO_DIR)/boot/kernel.elf
	grub-mkrescue -o $@ $(ISO_DIR)

$(GRUB_CFG):
	mkdir -p $(@D)
	echo 'set timeout=0'			>  $@
	echo 'set default=0'			>> $@
	echo 'menuentry "echOS" {'		>> $@
	echo '	multiboot /boot/kernel.elf'	>> $@
	echo '	boot'				>> $@
	echo '}'				>> $@

run: $(ISO)
	qemu-system-i386 -cdrom $<

clean:
	rm -rf *.o *.elf $(ISO_DIR) *.iso
