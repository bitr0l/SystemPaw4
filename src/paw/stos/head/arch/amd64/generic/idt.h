/*
 * Copyright (c) 2026, Chloe M., et al.
 * Provided under the BSD-3 clause.
 */

#ifndef _MACHINE_IDT_H_
#define _MACHINE_IDT_H_ 1

#include <stdef.h>

/* IDT gate kinds */
#define IDT_INT_GATE    0x8E
#define IDT_TRAP_GATE   0x8F
#define IDT_USER_GATE   0xEE

/*
 * Represents a 64-bit interrupt gate descriptor
 *
 * Refer to the "Exception And Interrupt Handling In 64-bit Mode"
 * section of the Intel SDM.
 */
typedef struct {
    USHORT OffsetLow16;
    USHORT CodeSeg;
    UQUAD Ist   : 3;
    UQUAD Zero  : 5;
    UQUAD Type  : 4;
    UQUAD Zero1 : 1;
    UQUAD Dpl   : 2;
    UQUAD P     : 1;
    USHORT OffsetMid16;
    ULONG OffsetHigh32;
    ULONG Reserved;
} IDT_GATE;

/*
 * In-memory representation of the IDT register
 *
 * Refer to the "Interrupt Descriptor Table (IDT)" section
 * in the Intel SDM.
 */
typedef struct PACKED {
    USHORT Limit;
    UPTR Offset;
} IDTR;

/*
 * Set an interrupt gate descriptor
 *
 * @Vector:  Interrupt vector of entry to set
 * @Type:    Interrupt gate type
 * @Ist:     Interrupt stack table index
 * @IsrBase: Interrupt service routine base
 */
VOID IdtSetGate(UCHAR Vector, UCHAR Type, UCHAR Ist, UPTR IsrBase);

/*
 * Load the interrupt descriptor table
 */
VOID IdtLoad(VOID);

#endif  /* !_MACHINE_IDT_H_ */
