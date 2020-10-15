CROSS_COMPILE ?= arm-none-eabi-
CC := $(CROSS_COMPILE)gcc
CFLAGS = -fno-common -g \
	 -mcpu=cortex-m3 -mthumb \
	 -T app.ld -nostartfiles \

TARGET = app.elf
all: $(TARGET)

$(TARGET): app.c startup.c port.c
	$(CC) $(CFLAGS) $^ -o app.elf

clean:
	rm -f *.o *.elf
