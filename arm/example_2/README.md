# Build & Run

Build the bootloader and the app:

```
make all
```

Run the QEMU:

```
make simulate
```

Clean up the space:

```
make clean
```

# The Boot Flow

1. Run the bootloader.
2. Bootloader initializes the hardware.
3. Bootloader stores the config to the top of the stack of the app.
4. Bootloader decrease the address of the top of the stack of the app.
4. Bootloader reset the **SP(stack pointer)** to the new address of the stack of the app.
5. Bootloader reset the **PC(Program Counter)** to the address of the entry of the app.
6. The app initialization.
7. App copy the config to a global variable.
8. The app shows the config to UART.
9. The app shows messages to UART.

**Note**: It should be careful to stack overflow if the operation is about the stack. For example, to copy the config to the stack pointer of the app, it might override the current stack.

# Flash Layout

```
+------------+
|    App     |
+------------+ 0x08010000
| Bootloader |
+------------+ 0x08000000
```

# Memory Layout - Bootloader

- The **reserved** segment uses to store the config that passes to the app.
- The **stack** is allocated to 4KB.
- The size of those sections **Data and BSS** depend on global variables of source code.
- The **heap** uses the remaining memory.

```
+------------+ 0x20040000
|  Reserved  |
+------------+ 0x2003FC00
|    Stack   |
+------------+ 0x2003EC00
|    Heap    |
+------------+ ?
| Data & BSS |
+------------+ 0x20000000
```

**Note**: The size of the reserved segment is 1KB.

# Memory Layout - App

- The bootloader created the **config** segment that uses to pass config.
- The **stack** is allocated to 4KB.
- The size of those sections **Data and BSS** depend on global variables of source code.
- The **heap** uses the remaining memory.

```
+------------+ 0x20040000
|   Config   |
+------------+ ?
|    Stack   | 4KB
+------------+ ?
|    Heap    |
+------------+ ?
| Data & BSS |
+------------+ 0x20000000
```

**Note**: The real size of the config depends on the data structure boot_config.

# Reference
- [STM32-P103](https://www.olimex.com/Products/ARM/ST/STM32-P103/)
- [mini-arm-os](https://github.com/jserv/mini-arm-os)
- [How to Write a Bootloader from Scratch](https://interrupt.memfault.com/blog/how-to-write-a-bootloader-from-scratch)
