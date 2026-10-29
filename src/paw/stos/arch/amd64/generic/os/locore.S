/*
 * Copyright (c) 2026, Chloe M., et al.
 * Provided under the BSD-3 clause.
 */

    .text
    .globl _start
    .extern KernelMain
_start:
    cli
    cld

    xor %rbp, %rbp
    call KernelMain

    mfence
1:  cli
    hlt
    jmp 1b
