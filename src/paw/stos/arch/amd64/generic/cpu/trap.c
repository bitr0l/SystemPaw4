/*
 * Copyright (c) 2026, Chloe M., et al.
 * Provided under the BSD-3 clause.
 */

#include <machine/trap.h>
#include <nucleus/bugcheck.h>
#include <aux/fmt.h>
#include <stdef.h>

#define TRAPSTR(VEC)            \
    ((VEC) >= NELEM(TrapTab))   \
        ? "???"                 \
        : TrapTab[(VEC)]

/*
 * Interrupt vector to trap string
 */
static const CHAR *TrapTab[] = {
    [TRAP_DIVERR] = "divison error",
    [TRAP_DBG]    = "debug exception",
    [TRAP_NMI]    = "non-maskable interrupt",
    [TRAP_BP]     = "breakpoint",
    [TRAP_OF]     = "overflow",
    [TRAP_BR]     = "BOUND range exceeded",
    [TRAP_UD]     = "undefined opcode",
    [TRAP_NM]     = "no math co-processor",
    [TRAP_DF]     = "double fault",
    [TRAP_CPR]    = "reserved exception [0x09]",
    [TRAP_TS]     = "invalid TSS",
    [TRAP_NP]     = "segment not present",
    [TRAP_SS]     = "stack segment fault",
    [TRAP_GP]     = "general protection fault",
    [TRAP_PF]     = "page fault"
};

VOID
TrapDispatch(TRAP_FRAME *Frame)
{
    if (Frame == NULL) {
        NucBugCheck("TrapDispatch frame is NULL\n");
    }

    Print("got trap: %s\n", TRAPSTR(Frame->Vector));
    NucBugCheck("fatal trap received\n");
}
