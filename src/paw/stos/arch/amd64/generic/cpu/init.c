/*
 * Copyright (c) 2026, Chloe M., et al.
 * Provided under the BSD-3 clause.
 */

#include <pexpert/pib.h>
#include <aux/fmt.h>
#include <aux/string.h>
#include <ctrace/registry.h>
#include <nucleus/bugcheck.h>
#include <machine/msr.h>
#include <machine/trap.h>
#include <machine/idt.h>
#include <machine/cpuid.h>

/* Vendor strings */
#define VENDOR_INTEL   "GenuineIntel"
#define VENDOR_INTEL1  "GenuineIotel"   /* Single bit error quirk */
#define VENDOR_UMC     "UMC UMC UMC "
#define VENDOR_AMD     "AuthenticAMD"

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

/*
 * Initialize the per core CTrace log store
 */
static VOID
InitLogStore(PIB *Pib)
{
    CHAR NameBuf[128];
    ST_STATUS Status;
    USHORT CTraceFlags = 0;

    if (Pib == NULL) {
        return;
    }

    /* Allocate a new CTrace object for this processor */
    Status = CTraceAllocFromRoot(&Pib->LogStore);
    if (Status != STATUS_SUCCESS) {
        NucBugCheck(
            "failed to allocate log store of core %d\n",
            Pib->LogicalId
        );
    }

    /*
     * Only the bootstrap processor is able to delegate to the root
     * console. The BSP always has a logical ID of zero.
     */
    if (Pib->LogicalId == 0) {
        CTraceFlags |= CTRACE_GCONS_SYNC;
    }

    /* Initialize the log store */
    PrintFmt(NameBuf, sizeof(NameBuf), "pib%d", Pib->LogicalId);
    Status = CTraceInitObject(NameBuf, CTraceFlags, Pib->LogStore);
    if (Status != STATUS_SUCCESS) {
        NucBugCheck(
            "failed to initialize log store of core %d\n",
            Pib->LogicalId
        );
    }
}

/*
 * Obtain the processor vendor
 *
 * @Pib:  Processor information block
 */
static VOID
GetProcessorVendor(PIB *Pib)
{
    ULONG Ebx, Edx, Ecx, Unused;
    CHAR VendorString[13];
    MPB *Mpb;

    if (Pib == NULL) {
        return;
    }

    Mpb = &Pib->Mpb;
    CPUID(0x00, Unused, Ebx, Ecx, Edx);

    /* DWORD 0 */
    VendorString[0] = Ebx & 0xFF;
    VendorString[1] = (Ebx >> 8) & 0xFF;
    VendorString[2] = (Ebx >> 16) & 0xFF;
    VendorString[3] = (Ebx >> 24) & 0xFF;

    /* DWORD 1 */
    VendorString[4] = Edx & 0xFF;
    VendorString[5] = (Edx >> 8) & 0xFF;
    VendorString[6] = (Edx >> 16) & 0xFF;
    VendorString[7] = (Edx >> 24) & 0xFF;

    /* DWORD 2 */
    VendorString[8] = Ecx & 0xFF;
    VendorString[9] = (Ecx >> 8) & 0xFF;
    VendorString[10] = (Ecx >> 16) & 0xFF;
    VendorString[11] = (Ecx >> 24) & 0xFF;
    VendorString[12] = '\0';

    /* Match which vendor */
    if (StrEq(VendorString, VENDOR_INTEL)) {
        Mpb->Vendor = CPU_VENDOR_INTEL;
    } else if (StrEq(VendorString, VENDOR_INTEL1)) {
        Mpb->Vendor = CPU_VENDOR_INTEL;
    } else if (StrEq(VendorString, VENDOR_UMC)) {
        Mpb->Vendor = CPU_VENDOR_UMC;
    } else if (StrEq(VendorString, VENDOR_AMD)) {
        Mpb->Vendor = CPU_VENDOR_AMD;
    } else {
        Mpb->Vendor = CPU_VENDOR_UNKNOWN;
    }

    CTraceDbgWrite(Pib->LogStore, "vendor : %s\n", VendorString);
}

/*
 * Obtain processor features
 *
 * @Pib: Processor information block
 */
static VOID
GetProcessorFeatures(PIB *Pib)
{
    ULONG Eax, Unused;
    MPB *Mpb;

    if (Pib == NULL) {
        return;
    }

    Mpb = &Pib->Mpb;
    CPUID(0x01, Eax, Unused, Unused, Unused);

    /* Model number and family*/
    Mpb->Model = (Eax >> 4) & 0xF;
    Mpb->Family = (Eax >> 8) & 0xF;
    Mpb->ExtModel = (Eax >> 16) & 0xF;
}

/*
 * Obtain machine specific processor information
 *
 * @Pib: Processor information block
 */
static VOID
GetProcessorInfo(PIB *Pib)
{
    if (Pib == NULL) {
        return;
    }

    /* Get the vendor ID */
    GetProcessorVendor(Pib);

    /* Get processor features */
    GetProcessorFeatures(Pib);
}

PIB *
PxGetPib(VOID)
{
    return (VOID *)MdRdmsr(IA32_GS_BASE);
}

VOID
PxPibP1Init(PIB *Result)
{
    MPB *Mpb;

    if (Result == NULL) {
        return;
    }

    Mpb = &Result->Mpb;

    /* Initialize IDT vectors */
    InitIdtVec();

    /* Write the global processor pointer */
    MdWrmsr(IA32_GS_BASE, (UPTR)Result);

    /* Initialize the per-core log store */
    InitLogStore(Result);

    /* Get processor information */
    GetProcessorInfo(Result);

    /* Some information logging */
    CTraceDbgWrite(Result->LogStore, "model : %Xh\n", Mpb->Model);
    CTraceDbgWrite(Result->LogStore, "family : %Xh\n", Mpb->Family);
    CTraceDbgWrite(Result->LogStore, "phase 1 init OK\n");
}
