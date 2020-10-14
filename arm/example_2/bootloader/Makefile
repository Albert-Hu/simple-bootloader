CROSS_COMPILE ?= arm-none-eabi-
CC := $(CROSS_COMPILE)gcc
CFLAGS = -fno-common -g \
	 -mcpu=cortex-m3 -mthumb \
	 -T bootloader.ld -nostartfiles \

TARGET = bootloader.elf
all: $(TARGET)

$(TARGET): bootloader.c startup.c
	$(CC) $(CFLAGS) $^ -o bootloader.elf

clean:
	rm -f *.o *.elf
