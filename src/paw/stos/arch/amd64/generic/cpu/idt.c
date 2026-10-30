/*
 * Copyright (c) 2026, Chloe M., et al.
 * Provided under the BSD-3 clause.
 */

#include <machine/idt.h>
#include <machine/gdt.h>

/*
 * The interrupt descriptor table and its IDTR in-memory
 * representation.
 *
 * XXX: The IDT is aligned on an 8-byte boundary to improve performance
 *      of cache line fills.
 */
ALIGN(8) static IDT_GATE Idt[256];
static IDTR Idtr = {
    .Limit = sizeof(Idt) - 1,
    .Offset = (UPTR)Idt
};

VOID
IdtSetGate(UCHAR Vector, UCHAR Type, UCHAR Ist, UPTR IsrBase)
{
    IDT_GATE *Gate;

    Gate = &Idt[Vector];
    Gate->Zero = 0;
    Gate->Zero1 = 0;
    Gate->Reserved = 0;
    Gate->P = 1;
    Gate->Dpl = (Type == IDT_USER_GATE) ? 3 : 0;
    Gate->Type = Type;
    Gate->Ist = Ist;
    Gate->CodeSeg = GDT_KCODE;
    Gate->OffsetLow16 = IsrBase & 0xFFFF;
    Gate->OffsetMid16 = (IsrBase >> 16) & 0xFFFF;
    Gate->OffsetHigh32 = (IsrBase >> 32) & 0xFFFFFFFF;
}

VOID
IdtLoad(VOID)
{
    ASMV(
        "lidt %0"
        :
        : "m" (Idtr)
        : "memory"
    );
}
