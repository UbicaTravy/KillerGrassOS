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

    ; Сообщение о загрузке
    mov si, loading_msg
    call print

    ; Загрузка ядра (2 сектора)
    mov ah, 0x02
    mov al, 2
    mov ch, 0
    mov cl, 2
    mov dh, 0
    mov bx, 0x8000  ; Грузим по адресу 0x8000
    int 0x13
    jc disk_error

    ; Переход к ядру
    jmp 0x0000:0x8000

disk_error:
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

loading_msg db "Booting FecalOS...", 0x0D, 0x0A, 0
error_msg db "Disk error!", 0

times 510-($-$$) db 0
dw 0xAA55