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
3. Bootloader shows some messages to UART.
4. Bootloader reset the **SP(stack pointer)** to the address of the stack of the app.
5. Bootloader reset the **PC(Program Counter)** to the address of the entry of the app.
6. The app initialization.
7. App shows some messages to UART.

# Flash Layout

```
+------------+
|    App     |
+------------+ 0x08010000
| Bootloader |
+------------+ 0x08000000
```

# Memory Layout

- The **stack** is allocated to 4KB.
- The size of those sections **Data and BSS** depend on global variables of source code.
- The **heap** uses the remaining memory.

```
+------------+ 0x20040000
|    Stack   |
+------------+ 0x2003F000
|    Heap    |
+------------+ ?
| Data & BSS |
+------------+ 0x20000000
```

# Reference
- [STM32-P103](https://www.olimex.com/Products/ARM/ST/STM32-P103/)
- [mini-arm-os](https://github.com/jserv/mini-arm-os)
- [How to Write a Bootloader from Scratch](https://interrupt.memfault.com/blog/how-to-write-a-bootloader-from-scratch)
