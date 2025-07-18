# Fecal OS

![ASM](https://img.shields.io/badge/Assembler-16_bit-007AAC?style=flat&logo=assemblyscript&logoColor=white)
![NASM](https://img.shields.io/badge/Assembler-NASM-007AAC?style=flat&logo=assemblyscript&logoColor=white)
[![QEMU x86](https://img.shields.io/badge/QEMU-x86-FF6600?style=flat)]()

This is the English README

[![Русский](https://img.shields.io/badge/README-Русский-blue)](README_ru.md)


<div align="center">
<img src="img/Fecal_OS_logo.png" width="500" alt="FecalOS_logo"/>
</div>

# Simple OS on Assembler

FecalOS is a minimal 16-bit x86 operating system designed for entertainment and educational purposes. It runs in real mode and includes its own bootloader, kernel, and basic system commands. The project demonstrates low-level programming using BIOS interrupts for I/O, disk operations, and memory management.

<div align="center">

## Current OS version: v0.0001
</div>

<div align="center">
<img src="img/FecalOS_is_not UNIX.png" width="700" alt="FecalOS_meme"/>
</div>

## Project structure
```
FecalOS/
├── boot.asm            # Booter (512 байт)
├── kernel/
│   ├── main.asm        # Kernel OS
│   └── commands/       # System commands
│       ├── help.asm    # Help
│       ├── clear.asm   # Clear screen
│       ├── exit.asm    # Shutdown
│       ├── info.asm    # Info about system
│       ├── mem.asm     # Info about memory
│       ├── time.asm    # Show time
│       └── reboot.asm  # Reboot
├── lib/
│   ├── io.asm          # Input/Output
│   └── string.asm      # String operation
└── build.bat           # Build and run OS
```

## Basic technologies:

- BIOS interrupts for I/O
- Real Mode (16-bit x86 mode)
- MBR boot (without GRUB)
- VGA text mode (80x25)

## Bootloader (512 bytes)

- Standalone MBR bootloader (512 bytes)
- Loading kernel from disk at address 0x8000
- Checking for disk read errors
- Transition to protected mode (not implemented yet, but there is a template)

## Base kernel (kernel/main.asm):

- Initialization of segment registers
- Command management via a single handler
- System input buffer (64 bytes)
- Mechanism for handling unknown commands

## Drivers and libraries

- VGA driver (via BIOS int 0x10):
- Text output (80x25 mode)
- Screen clearing (clear command)
- Backspace support when input

## Keyboard input (via BIOS int 0x16):

- Reading scan codes
- Enter/Backspace processing
- Input buffering

## String functions (lib/string.asm):

- strcmp - string comparison
- Converting numbers to strings (for mem)

## Critical components:

```asm
int 0x10 # BIOS Video Service
int 0x16 # Keyboard Input
int 0x13 # Disk Operations
int 0x15 # Advanced Services
int 0x1A # Real Time Clock
```

## Project memory:

```
Address       Purpose Size
0x7C00-0x7DFF Bootloader (MBR) 512 bytes
0x8000-0x8FFF OS kernel 4KB
0x9000-0x9FFF Command buffer 4KB
0xA000-0xFFFF Stack and temporary data 24KB
```

## System commands
```
Command  File                 Functionality
help     commands/help.asm    List of commands
clear    commands/clear.asm   Clear screen
exit     commands/exit.asm    Shutdown (via ACPI/hang)
info     commands/info.asm    CPU and memory information
mem      commands/mem.asm     Base memory size (int 0x12)
time     commands/time.asm    Current time (via CMOS)
reboot   commands/reboot.asm  Reboot(trigger 0xFE to port 0x64)
```

# Now, you can seen

<img src="img/screenshot_v0.0001.jpg" width="700" alt="FecalOS_meme"/>

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