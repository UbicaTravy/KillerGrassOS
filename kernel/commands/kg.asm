bits 16

extern kg_editor

check_kg:
    mov si, cmd_kg
    mov di, cmd_buffer
    call strcmp
    jc .kg_command
    ret

.kg_command:
    mov byte [cmd_handled], 1  ; Важно: помечаем команду как обработанную!
    call kg_editor
    ret

cmd_kg db "kg", 0