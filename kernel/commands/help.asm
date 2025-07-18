check_help:
    mov di, .command
    call strcmp
    jne .skip
    mov si, .help_msg
    call print
.skip:
    ret

.command db "help", 0
.help_msg db "Available commands:", 0x0D, 0x0A
          db "help   - Show this help", 0x0D, 0x0A
          db "clear  - Clear screen", 0x0D, 0x0A
          db "info   - System info", 0x0D, 0x0A
          db "mem    - Memory info", 0x0D, 0x0A
          db "time   - Show time", 0x0D, 0x0A
          db "reboot - Restart system", 0x0D, 0x0A
          db "exit   - Shutdown", 0x0D, 0x0A, 0