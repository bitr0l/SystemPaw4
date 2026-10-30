/*
 * Copyright (c) 2026, Chloe M., et al.
 * Provided under the BSD-3 clause.
 */

    .text
    .globl NucBugCheck
NucBugCheck:
    cli         /* Disable interrupts */
    cld         /* Just in case */

    mov $1, %rax            /* Prepare the lock */
    xchg %rax, MpLock       /* Acquire the MP lock */
    or %rax, %rax           /* Are we another processor? */
    jnz LockOut             /* Yes, lock out */

    lea BugCheckStackTop(%rip), %rsp
    call BugCheckHandler
LockOut:
    hlt
    jmp LockOut

    .section .data
    .align 16
MpLock: .quad 0

    .section .bss
BugCheckStackBase:
    .skip 4096
BugCheckStackTop:
