# Команды для сборки:
# make all (или просто make) — собрать все файлы
# make run — запустить QEMU
# make clean — удалить все файлы
# make iso — собрать ISO образ

CC = gcc
ASM = nasm
LD = ld
CFLAGS = -m32 -ffreestanding -nostdlib -Wall -Wextra -Os -g0
ASMFLAGS = -f bin
LDFLAGS = -m elf_i386 -T linker.ld -nostdlib

all: os.img

boot.bin: boot.asm kernel.bin
	$(eval KERNEL_SIZE := $(shell stat -c%s kernel.bin))
	$(eval KERNEL_SECTORS := $(shell echo $$(( ($(KERNEL_SIZE) + 511) / 512 ))))
	$(ASM) $(ASMFLAGS) -D KERNEL_SECTORS=$(KERNEL_SECTORS) $< -o $@

kgos.o: kgos.c drivers/vga.h drivers/keyboard.h drivers/fash.h libs/types.h libs/string.h kernel/commands/commands.h kernel/input.h kernel/logo.h
	$(CC) $(CFLAGS) -c $< -o $@

kernel.o: kernel.c drivers/vga.h libs/types.h kgos.c
	$(CC) $(CFLAGS) -c $< -o $@

drivers/vga.o: drivers/vga.c drivers/vga.h libs/types.h
	$(CC) $(CFLAGS) -c $< -o $@

drivers/fash.o: drivers/fash.c drivers/fash.h drivers/vga.h libs/types.h libs/string.h
	$(CC) $(CFLAGS) -c $< -o $@

drivers/io.o: drivers/io.c drivers/io.h libs/types.h
	$(CC) $(CFLAGS) -c $< -o $@

kernel/input.o: kernel/input.c kernel/input.h kernel/commands/commands.h drivers/vga.h drivers/fash.h drivers/keyboard.h libs/types.h libs/string.h
	$(CC) $(CFLAGS) -c $< -o $@

kernel/logo.o: kernel/logo.c kernel/logo.h drivers/vga.h libs/types.h
	$(CC) $(CFLAGS) -c $< -o $@

kernel/commands/commands.o: kernel/commands/commands.c kernel/commands/commands.h drivers/vga.h drivers/fash.h libs/types.h libs/string.h
	$(CC) $(CFLAGS) -c $< -o $@

kernel/commands/exit.o: kernel/commands/exit.c kernel/commands/commands.h drivers/vga.h drivers/fash.h libs/types.h
	$(CC) $(CFLAGS) -c $< -o $@

kernel/commands/help.o: kernel/commands/help.c kernel/commands/commands.h drivers/vga.h drivers/fash.h libs/types.h
	$(CC) $(CFLAGS) -c $< -o $@

kernel/commands/clear.o: kernel/commands/clear.c kernel/commands/commands.h drivers/vga.h drivers/fash.h libs/types.h
	$(CC) $(CFLAGS) -c $< -o $@

kernel/commands/echo.o: kernel/commands/echo.c kernel/commands/commands.h drivers/vga.h drivers/fash.h libs/types.h
	$(CC) $(CFLAGS) -c $< -o $@

kernel/commands/info.o: kernel/commands/info.c kernel/commands/commands.h drivers/vga.h drivers/fash.h libs/types.h
	$(CC) $(CFLAGS) -c $< -o $@

kernel/commands/version.o: kernel/commands/version.c kernel/commands/commands.h drivers/vga.h drivers/fash.h libs/types.h
	$(CC) $(CFLAGS) -c $< -o $@

kernel/commands/date.o: kernel/commands/date.c kernel/commands/commands.h drivers/vga.h drivers/fash.h libs/types.h
	$(CC) $(CFLAGS) -c $< -o $@

kernel/commands/memory.o: kernel/commands/memory.c kernel/commands/commands.h drivers/vga.h drivers/fash.h libs/types.h
	$(CC) $(CFLAGS) -c $< -o $@

kernel/commands/reboot.o: kernel/commands/reboot.c kernel/commands/commands.h drivers/vga.h drivers/fash.h drivers/io.h libs/types.h
	$(CC) $(CFLAGS) -c $< -o $@

kernel/commands/color.o: kernel/commands/color.c kernel/commands/commands.h drivers/vga.h drivers/fash.h libs/types.h
	$(CC) $(CFLAGS) -c $< -o $@

kernel/commands/run.o: kernel/commands/run.c kernel/commands/commands.h kernel/programms/runner.h drivers/vga.h drivers/fash.h libs/types.h
	$(CC) $(CFLAGS) -c $< -o $@

kernel/commands/demo.o: kernel/commands/demo.c kernel/commands/commands.h kernel/programms/runner.h drivers/vga.h drivers/fash.h libs/types.h
	$(CC) $(CFLAGS) -c $< -o $@

kernel/commands/kg.o: kernel/commands/kg.c kernel/commands/commands.h kernel/programms/runner.h drivers/vga.h drivers/fash.h libs/types.h
	$(CC) $(CFLAGS) -c $< -o $@

kernel/programms/runner.o: kernel/programms/runner.c kernel/programms/runner.h drivers/vga.h drivers/keyboard.h drivers/fash.h libs/types.h libs/string.h
	$(CC) $(CFLAGS) -c $< -o $@

kernel/programms/demo.o: kernel/programms/demo.c kernel/programms/runner.h drivers/vga.h drivers/keyboard.h libs/types.h
	$(CC) $(CFLAGS) -c $< -o $@

kernel/programms/kgter.o: kernel/programms/kgter.c kernel/programms/runner.h kernel/programms/api.h drivers/vga.h drivers/keyboard.h libs/types.h
	$(CC) $(CFLAGS) -c $< -o $@

drivers/keyboard.o: drivers/keyboard.c drivers/keyboard.h drivers/vga.h libs/types.h
	$(CC) $(CFLAGS) -c $< -o $@

string.o: libs/string.c libs/string.h libs/types.h
	$(CC) $(CFLAGS) -c $< -o $@

linker.ld: ;


kernel.elf: kernel.o drivers/vga.o drivers/fash.o drivers/io.o drivers/keyboard.o libs/string.o kgos.o kernel/input.o kernel/logo.o kernel/commands/commands.o kernel/commands/help.o kernel/commands/exit.o kernel/commands/clear.o kernel/commands/echo.o kernel/commands/info.o kernel/commands/version.o kernel/commands/date.o kernel/commands/memory.o kernel/commands/reboot.o kernel/commands/color.o kernel/commands/run.o kernel/commands/demo.o kernel/commands/kg.o kernel/programms/runner.o kernel/programms/demo.o kernel/programms/kgter.o linker.ld
	$(LD) $(LDFLAGS) kernel.o drivers/vga.o drivers/fash.o drivers/io.o drivers/keyboard.o libs/string.o kgos.o kernel/input.o kernel/logo.o kernel/commands/commands.o kernel/commands/help.o kernel/commands/exit.o kernel/commands/clear.o kernel/commands/echo.o kernel/commands/info.o kernel/commands/version.o kernel/commands/date.o kernel/commands/memory.o kernel/commands/reboot.o kernel/commands/color.o kernel/commands/run.o kernel/commands/demo.o kernel/commands/kg.o kernel/programms/runner.o kernel/programms/demo.o kernel/programms/kgter.o -o $@

kernel.bin: kernel.elf
	objcopy -O binary $< $@

os.img: boot.bin kernel.bin
	rm -f $@
	$(eval TOTAL_SECTORS := $(shell echo $$((1 + $(KERNEL_SECTORS) + 1))))
	dd if=/dev/zero of=$@ bs=512 count=$(TOTAL_SECTORS) 2>/dev/null
	dd if=boot.bin of=$@ bs=512 conv=notrunc 2>/dev/null
	dd if=kernel.bin of=$@ bs=512 seek=1 conv=notrunc 2>/dev/null

run:
	qemu-system-x86_64 -drive format=raw,file="os.img" -serial stdio

.PHONY: all run clean

clean:
	rm -f *.o *.bin *.elf *.img *.iso
	rm -rf grub/
	rm -rf drivers/*.o
	rm -rf kernel/*.o
	rm -rf kernel/commands/*.o

iso: os.img
	mkdir -p iso/boot
	cp os.img iso/boot/
	genisoimage -R -b boot/os.img -no-emul-boot -boot-load-size 4 -boot-info-table -o kgos.iso iso/
	rm -rf iso/

run-iso: iso
	qemu-system-x86_64 -cdrom kernelos.iso -serial stdio