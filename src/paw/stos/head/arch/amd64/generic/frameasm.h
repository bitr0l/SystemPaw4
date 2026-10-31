/*
 * Copyright (c) 2026, Chloe M., et al.
 * Provided under the BSD-3 clause.
 */

#ifndef _MACHINE_FRAMEASM_H_
#define _MACHINE_FRAMEASM_H_ 1

/*
 * Push the trapframe
 */
#define FRAME_PUSH(VECTOR)       \
    pushq %r15                  ;\
    pushq %r14                  ;\
    pushq %r13                  ;\
    pushq %r12                  ;\
    pushq %r11                  ;\
    pushq %r10                  ;\
    pushq %r9                   ;\
    pushq %r8                   ;\
    pushq %rbp                  ;\
    pushq %rdi                  ;\
    pushq %rsi                  ;\
    pushq %rdx                  ;\
    pushq %rcx                  ;\
    pushq %rbx                  ;\
    pushq %rax                  ;\
    pushq $VECTOR               ;\

/*
 * Pop the trap frame
 */
#define FRAME_POP()              ;\
    addq %8, %rsp                ;\
    popq %rax                    ;\
    popq %rbx                    ;\
    popq %rcx                    ;\
    popq %rdx                    ;\
    popq %rsi                    ;\
    popq %rdi                    ;\
    popq %rbp                    ;\
    popq %r8                     ;\
    popq %r9                     ;\
    popq %r10                    ;\
    popq %r11                    ;\
    popq %r12                    ;\
    popq %r13                    ;\
    popq %r14                    ;\
    popq %r15                    ;\

/*
 * Interrupt entry when there is no error code
 */
#define INTR_ENTRY(NAME, VECTOR)    \
    NAME:                           \
        testq $3, 8(%rsp)          ;\
        jz 1f                      ;\
        lfence                     ;\
        swapgs                     ;\
        pushq $0                   ;\
    1:  FRAME_PUSH(VECTOR)

/*
 * Interrupt entry for when there is an error code
 */
#define INTR_ENTRY_EC(NAME, VECTOR)   ;\
    NAME:                             ;\
        testq $3, 16(%rsp)            ;\
        jz 1f                         ;\
        lfence                        ;\
        swapgs                        ;\
    1: FRAME_PUSH(VECTOR)

#endif  /* !_MACHINE_FRAMEASM_H_ */
