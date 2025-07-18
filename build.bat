@echo off
nasm -f bin boot.asm -o boot.bin
nasm -f bin kernel.asm -o kernel.bin

:: Создаем образ (загрузчик + ядро + выравнивание)
fsutil file createnew padding.bin 1024 >nul
copy /b boot.bin + kernel.bin + padding.bin os.bin
del padding.bin

:: Запуск
qemu-system-i386 -drive format=raw,file=os.bin
pause