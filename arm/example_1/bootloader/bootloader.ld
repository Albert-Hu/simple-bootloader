ENTRY(reset_handler)

MEMORY
{
	ROM (rx) : ORIGIN = 0x08000000, LENGTH = 64K
	RAM (rwx) : ORIGIN = 0x20000000, LENGTH = 32K
	DRAM (rwx) : ORIGIN = 0x20008000, LENGTH = 32K
}

SECTIONS
{
	.text :
	{
		KEEP(*(.isr_vector))
		*(.text)
		*(.text.*)
		*(.rodata)
		*(.rodata.*)
		_sromdev = .;
		_eromdev = .;
		_sidata = .;
	} >ROM

	.data : AT(_sidata)
	{
		_sdata = .;
		*(.data)
		*(.data.*)
		_edata = .;
	} >RAM

	.bss :
	{
		_sbss = .;
		*(.bss)
		_ebss = .;
	} >RAM

	.ARM.exidx :
	{
		*(.ARM.exidx* .gnu.linkonce.armexidx.*)
	} >RAM

	_app_rom = ORIGIN(ROM) + LENGTH(ROM);
	_estack = ORIGIN(RAM) + LENGTH(RAM);
	_heap_begin = ORIGIN(DRAM);
	_heap_end = ORIGIN(DRAM) + LENGTH(DRAM);
}
