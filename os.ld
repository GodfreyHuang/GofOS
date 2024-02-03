# The ISA is RISC-V
OUTPUT_ARCH( "riscv" )

# OS Entry Point is boot
ENTRY( _boot )

# The memory setting: Start at 0x80000000 to 0x88000000
# wxa!ri = can write, execute, available
MEMORY
{
    ram   (wxa!ri) : ORIGIN = 0x80000000, LENGTH = 128M
}

# PHDRS means OS need to load .text, .data and .bss
# test means machine codes
# data means initialized static data, read only data called rodata
# bss means uninitialized static data
PHDRS
{
    text PT_LOAD;
    data PT_LOAD;
    bss PT_LOAD;
}

# SECTIONS : define the definition of each PHDRS
# PROVIDE can help us the define symbols, these symbols are represent memory address
# *(XXX)
# "ram AT" : means VMA(Virtual Memory Address), SECTIONS will get this memory address when run the program
# "ram: test" :  means LMA(Load Memory Address)
SECTIONS
{
    .text : {
        PROVIDE(_text_start = .);
        *(.text.init) *(.text .text.*)
        PROVIDE(_text_end = .);
    } >ram AT>ram :text

    .rodata : {
        PROVIDE(_rodata_start = .);
        *(.rodata .rodata.*)
        PROVIDE(_rodata_end = .);
    } >ram AT>ram :text

    .data : {
        . = ALIGN(4096);
        PROVIDE(_data_start = .);
        *(.sdata .sdata.*) *(.data .data.*)
        PROVIDE(_data_end = .);
    } >ram AT>ram :data

    .bss :{
        PROVIDE(_bss_start = .);
        *(.sbss .sbss.*) *(.bss .bss.*)
        PROVIDE(_bss_end = .);
    } >ram AT>ram :bss

# Here define the start point and the end point of memory
    PROVIDE(_memory_start = ORIGIN(ram));
    PROVIDE(_memory_end = ORIGIN(ram) + LENGTH(ram));

# Here define the size of the heap, which can use malloc()
    PROVIDE(_heap_start = _bss_end);
    PROVIDE(_heap_size = _memory_end - _heap_start);
}
