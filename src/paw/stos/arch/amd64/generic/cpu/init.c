/*
 * Copyright (c) 2026, Chloe M., et al.
 * Provided under the BSD-3 clause.
 */

#include <pexpert/pib.h>
#include <machine/msr.h>
#include <machine/trap.h>
#include <machine/idt.h>

/*
 * Initialize IDT vectors here
 */
static VOID
InitIdtVec(VOID)
{
    IdtSetGate(0x00, IDT_TRAP_GATE, 0, ISR(DivErr));
    IdtSetGate(0x01, IDT_TRAP_GATE, 0, ISR(DebugExcept));
    IdtSetGate(0x02, IDT_TRAP_GATE, 0, ISR(Nmi));
    IdtSetGate(0x03, IDT_TRAP_GATE, 0, ISR(BreakPoint));
    IdtSetGate(0x04, IDT_TRAP_GATE, 0, ISR(Overflow));
    IdtSetGate(0x05, IDT_TRAP_GATE, 0, ISR(BoundRange));
    IdtSetGate(0x06, IDT_TRAP_GATE, 0, ISR(InvalidOpcode));
    IdtSetGate(0x07, IDT_TRAP_GATE, 0, ISR(NoCoProc));
    IdtSetGate(0x08, IDT_TRAP_GATE, 0, ISR(DoubleFault));
    IdtSetGate(0x0A, IDT_TRAP_GATE, 0, ISR(InvalidTss));
    IdtSetGate(0x0B, IDT_TRAP_GATE, 0, ISR(SegNp));
    IdtSetGate(0x0C, IDT_TRAP_GATE, 0, ISR(StackSegFault));
    IdtSetGate(0x0D, IDT_TRAP_GATE, 0, ISR(Gpf));
    IdtSetGate(0x0E, IDT_TRAP_GATE, 0, ISR(PageFault));
    IdtLoad();
}

PIB *
PxGetPib(VOID)
{
    return (VOID *)MdRdmsr(IA32_GS_BASE);
}

VOID
PxPibP1Init(PIB *Result)
{
    if (Result == NULL) {
        return;
    }

    /* Initialize IDT vectors */
    InitIdtVec();

    /* Write the global processor pointer */
    MdWrmsr(IA32_GS_BASE, (UPTR)Result);
}
