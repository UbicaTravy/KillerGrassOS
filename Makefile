# Команды для сборки:
# make all (или просто make) — собрать все файлы
# make run — запустить QEMU
# make clean — удалить все файлы
# make iso — собрать ISO образ
# make multiboot_header.o — собрать multiboot_header.o

CC = gcc
ASM = nasm
LD = ld
CFLAGS = -m32 -ffreestanding -nostdlib -Wall -Wextra -O0 -g
ASMFLAGS = -f bin
LDFLAGS = -m elf_i386 -T linker.ld -nostdlib

all: os.img

boot.bin: boot.asm
	$(ASM) $(ASMFLAGS) $< -o $@

fecalos.o: fecalos.c drivers/vga.h types.h
	$(CC) $(CFLAGS) -c $< -o $@

kernel.o: kernel.c drivers/vga.h types.h fecalos.c
	$(CC) $(CFLAGS) -c $< -o $@

drivers/vga.o: drivers/vga.c drivers/vga.h types.h
	$(CC) $(CFLAGS) -c $< -o $@

linker.ld: ;

kernel.elf: kernel.o drivers/vga.o fecalos.o multiboot_header.o linker.ld
	$(LD) $(LDFLAGS) multiboot_header.o kernel.o drivers/vga.o fecalos.o -o $@

kernel.bin: kernel.elf
	objcopy -O binary $< $@

os.img: boot.bin kernel.bin
	rm -f $@
	dd if=/dev/zero of=$@ bs=512 count=2880
	dd if=boot.bin of=$@ conv=notrunc
	dd if=kernel.bin of=$@ seek=1 conv=notrunc

iso: kernel.elf grub.cfg
	mkdir -p grub/boot/grub
	cp kernel.elf grub/boot/
	cp grub.cfg grub/boot/grub/
	grub-mkrescue -o fecalos.iso grub/

run:
	qemu-system-x86_64 -drive format=raw,file=os.img -serial stdio -no-reboot -no-shutdown

.PHONY: all run clean iso

clean:
	rm -f *.o *.bin *.elf *.img *.iso
	rm -rf grub/
	rm -rf drivers/*.o

multiboot_header.o: multiboot_header.asm
	nasm -f elf32 $< -o $@