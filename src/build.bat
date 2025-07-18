@echo off
nasm -f bin boot.asm -o boot.bin
nasm -f bin kernel.asm -o kernel.bin

echo Проверка размеров:
echo Загрузчик: 
dir boot.bin
echo Ядро: 
dir kernel.bin

copy /b boot.bin + kernel.bin os.bin

echo Запуск QEMU...
qemu-system-i386 -drive format=raw,file=os.bin
pause