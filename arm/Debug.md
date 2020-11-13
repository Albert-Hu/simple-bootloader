# Use ELF to Debug

We can check the memory layout by analyzing the ELF.



## Dump the Section Headers

Use the following command:

```shell
arm-none-eabi-objdump -h [file]
```

**[file]** is the ELF you want to analyze.



It would look like:

```
Sections:
Idx Name          Size      VMA       LMA       File off  Algn
  0 .text         00009df8  08000000  08000000  00008000  2**3
                  CONTENTS, ALLOC, LOAD, READONLY, CODE
  1 .ARM.exidx    00000008  08009df8  08009df8  00011df8  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  2 .data         00000590  20000000  08009e00  00018000  2**2
                  CONTENTS, ALLOC, LOAD, DATA
  3 .bss          00000058  20000590  0800a390  00018590  2**2
                  ALLOC
  4 .debug_info   00000754  00000000  00000000  00018590  2**0
                  CONTENTS, READONLY, DEBUGGING
  5 .debug_abbrev 000002ba  00000000  00000000  00018ce4  2**0
                  CONTENTS, READONLY, DEBUGGING
  6 .debug_aranges 00000060  00000000  00000000  00018f9e  2**0
                  CONTENTS, READONLY, DEBUGGING
  7 .debug_line   00000261  00000000  00000000  00018ffe  2**0
                  CONTENTS, READONLY, DEBUGGING
  8 .debug_str    0000038e  00000000  00000000  0001925f  2**0
                  CONTENTS, READONLY, DEBUGGING
  9 .comment      00000030  00000000  00000000  000195ed  2**0
                  CONTENTS, READONLY
 10 .ARM.attributes 00000031  00000000  00000000  0001961d  2**0
                  CONTENTS, READONLY
 11 .debug_frame  00001128  00000000  00000000  00019650  2**2
                  CONTENTS, READONLY, DEBUGGING
```

The LMA mapped to the Flash, and the VMA mapped to the SRAM.

**LMA**: Load Memory Address.
**VMA**: Virtual Memory Address.



## Disassemble the ELF

Use the following command:

```shell
arm-none-eabi-objdump -D [file]
```

**[file]** is the ELF you want to analyze.



It would look like:

```
Disassembly of section .text:

08000000 <isr_vectors>:
 8000000:       20004ffc        strdcs  r4, [r0], -ip
 8000004:       080001dd        stmdaeq r0, {r0, r2, r3, r4, r6, r7, r8}
 8000008:       0800023d        stmdaeq r0, {r0, r2, r3, r4, r5, r9}
 800000c:       08000245        stmdaeq r0, {r0, r2, r6, r9}

08000010 <_data_section>:
 8000010:       08009e00        stmdaeq r0, {r9, sl, fp, ip, pc}
 8000014:       20000000        andcs   r0, r0, r0
 8000018:       00000590        muleq   r0, r0, r5

0800001c <_bss_section>:
 800001c:       20000590        mulcs   r0, r0, r5
 8000020:       00000058        andeq   r0, r0, r8, asr r0

08000024 <load_app>:
 8000024:       b480            push    {r7}
 8000026:       b083            sub     sp, #12
 8000028:       af00            add     r7, sp, #0
 800002a:       6078            str     r0, [r7, #4]
 800002c:       6039            str     r1, [r7, #0]
 800002e:       f380 8808       msr     MSP, r0
 8000032:       4708            bx      r1
 8000034:       370c            adds    r7, #12
 8000036:       46bd            mov     sp, r7
 8000038:       f85d 7b04       ldr.w   r7, [sp], #4
 800003c:       4770            bx      lr
 800003e:       bf00            nop

08000040 <main>:
 8000040:       b590            push    {r4, r7, lr}
 8000042:       b083            sub     sp, #12
 8000044:       af02            add     r7, sp, #8
 8000046:       f241 0318       movw    r3, #4120       ; 0x1018
 800004a:       f2c4 0302       movt    r3, #16386      ; 0x4002
 800004e:       f241 0218       movw    r2, #4120       ; 0x1018
 8000052:       f2c4 0202       movt    r2, #16386      ; 0x4002
 8000056:       6812            ldr     r2, [r2, #0]
 8000058:       f042 0205       orr.w   r2, r2, #5
 800005c:       601a            str     r2, [r3, #0]
 800005e:       f241 031c       movw    r3, #4124       ; 0x101c
 --- Read More ---
```



# Use QEMU and GDB

We use QEMU to run a GDB server, then open a GDB to connect to it.



Run the QEMU first:

```shell
qemu-system-arm -M stm32-p103 -nographic -S -gdb tcp::[port number] -kernel [file]
```

**[file]** is the ELF you want to debug.

**[port number]** is the port number of TCP.

**-S** means freeze CPU at startup.



Run the GDB:

```shell
arm-none-eabi-gdb [file]
```

**[file]** is the ELF you want to debug.



After open the GDB successfully, you will enter the GDB console.

Connect to QEMU:

```
target remote :[port number]
```

**[port number]** is the port number of TCP.



Before you debug, load the ELF by the command:

```
load
```



## Set Breakpoint

You can set a breakpoint to suspend the running program by the command:

```
break [source file]:[line number]
```

Or use the short command:

```
br [source file]:[line number]
```

**[source file]** is the source code file that you use to compilation.

**[line number]** is the line number at the source code you want to break out.



After all the breakpoints set, run the command to start:

```
continue
```

Or use the short command:

```
c
```



## Dump CPU Registers

You can dump the CPU registers to check somethings by the command:

```
info register
```

It would look like:

```
r0             0x0	0
r1             0x0	0
r2             0x0	0
r3             0x0	0
r4             0x0	0
r5             0x0	0
r6             0x0	0
r7             0x0	0
r8             0x0	0
r9             0x0	0
r10            0x0	0
r11            0x0	0
r12            0x0	0
sp             0x0	0x0
lr             0x0	0
pc             0x80001dc	0x80001dc <reset_handler>
cpsr           0x40000173	1073742195
```



## Dump The Stack

You can dump the stack to check somethings by the command:

```
info stack
```

It would look like:

```
#0  reset_handler () at startup.c:49
```



## Dump Memory

You can dump a region of memory to a file by the command:

```
dump memory [output file] [start address] [end address]
```

**[output file]** is the file stored dumped memory.

**[start address]** is the address of memory to start dumping.

**[end address]** is the address of memory to end dumping.

