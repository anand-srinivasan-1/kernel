starting_address = 0x100000;

OUTPUT_FORMAT(elf64-x86-64)
ENTRY(_start)
SECTIONS
{
    . = starting_address;
    .text : {
        *(.text)
    }
    .data : {
        *(.data)
    }
    .bss : {
        *(.bss)
    }
    /DISCARD/ : {
        *(.interp)
        *(.comment)
        *(.note)
        *(.note.*)
    }
}
