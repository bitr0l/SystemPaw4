/*
 * Copyright (c) 2026, Chloe M., et al.
 * Provided under the BSD-3 clause.
 */

#include <machine/frameasm.h>

    .text
    .extern TrapDispatch
    .align 8
    .globl DivErr
INTR_ENTRY(DivErr, 0x00)
    mov %rsp, %rdi
    call TrapDispatch
1:  cli
    hlt
    jmp 1b

    .globl DebugExcept
INTR_ENTRY(DebugExcept, 0x01)
    mov %rsp, %rdi
    call TrapDispatch
1:  cli
    hlt
    jmp 1b

    .globl Nmi
INTR_ENTRY(Nmi, 0x02)
    mov %rsp, %rdi
    call TrapDispatch
1:  cli
    hlt
    jmp 1b

    .globl BreakPoint
INTR_ENTRY(BreakPoint, 0x03)
    mov %rsp, %rdi
    call TrapDispatch
1:  cli
    hlt
    jmp 1b

    .globl Overflow
INTR_ENTRY(Overflow, 0x04)
    mov %rsp, %rdi
    call TrapDispatch
1:  cli
    hlt
    jmp 1b

    .globl BoundRange
INTR_ENTRY(BoundRange, 0x05)
    mov %rsp, %rdi
    call TrapDispatch
1:  cli
    hlt
    jmp 1b

    .globl InvalidOpcode
INTR_ENTRY(InvalidOpcode, 0x06)
    mov %rsp, %rdi
    call TrapDispatch
1:  cli
    hlt
    jmp 1b

    .globl NoCoProc
INTR_ENTRY(NoCoProc, 0x07)
    mov %rsp, %rdi
    call TrapDispatch
1:  cli
    hlt
    jmp 1b

    .globl DoubleFault
INTR_ENTRY_EC(DoubleFault, 0x08)
    mov %rsp, %rdi
    call TrapDispatch
1:  cli
    hlt
    jmp 1b

    .globl InvalidTss
INTR_ENTRY_EC(InvalidTss, 0x0A)
    mov %rsp, %rdi
    call TrapDispatch
1:  cli
    hlt
    jmp 1b

    .globl SegNp
INTR_ENTRY_EC(SegNp, 0x0B)
    mov %rsp, %rdi
    call TrapDispatch
1:  cli
    hlt
    jmp 1b

    .globl StackSegFault
INTR_ENTRY_EC(StackSegFault, 0x0C)
    mov %rsp, %rdi
    call TrapDispatch
1:  cli
    hlt
    jmp 1b

    .globl Gpf
INTR_ENTRY_EC(Gpf, 0x0D)
    mov %rsp, %rdi
    call TrapDispatch
1:  cli
    hlt
    jmp 1b

    .globl PageFault
INTR_ENTRY_EC(PageFault, 0x0E)
    mov %rsp, %rdi
    call TrapDispatch
1:  cli
    hlt
    jmp 1b
    hlt
