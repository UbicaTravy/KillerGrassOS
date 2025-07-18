check_reboot:
    mov di, reboot_cmd
    call strcmp
    jne .skip
    mov si, reboot_msg
    call print
    ; Триггер 8042 контроллера клавиатуры
    mov al, 0xFE
    out 0x64, al
    ret
.skip:
    ret

reboot_cmd db "reboot", 0
reboot_msg db "Restarting system...", 0x0D, 0x0A, 0