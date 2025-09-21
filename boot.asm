; bootloader KillerGrass OS

[org 0x7C00]
[bits 16]

%ifndef KERNEL_SECTORS
%define KERNEL_SECTORS 40 ; fallback if not provided by build system
%endif

start:
    ; инициализируем сегментные регистры
    cli
    xor ax, ax ; Я НИКОГДА НЕ НАПИШУ mov ax, 0!
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7C00

    ; сохраняем номер диска
    mov [boot_drive], dl

    ; сообщение о загрузке
    mov si, loading_msg
    call print_string

    ; оставляем стандартный текстовый режим 80x25

    ; читаем ядро с диска
    mov ah, 0x02        ; функция чтения диска
    mov al, KERNEL_SECTORS ; количество секторов ядра
    mov ch, 0           ; цилиндр 0
    mov cl, 2           ; сектор 2
    mov dh, 0           ; головка 0
    mov dl, [boot_drive] ; номер диска
    mov bx, 0x8000      ; адрес загрузки
    int 0x13
    jc disk_error

    ; выводим сообщение об успешном чтении
    mov si, disk_ok_msg
    call print_string

    ; простой переход в защищенный режим
    cli
    
    ; загружаем GDT
    lgdt [gdt_descriptor]
    
    ; включаем A20
    in al, 0x92
    or al, 2
    out 0x92, al
    
    ; включаем защищенный режим
    mov eax, cr0
    or eax, 1
    mov cr0, eax
    
    ; длинный переход в защищенный режим
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

; 32 битный режим
[bits 32]
protected_mode:
    ; инициализируем сегментные регистры
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov esp, 0x90000
    
    ; копируем ядро в правильное место (1MB)
    mov esi, 0x8000
    mov edi, 0x100000
%define KERNEL_BYTES (KERNEL_SECTORS * 512)
    mov ecx, KERNEL_BYTES
    rep movsb
    
    ; переход к ядру
    call 0x100000
    
    ; если ядро вернется (не должно), то зависаем
    jmp $

; данные
boot_drive db 0
loading_msg db 'Loading KillerGrass OS (KGOS)...', 13, 10, 0
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

times 510-($-$$) db 0 ; остальное заполняем нулями. до 510 потому что 2 байта уходят на магическое число в конце
dw 0xAA55 