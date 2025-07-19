bits 16
global kg_editor

kg_editor:
    ; Очистка экрана
    mov ax, 0x0003
    int 0x10

    ; Вывод заголовка
    mov si, kg_header
    call print

.input_loop:
    ; Чтение клавиши
    mov ah, 0x00
    int 0x16

    ; Выход по Ctrl+X
    cmp al, 0x18
    je .exit_editor

    ; Backspace
    cmp al, 0x08
    je .backspace

    ; Enter
    cmp al, 0x0D
    je .newline

    ; Обычный символ
    mov ah, 0x0E
    int 0x10
    jmp .input_loop

.backspace:
    mov ah, 0x0E
    mov al, 0x08
    int 0x10
    mov al, ' '
    int 0x10
    mov al, 0x08
    int 0x10
    jmp .input_loop

.newline:
    mov ah, 0x0E
    mov al, 0x0D
    int 0x10
    mov al, 0x0A
    int 0x10
    jmp .input_loop

.exit_editor:
    ret

kg_header db "KG Editor (Ctrl+X to exit)", 0x0D, 0x0A, 0x0A, 0