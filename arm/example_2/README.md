# Boot Flow
1. Execute bootloader code from 0x08000000.
2. Run bootloader and initialize RAM, setup the .data section and clean up .bss section.
3. Finish boot procedure and execute app code from 0x08008000.
4. Run app and initialize RAM, setup the .data section and clean up .bss section.

# What does Bootloader do?
1. Print booting message.
2. Reset MSP(Main Stack Pointer) register.
3. Reset PC(Program Counter) to app's entry point.

# What does app do?
1. Just print message.

# ROM Partition
- Bootloader start at 0x08000000
- APP start at 0x08008000

```
+------------+
|            |
|    APP     |
+------------+ 0x08008000
|            |
| Bootloader |
+------------+ 0x08000000
```

# RAM & DRAM
- RAM is used by main stack pointer.
- DRAM is used by heap of malloc.

```
+------------+ 0x20010000
|            |
|   (DRAM)   |
+------------+ 0x20008000
|            |
|   (RAM)    |
+------------+ 0x20000000
```

## RAM
- RAM size is 32KB.
- RAM start at 0x20000000

## DRAM
- DRAM size is 32KB.
- DRAM start at 0x20008000

# Reference
- [mini-arm-os](https://github.com/jserv/mini-arm-os)
- [How to Write a Bootloader from Scratch](https://interrupt.memfault.com/blog/how-to-write-a-bootloader-from-scratch)
