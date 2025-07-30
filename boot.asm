[org 0x7C00]
[bits 16]

start:
    ; Инициализируем сегментные регистры
    cli
    mov ax, 0
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7C00

    ; Сохраняем номер диска
    mov [boot_drive], dl

    ; Выводим сообщение о загрузке
    mov si, loading_msg
    call print_string

    ; Читаем ядро с диска (только 5 секторов для начала)
    mov ah, 0x02        ; Функция чтения диска
    mov al, 5           ; Количество секторов (2.5KB)
    mov ch, 0           ; Цилиндр 0
    mov cl, 2           ; Сектор 2
    mov dh, 0           ; Головка 0
    mov dl, [boot_drive] ; Номер диска
    mov bx, 0x8000      ; Адрес загрузки
    int 0x13
    jc disk_error

    ; Выводим сообщение об успешном чтении
    mov si, disk_ok_msg
    call print_string

    ; Простой переход в защищенный режим (без Long Mode для начала)
    cli
    
    ; Загружаем GDT
    lgdt [gdt_descriptor]
    
    ; Включаем A20
    in al, 0x92
    or al, 2
    out 0x92, al
    
    ; Включаем защищенный режим
    mov eax, cr0
    or eax, 1
    mov cr0, eax
    
    ; Длинный переход в защищенный режим
    jmp 0x08:protected_mode

disk_error:
    mov si, disk_error_msg
    call print_string
    jmp $

print_string:
    lodsb
    or al, al
    jz .done
    mov ah, 0x0E
    int 0x10
    jmp print_string
.done:
    ret

[bits 32]
protected_mode:
    ; Устанавливаем сегментные регистры
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    
    ; Устанавливаем стек
    mov esp, 0x90000
    
    ; Копируем ядро в правильное место
    mov esi, 0x8000
    mov edi, 0x100000
    mov ecx, 0x1400    ; 5KB
    rep movsb
    
    ; Переход к ядру
    jmp 0x100000

; Данные
boot_drive db 0
loading_msg db 'Loading FecalOS (Simple)...', 13, 10, 0
disk_ok_msg db 'Disk OK!', 13, 10, 0
disk_error_msg db 'Disk error!', 13, 10, 0

; GDT для защищенного режима
gdt_start:
    dq 0x0000000000000000  ; Null descriptor
    dq 0x00CF9A000000FFFF  ; Code segment (0x08)
    dq 0x00CF92000000FFFF  ; Data segment (0x10)
gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start

times 510-($-$$) db 0
dw 0xAA55 