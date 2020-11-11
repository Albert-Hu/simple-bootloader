# How to Dump the ELF

```
arm-none-eabi-objdump -D [file]
```

# How to Debug using GDB

```
qemu-system-arm -M stm32-p103 -nographic -kernel [elf file] -S -gdb tcp::[port number]
```
