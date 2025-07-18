check_time:
    mov di, time_command
    call strcmp
    jne time_skip
    
    mov si, time_time_msg
    call print
    
    ; Получаем время от BIOS
    mov ah, 0x02
    int 0x1A
    jc time_error
    
    ; Часы
    mov al, ch
    call time_print_bcd
    mov al, ':'
    call time_print_char
    
    ; Минуты
    mov al, cl
    call time_print_bcd
    mov al, ':'
    call time_print_char
    
    ; Секунды
    mov al, dh
    call time_print_bcd
    
    jmp time_done
    
time_error:
    mov si, time_error_msg
    call print
time_done:
    mov si, time_crlf
    call print
    
    mov byte [cmd_handled], 1
time_skip:
    ret

time_print_bcd:
    mov ah, al
    shr al, 4
    add al, '0'
    call time_print_char
    mov al, ah
    and al, 0x0F
    add al, '0'
time_print_char:
    mov ah, 0x0E
    int 0x10
    ret

time_command db "time", 0
time_time_msg db "Current time: ", 0
time_error_msg db "Error reading time", 0x0D, 0x0A, 0
time_crlf db 0x0D, 0x0A, 0