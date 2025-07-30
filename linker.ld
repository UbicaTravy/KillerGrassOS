ENTRY(_start)

SECTIONS {
    . = 0x100000;
    
    .text : {
        *(.text)
        *(.text.*)
    }
    
    .data : { 
        *(.data)
        *(.data.*)
    }
    
    .bss : { 
        *(.bss)
        *(.bss.*)
    }
    
    .rodata : {
        *(.rodata)
        *(.rodata.*)
    }
    
    /DISCARD/ : {
        *(.comment)
        *(.note.*)
    }
} 