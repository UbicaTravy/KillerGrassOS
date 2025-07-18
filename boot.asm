bits 16
org 0x7C00

start:
    cli
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7C00
    sti

    ; Очистка экрана
    mov ax, 0x0003
    int 0x10

    ; Загрузка ядра (2 сектора)
    mov ah, 0x02
    mov al, 2
    mov ch, 0
    mov cl, 2
    mov dh, 0
    mov bx, 0x8000
    int 0x13
    jc error

    ; Переход к ядру
    jmp 0x0000:0x8000

error:
    mov si, error_msg
    call print
    jmp $

print:
    lodsb
    test al, al
    jz .done
    mov ah, 0x0E
    int 0x10
    jmp print
.done:
    ret

error_msg db "Boot error!", 0

times 510-($-$$) db 0
dw 0xAA55