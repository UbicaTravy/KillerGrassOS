KillerGrass OS (KGOS)

> **KillerGrass OS (KGOS)** is a simple 32-bit operating system with a modular kernel, VGA driver, basic command shell, and demo user code. See below for Russian description and details.

---

![ASM](https://img.shields.io/badge/Assembler-32_bit-007AAC?style=flat&logo=assemblyscript&logoColor=white)
![NASM](https://img.shields.io/badge/Assembler-NASM-007AAC?style=flat&logo=assemblyscript&logoColor=white)
![C](https://img.shields.io/badge/C-A8B9CC?style=for-the-badge&logo=c&logoColor=white)
[![QEMU x86](https://img.shields.io/badge/QEMU-x86-FF6600?style=flat)]()

<div align="center">
<img src="img/killergrass_os_logo.jpg" width="500" alt="KGOS_logo"/>
</div>

**KillerGrass OS (KGOS)** — простая 32-битная операционная система с модульным ядром, VGA-драйвером, базовой командной оболочкой и выполнением встроенных команд.

Последняя версия: v0.0003

[Биография и документация проекта](BIO-FECALOS.md)

---

## Быстрый старт

### Сборка и запуск в QEMU

```bash
sudo apt install gcc nasm binutils grub-pc-bin xorriso qemu-system-x86
make clean && make
qemu-system-x86_64 -cdrom os.img -serial stdio
```

---

## 📁 Структура проекта (тут не всё, но самое главное)

```
KillerGrassOS/
├── drivers/           # драйверы устройств (VGA, клавиатура)
│   ├── vga.c/h
│   ├── keyboard.c/h
|   ├── fash.c         # командная оболочка
├── kernel/
|   ├── commands/      # команды
|   ├── programms      # программы
|   ├── logo.c         # логотип
|   ├── logo.h
├── libs/              # бибилиотеки строк и типов
├── kernel.c           # ядро: инициализация, проверки, запуск fecalos_main
├── fecalos.c          # пользовательская/демонстрационная логика ОС
├── fecalos.h          # прототип fecalos_main
├── string.c/h         # строковые функции
├── types.h            # собственные типы (size_t, uint32_t и др.)
├── boot.asm           # загрузчик
├── linker.ld          # скрипт линковки
└── Makefile           # система сборки
```

## Сборка

### Требования

- gcc (32-битная поддержка)
- nasm
- ld, objcopy (binutils)
- qemu-system-x86 (для теста)

### Основные команды

```bash
make clean         # очистить сборку
make               # собрать образ os.img (флоппи)
make iso           # собрать загрузочный ISO-образ
make run           # запустить os.img в QEMU
```

---

## Запуск

  ```bash
  make run
  ```

---

## Возможности

- VGA текстовый режим (16 цветов, индивидуальный фон для каждой строки)
- PS/2 клавиатура (обработка ввода)
- Командная строка fash (CLI)
- Базовые команды (help, info, clear, echo, version, ...)
- Модульная архитектура (ядро ≠ пользовательская логика, можно легко добавлять свои драйвера, модули и команды)
- Разделение на команды и программы

---

## Contributing

Pull requests, issues, and suggestions are welcome! Feel free to fork the project and make it better. See the code comments for style and humor guidelines :)

---

## License

[![License](https://img.shields.io/badge/License-GNU_GPL_v3.0-green)](LICENSE)

---

## Our in Telegram

[![Telegram](https://img.shields.io/badge/-Telegram-2CA5E0?style=for-the-badge&logo=telegram&logoColor=white)](https://t.me/killergass_os)

---

### Created by KillerGrass

<div align="center">
<img src="img/killergrass_logo.jpg" width="400" alt="KillerGrass_logo"/>

[![GitHub](https://img.shields.io/badge/-GitHub-181717?style=for-the-badge&logo=github&logoColor=white)](https://github.com/UbicaTravy)
[![LIVE Channel](https://img.shields.io/badge/-LIVE%20Kanal-2CA5E0?style=for-the-badge&logo=telegram&logoColor=white)](https://t.me/kanal_kashkamalhika)
</div>

<div align="center">

## Contacts

[![Telegram](https://img.shields.io/badge/Telegram-2CA5E0?style=flat&logo=telegram&logoColor=white)](https://t.me/KillerGrassContactBot)
[![Gmail](https://img.shields.io/badge/Gmail-D14836?style=flat&logo=gmail&logoColor=white)](mailto:killergrasscontact@gmail.com)
</div>
