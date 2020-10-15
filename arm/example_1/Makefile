CROSS_COMPILE ?= arm-none-eabi-

TARGET = example_1.bin

all: $(TARGET)

$(TARGET): bootloader.bin app.bin
	$(CROSS_COMPILE)objcopy --gap-fill 0xff --pad-to 0x08010000 -O binary bootloader/bootloader.elf bootloader.bin
	$(CROSS_COMPILE)objcopy -O binary app/app.elf app.bin
	cat $? > $@

app.bin:
	make -C app

bootloader.bin:
	make -C bootloader

qemu: $(TARGET)
	@qemu-system-arm -M ? | grep stm32-p103 >/dev/null || exit
	@echo "Press Ctrl-A and then X to exit QEMU"
	@echo
	qemu-system-arm -M stm32-p103 -nographic -kernel $<

clean:
	make -C app clean
	make -C bootloader clean
	rm -f *.bin

.PHONY: app bootloader
