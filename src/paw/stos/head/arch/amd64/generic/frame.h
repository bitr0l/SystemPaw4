/*
 * Copyright (c) 2026, Chloe M., et al.
 * Provided under the BSD-3 clause.
 */

#ifndef _MACHINE_FRAME_H_
#define _MACHINE_FRAME_H_ 1

#include <stdef.h>

/*
 * Represents a trap frame which is an in-memory snapshot of
 * the processor state.
 */
typedef struct PACKED {
    UQUAD Vector;
    UQUAD Rax;
    UQUAD Rbx;
    UQUAD Rcx;
    UQUAD Rdx;
    UQUAD Rsi;
    UQUAD Rdi;
    UQUAD Rbp;
    UQUAD R8;
    UQUAD R9;
    UQUAD R10;
    UQUAD R11;
    UQUAD R12;
    UQUAD R13;
    UQUAD R14;
    UQUAD R15;

    /* Pushed by hardware */
    UQUAD ErrorCode;
    UQUAD Rip;
    UQUAD CodeSeg;
    UQUAD RFlags;
    UQUAD Rsp;
    UQUAD StackSeg;
} TRAP_FRAME;

#endif  /* !_MACHINE_FRAME_H_ */
