# Requirements
- ARM Toolchain(arm-none-eabi)
- QEMU(qemu-system-arm)

# Simple Bootloader for STM32-P103
- [Example 1](/arm/example_1)
- [Example 2](/arm/example_2)

# How to Dump the ELF

```
arm-none-eabi-objdump -D [file]
```

# How to Debug using GDB

```
qemu-system-arm -M stm32-p103 -nographic -kernel [elf file] -S -gdb tcp::[port number]
```
