check_mem:
    mov di, mem_command
    call strcmp
    jne mem_skip
    
    mov si, mem_mem_msg
    call print
    
    ; Получаем размер базовой памяти
    int 0x12
    call mem_print_dec
    
    mov si, mem_kb_msg
    call print
    
    mov byte [cmd_handled], 1
mem_skip:
    ret

mem_print_dec:
    mov bx, 10
    xor cx, cx
mem_dec_loop:
    xor dx, dx
    div bx
    push dx
    inc cx
    test ax, ax
    jnz mem_dec_loop
mem_print_digit:
    pop ax
    add al, '0'
    mov ah, 0x0E
    int 0x10
    loop mem_print_digit
    ret

mem_command db "mem", 0
mem_mem_msg db "Base memory: ", 0
mem_kb_msg  db " KB", 0x0D, 0x0A, 0