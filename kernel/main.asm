bits 16
org 0x8000

; Точка входа ядра
start:
    ; Инициализация сегментов
    mov ax, cs
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7C00  ; Используем стек ниже загрузчика

    ; Очистка экрана
    mov ax, 0x0003
    int 0x10

    ; Вывод приветствия
    mov si, os_name
    call print

    ; Переход к основному циклу
    jmp main_loop

; Подключаем библиотеки
%include "../lib/io.asm"
%include "../lib/string.asm"

; Подключаем команды
%include "commands/help.asm"
%include "commands/clear.asm"
%include "commands/exit.asm"
%include "commands/info.asm"
%include "commands/mem.asm"
%include "commands/time.asm"
%include "commands/reboot.asm"

main_loop:
    ; Проверка целостности стека
    cmp sp, 0x7C00
    jae .stack_ok
    mov si, stack_error_msg
    call print
    mov sp, 0x7C00
.stack_ok:

    ; Вывод промпта
    mov si, prompt
    call print

    ; Чтение команды
    mov di, cmd_buffer
    call read_string

    ; Обработка команд
    call handle_command
    jmp main_loop

handle_command:
    ; Сброс флага обработки
    mov byte [cmd_handled], 0
    
    ; Проверяем все команды
    call check_help
    call check_clear
    call check_exit
    call check_info
    call check_mem
    call check_time
    call check_reboot
    
    ; Если команда не распознана
    cmp byte [cmd_handled], 1
    je .done
    
    mov si, unknown_cmd
    call print
    
.done:
    ret

; Данные
os_name:
    db " /$$$$$$$$                            /$$    /$$$$$$   /$$$$$$ ", 0x0D, 0x0A
    db "| $$_____/                           | $$   /$$__  $$ /$$__  $$", 0x0D, 0x0A
    db "| $$     /$$$$$$   /$$$$$$$  /$$$$$$ | $$|   $$  \ $$| $$  \__/", 0x0D, 0x0A
    db "| $$$$$ /$$__  $$ /$$_____/ |____  $$| $$|   $$  | $$|  $$$$$$ ", 0x0D, 0x0A
    db "| $$__/| $$$$$$$$| $$        /$$$$$$$| $$|   $$  | $$ \____  $$", 0x0D, 0x0A
    db "| $$   | $$_____/| $$       /$$__  $$| $$|   $$  | $$ /$$  \ $$", 0x0D, 0x0A
    db "| $$   |  $$$$$$$|  $$$$$$$|  $$$$$$$| $$|    $$$$$$/|  $$$$$$/", 0x0D, 0x0A
    db "|__/    \_______/ \_______/ \_______/|__/   \______/  \______/ ", 0x0D, 0x0A
    db "______________________________________________________________", 0x0D, 0x0A
    db "|  FecalOS:                                        v0.0001    |", 0x0D, 0x0A
    db "|  GitHub:            https://github.com/UbicaTravy/FecalOS/  |", 0x0D, 0x0A
    db "|-------------------------------------------------------------|", 0x0D, 0x0A
    db "|                  Created by KillerGrass                     |", 0x0D, 0x0A
    db "|                    License GNU GPL v3                       |", 0x0D, 0x0A
    db "==============================================================", 0x0D, 0x0A, 0

prompt db "> ", 0
cmd_buffer times 64 db 0
unknown_cmd db "Unknown command", 0x0D, 0x0A, 0
cmd_handled db 0
stack_error_msg db "Stack corruption detected! Reset to 0x7C00", 0x0D, 0x0A, 0