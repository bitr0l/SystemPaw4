/*
 * Copyright (c) 2026, Chloe M., et al.
 * Provided under the BSD-3 clause.
 */

    .text
    .extern MdTrapDispatch
    .align 8
    .globl DivErr
DivErr:
1:  cli
    hlt
    jmp 1b

    .globl DebugExcept
DebugExcept:
1:  cli
    hlt
    jmp 1b

    .globl Nmi
Nmi:
1:  cli
    hlt
    jmp 1b

    .globl BreakPoint
BreakPoint:
1:  cli
    hlt
    jmp 1b

    .globl Overflow
Overflow:
1:  cli
    hlt
    jmp 1b

    .globl BoundRange
BoundRange:
1:  cli
    hlt
    jmp 1b

    .globl InvalidOpcode
InvalidOpcode:
1:  cli
    hlt
    jmp 1b

    .globl NoCoProc
NoCoProc:
1:  cli
    hlt
    jmp 1b

    .globl DoubleFault
DoubleFault:
1:  cli
    hlt
    jmp 1b

    .globl InvalidTss
InvalidTss:
1:  cli
    hlt
    jmp 1b

    .globl SegNp
SegNp:
1:  cli
    hlt
    jmp 1b

    .globl StackSegFault
StackSegFault:
1:  cli
    hlt
    jmp 1b

    .globl Gpf
Gpf:
1:  cli
    hlt
    jmp 1b

    .globl PageFault
PageFault:
1:  cli
    hlt
    jmp 1b
    hlt
