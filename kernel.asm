bits 16
org 0x8000

start:
    ; Инициализация
    mov ax, 0x0003
    int 0x10

    ; Вывод приветствия
    mov si, os_name
    call print

main_loop:
    ; Вывод промпта
    mov si, prompt
    call print

    ; Чтение команды
    mov di, cmd_buffer
    call read_string

    ; Обработка команд
    call handle_command
    jmp main_loop

; Подключаем модули
%include "io.asm"
%include "string.asm"

; Данные
os_name db "FecalOS v0.0001", 0x0D, 0x0A, 0
prompt db "> ", 0
cmd_buffer times 64 db 0
help_msg db "Commands: help, clear, exit", 0x0D, 0x0A, 0
bye_msg db "Shutting down...", 0

; Обработчик команд
handle_command:
    mov si, cmd_buffer
    mov di, cmd_help
    call strcmp
    je .help

    mov di, cmd_clear
    call strcmp
    je .clear

    mov di, cmd_exit
    call strcmp
    je .exit

    ; Неизвестная команда
    mov si, unknown_cmd
    call print
    ret

.help:
    mov si, help_msg
    call print
    ret

.clear:
    mov ax, 0x0003
    int 0x10
    ret

.exit:
    mov si, bye_msg
    call print
    jmp $

cmd_help db "help", 0
cmd_clear db "clear", 0
cmd_exit db "exit", 0
unknown_cmd db "Unknown command", 0x0D, 0x0A, 0