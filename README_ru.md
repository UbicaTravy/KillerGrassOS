# Fecal OS

![ASM](https://img.shields.io/badge/Assembler-16_bit-007AAC?style=flat&logo=assemblyscript&logoColor=white)
![NASM](https://img.shields.io/badge/Assembler-NASM-007AAC?style=flat&logo=assemblyscript&logoColor=white)
[![QEMU x86](https://img.shields.io/badge/QEMU-x86-FF6600?style=flat)]()

Это README на русском

[![English](https://img.shields.io/badge/README-English-blue)](README_ru.md)


<div align="center">
<img src="img/Fecal_OS_logo.png" width="500" alt="FecalOS_logo"/>
</div>

# Простая ОС на ассемблер

FecalOS — это минимальная 16-битная операционная система x86, разработанная для развлечений и образования. Она работает в реальном режиме и включает в себя собственный загрузчик, ядро и базовые системные команды. Проект демонстрирует низкоуровневое программирование с использованием прерываний BIOS для ввода-вывода, дисковых операций и управления памятью.

<div align="center">

## Последняя доступная версия v0.0001
</div>

<div align="center">
<img src="img/FecalOS_is_not UNIX.png" width="700" alt="FecalOS_meme"/>
</div>

## Структура проекта
```
FecalOS/
├── boot.asm            # Загрузчик (512 bait)
├── kernel/
│   ├── main.asm        # Ядро ОС
│   ├──programs/
│   | └──kg.asm         # Программа KillerGrass текстовый редактор
│   └── commands/       # Системные команды
│       ├── help.asm    # Показать все команды
│       ├── clear.asm   # Отчистить экран
│       ├── exit.asm    # Выключение
│       ├── info.asm    # Инофрмация о системе
│       ├── mem.asm     # Инофрмация о ОЗУ
│       ├── time.asm    # Показать время
│       ├── kg.asm      # KillerGrass Editor команда
│       └── reboot.asm  # Перезапуск
├── lib/
│   ├── io.asm          # Ввод/Вывод
│   └── string.asm      # Строковые операции
├── run.bat             # Запуск ОС
└── build.bat           # Собрать ОС
```

## Базовые технологии:

- Прерывания BIOS для ввода/вывода
- Реальный режим (16-битный режим x86)
- Загрузка MBR (без GRUB)
- Текстовый режим VGA (80x25)

## Загрузчик (512 байт)

- Автономный загрузчик MBR (512 байт)
- Загрузка ядра с диска по адресу 0x8000
- Проверка ошибок чтения с диска
- Переход в защищённый режим (пока не реализовано, но есть шаблон)

## Базовое ядро (kernel/main.asm):

- Инициализация сегментных регистров
- Управление командами через один обработчик
- Системный буфер ввода (64 байта)
- Механизм обработки неизвестных команд

## Драйверы и библиотеки

- Драйвер VGA (через BIOS int 0x10):
- Текстовый вывод (режим 80x25)
- Очистка экрана (команда clear)
- Поддержка Backspace при вводе

## Ввод с клавиатуры (через BIOS int 0x16):

- Чтение скан-кодов
- Обработка Enter/Backspace
- Буферизация ввода

## Строковые функции (lib/string.asm):

- strcmp - сравнение строк
- Преобразование чисел в строки (для памяти)

## Критические компоненты:

```asm
int 0x10 # Видеослужба BIOS
int 0x16 # Ввод с клавиатуры
int 0x13 # Дисковые операции
int 0x15 # Дополнительные службы
int 0x1A # Часы реального времени
```

## Память проекта:

```
Адрес Назначение Размер
0x7C00-0x7DFF Загрузчик (MBR) 512 байт
0x8000-0x8FFF Ядро ОС 4 КБ
0x9000-0x9FFF Буфер команд 4 КБ
0xA000-0xFFFF Стек и временные данные 24 КБ
```

## Системные команды
```
Команда   Файл                 Функционал
help      commands/help.asm    Список Команды
clear     commands/clear.asm   Очистить экран
exit      commands/exit.asm    Выключить (через ACPI/зависание)
info      commands/info.asm    Информация о процессоре и памяти
mem       commands/mem.asm     Базовый размер памяти (int 0x12)
kg        commans/kg.asm       Открыть текстовый редактор KillerGrass
time      commands/time.asm    Текущее время (через CMOS)
reboot    commands/reboot.asm  Перезагрузка (триггер 0xFE на порт 0x64)
```

# Сейчас, вы можете увидеть

<img src="img/screenshot_v0.0001.jpg" width="700" alt="FecalOS_meme"/>

# Я вдохновился

[Little book about creating OS](https://littleosbook.github.io/#host-operating-system)

[Temple OS](https://templeos.org/)
[Что это?](https://en.wikipedia.org/wiki/TempleOS)

[bootOS](https://github.com/nanochess/bootOS)

# License

[![License](https://img.shields.io/badge/License-GNU_GPL_v3.0-green)](LICENSE)

### Created by KillerGrass

<div align="center">

<img src="img/killergrass_logo.jpg" width="400" alt="KillerGrass_logo"/>

[![GitHub](https://img.shields.io/badge/-GitHub-181717?style=for-the-badge&logo=github&logoColor=white)](https://github.com/UbicaTravy)

[![Telegram](https://img.shields.io/badge/-Telegram-2CA5E0?style=for-the-badge&logo=telegram&logoColor=white)](https://t.me/killergrass_programms)

[![LIVE Channel](https://img.shields.io/badge/-LIVE&nbsp;Kanal-2CA5E0?style=for-the-badge&logo=telegram&logoColor=white)](https://t.me/kanal_kashkamalhika)

</div>

<div align="center">

## Contacts

[![Telegram](https://img.shields.io/badge/Telegram-2CA5E0?style=flat&logo=telegram&logoColor=white)](https://t.me/killer_grass1834)
[![Gmail](https://img.shields.io/badge/Gmail-D14836?style=flat&logo=gmail&logoColor=white)](mailto:killergrasscontact@gmail.com)
</div>