check_info:
    mov di, info_command
    call strcmp
    jne info_skip
    
    mov si, info_info_msg
    call print
    
    ; Выводим информацию о процессоре
    mov si, info_cpu_msg
    call print
    
    ; Упрощенное определение CPU
    pushf
    pop ax
    and ax, 0x0FFF
    push ax
    popf
    pushf
    pop ax
    and ax, 0xF000
    cmp ax, 0xF000
    je .cpu_8086
    mov si, info_cpu_286_str
    jmp .print_cpu
    
.cpu_8086:
    mov si, info_cpu_8086_str
    
.print_cpu:
    call print
    
    ; Выводим информацию о памяти
    mov si, info_mem_msg
    call print
    int 0x12
    call info_print_dec
    mov si, info_kb_msg
    call print
    
    ; Выводим информацию о времени
    mov si, info_time_msg
    call print
    mov ah, 0x02
    int 0x1A
    jc .time_error
    mov al, ch
    call info_print_bcd
    mov al, ':'
    call info_print_char
    mov al, cl
    call info_print_bcd
    mov al, ':'
    call info_print_char
    mov al, dh
    call info_print_bcd
    jmp .done_time
    
.time_error:
    mov si, info_time_error_msg
    call print
    
.done_time:
    mov si, info_crlf
    call print
    
    mov byte [cmd_handled], 1
info_skip:
    ret

; Вспомогательные функции
info_print_dec:
    mov bx, 10
    xor cx, cx
.dec_loop:
    xor dx, dx
    div bx
    push dx
    inc cx
    test ax, ax
    jnz .dec_loop
.print_digit:
    pop ax
    add al, '0'
    mov ah, 0x0E
    int 0x10
    loop .print_digit
    ret

info_print_bcd:
    mov ah, al
    shr al, 4
    add al, '0'
    call info_print_char
    mov al, ah
    and al, 0x0F
    add al, '0'
info_print_char:
    mov ah, 0x0E
    int 0x10
    ret

; Данные команды
info_command db "info", 0
info_info_msg:
    db " ___________________________ ", 0x0D, 0x0A
    db "|=== System Information ===|", 0x0D, 0x0A
    db "|--------------------------|", 0x0D, 0x0A
    db "| OS Version:     v0.0001  |", 0x0D, 0x0A
    db "|                          |", 0x0D, 0x0A, 0

info_cpu_msg db "| CPU: ", 0
info_cpu_8086_str db "8086/8088          |", 0x0D, 0x0A, 0
info_cpu_286_str db "80286 or higher     |", 0x0D, 0x0A, 0

info_mem_msg db "| Base memory: ", 0
info_kb_msg db " KB      |", 0x0D, 0x0A, 0

info_time_msg db "| Current time: ", 0
info_time_value db "HH:MM:SS         |", 0x0D, 0x0A  ; Шаблон для вывода времени
info_time_error_msg db "Error            |", 0x0D, 0x0A
    db "|__________________________|", 0x0D, 0x0A, 0
info_crlf db 0x0D, 0x0A, 0