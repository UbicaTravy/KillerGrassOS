bits 16
org 0x8000  ; Соответствует адресу загрузки

start:
    ; Проверка, что мы в ядре
    mov si, kernel_msg
    call print

    ; Основная ОС
    mov si, os_name
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

kernel_msg db "Kernel loaded!", 0x0D, 0x0A, 0
os_name db "FecalOS v0.0001", 0x0D, 0x0A, 0

; Дополняем до 1024 байт (2 сектора)
times 1024-($-$$) db 0