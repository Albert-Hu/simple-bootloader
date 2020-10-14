# Boot Flow
1. Execute bootloader code from 0x08000000.
2. Run bootloader and initialize RAM, setup the .data section and clean up .bss section.
3. Copy config to RAM which address at 0x20000000.
4. Finish boot procedure and execute app code from 0x08008000.
5. Run app and initialize RAM, setup the .data section and clean up .bss section.
6. Print config from RAM which address at 0x20000000.

# What does Bootloader do?
1. Copy config from ROM to RAM.
2. Print booting message.
3. Reset MSP(Main Stack Pointer) register.
4. Reset PC(Program Counter) to app's entry point.

# What does app do?
1. Print config.
2. Print app message.

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

# RAM
- Total RAM size is 64KB.
- Config store at 0x20000000 which size is 4KB.
- RAM size used by bootloader and app is 60KB.
- Data section and BSS section are at 0x20001000
- Stack pointer is at 0x20010000

```
+------------+ 0x20010000
| Bootloader |
|     &      |
|    APP     |
+------------+ 0x20001000
|   Config   |
+------------+ 0x20000000
```

# Reference
- [mini-arm-os](https://github.com/jserv/mini-arm-os)
- [How to Write a Bootloader from Scratch](https://interrupt.memfault.com/blog/how-to-write-a-bootloader-from-scratch)
