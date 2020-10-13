ENTRY(reset_handler)

MEMORY
{
	ROM (rx) : ORIGIN = 0x08000000, LENGTH = 32K
	RAM (rwx) : ORIGIN = 0x20000000, LENGTH = 64K
}

SECTIONS
{
	.text :
	{
		KEEP(*(.isr_vector))
		*(.text)
		*(.text.*)
		*(.rodata)
		_sromdev = .;
		_eromdev = .;
		_sidata = .;
	} >ROM

	.data : AT(_sidata)
	{
		_sdata = .;
		*(.data)
		*(.data*)
		_edata = .;
	} >RAM

	.bss :
	{
		_sbss = .;
		*(.bss)
		_ebss = .;
	} >RAM

	_estack = ORIGIN(RAM) + LENGTH(RAM);
	_app_rom = ORIGIN(ROM) + LENGTH(ROM);
}
