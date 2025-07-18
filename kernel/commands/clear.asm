check_clear:
    mov di, .command
    call strcmp
    jne .skip
    mov ax, 0x0003
    int 0x10
.skip:
    ret

.command db "clear", 0