ENTRY(reset_handler)

/*
	The STM32-P103 has 128 KB flash and 20 KB RAM.
	The bootloader uses half of the size of the flash.
*/
MEMORY
{
	FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 64K
	SRAM (rwx) : ORIGIN = 0x20000000, LENGTH = 20K
}

SECTIONS
{
	.text : ALIGN(4)
	{
		FILL(0xff)
		KEEP(*(.isr_vector))
		. = ALIGN(4);

		/* Data Section Information */
		_data_section = .;
		/* LMA, Load Memory Address */
		LONG(LOADADDR(.data));
		/* VMA, Virtual Memory Address */
		LONG(ADDR(.data));
		LONG(SIZEOF(.data));

		/* BSS Section Information */
		_bss_section = .;
		/* VMA, Virtual Memory Address */
		LONG(ADDR(.bss));
		LONG(SIZEOF(.bss));
	} > FLASH

	.text : ALIGN(4)
	{
		*(.text* .text.*)
		*(.rodata .rodata.*)
		. = ALIGN(4);
	} > FLASH

	.data : ALIGN(4)
	{
		FILL(0xff)
		*(.data .data.*)
		. = ALIGN(4);
	} > SRAM AT>FLASH

	.bss : ALIGN(4)
	{
		FILL(0xff)
		*(.bss .bss.*)
		. = ALIGN(4);
	} > SRAM

	_stack_size = 4k;
	_stack_top = ORIGIN(SRAM) + LENGTH(SRAM) - 4;
	_heap_begin = ORIGIN(SRAM) + SIZEOF(.data) + SIZEOF(.bss);
	_heap_end = ORIGIN(SRAM) + LENGTH(SRAM) - _stack_size;

	/* That the entry point address of the application. */
	_app_entry = ORIGIN(FLASH) + LENGTH(FLASH);
}
