print:
    lodsb
    test al, al
    jz .done
    mov ah, 0x0E
    int 0x10
    jmp print
.done:
    ret

read_string:
    xor cx, cx
.loop:
    mov ah, 0x00
    int 0x16
    
    cmp al, 0x08
    je .backspace
    
    cmp al, 0x0D
    je .done
    
    cmp cx, 63
    jae .loop
    
    stosb
    inc cx
    
    mov ah, 0x0E
    int 0x10
    jmp .loop

.backspace:
    test cx, cx
    jz .loop
    dec di
    dec cx
    
    mov ah, 0x0E
    mov al, 0x08
    int 0x10
    mov al, ' '
    int 0x10
    mov al, 0x08
    int 0x10
    jmp .loop

.done:
    mov byte [di], 0
    mov ah, 0x0E
    mov al, 0x0D
    int 0x10
    mov al, 0x0A
    int 0x10
    ret