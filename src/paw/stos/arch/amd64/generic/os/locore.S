/*
 * Copyright (c) 2026, Chloe M., et al.
 * Provided under the BSD-3 clause.
 */

    .text
    .globl _start
_start:
    cli
    cld

    xor %rbp, %rbp
    mfence
1:  cli
    hlt
    jmp 1b
