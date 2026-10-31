/*
 * Copyright (c) 2026, Chloe M., et al.
 * Provided under the BSD-3 clause.
 */

#ifndef _MACHINE_TRAP_H_
#define _MACHINE_TRAP_H_ 1

#include <machine/frame.h>

#define TRAP_DIVERR     0x00        /* Divide error */
#define TRAP_DBG        0x01        /* Debug exception */
#define TRAP_NMI        0x02        /* Non-maskable interrupt */
#define TRAP_BP         0x03        /* Breakpoint */
#define TRAP_OF         0x04        /* Overflow */
#define TRAP_BR         0x05        /* BOUND range exceeded */
#define TRAP_UD         0x06        /* Undefined opcode */
#define TRAP_NM         0x07        /* No math coprocessor */
#define TRAP_DF         0x08        /* Double fault */
#define TRAP_CPR        0x09        /* Reserved */
#define TRAP_TS         0x0A        /* Invalid TSS */
#define TRAP_NP         0x0B        /* Segment not present */
#define TRAP_SS         0x0C        /* Stack segment fault */
#define TRAP_GP         0x0D        /* General protection fault */
#define TRAP_PF         0x0E        /* Page fault */

/* Trap handlers */
VOID DivErr(VOID);
VOID DebugExcept(VOID);
VOID Nmi(VOID);
VOID BreakPoint(VOID);
VOID Overflow(VOID);
VOID BoundRange(VOID);
VOID InvalidOpcode(VOID);
VOID NoCoProc(VOID);
VOID DoubleFault(VOID);
VOID InvalidTss(VOID);
VOID SegNp(VOID);
VOID StackSegFault(VOID);
VOID Gpf(VOID);
VOID PageFault(VOID);

/*
 * Trap handler
 *
 * @Frame:  Trap frame
 */
VOID TrapDispatch(TRAP_FRAME *Frame);

#endif  /* !_MACHINE_TRAP_H_ */
