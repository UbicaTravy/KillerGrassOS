@echo off
del *.bin /q >nul 2>&1

echo [1/3] Building bootloader...
nasm -f bin boot.asm -o boot.bin

echo [2/3] Building kernel...
nasm -f bin kernel/main.asm -o kernel.bin -ikernel/ -ilib/

echo [3/3] Creating disk image...
fsutil file createnew padding.bin 4096 >nul
copy /b boot.bin + kernel.bin + padding.bin os.bin
del padding.bin

echo.
echo File sizes:
echo - Bootloader: 
dir boot.bin
echo - Kernel: 
dir kernel.bin
echo - Disk image: 
dir os.bin
pause