/*
 * Copyright (c) 2026, Chloe M., et al.
 * Provided under the BSD-3 clause.
 */

#include <rsm/physseg.h>
#include <ctrace/registry.h>
#include <ctrace/object.h>
#include <nucleus/bal.h>
#include <nucleus/bugcheck.h>

/* Use to convert type constants to strings */
#define MEM_TYPE(TYPE)          \
    ((TYPE) < NELEM(TypeTab))   \
        ? TypeTab[(TYPE)]       \
        : "invalid"

/* Globals */
static CTRACE_OBJECT *CTracePmm = NULL;

/*
 * Memory type constant to human readable
 * string table.
 */
static const char *TypeTab[] = {
    [MEMORY_USABLE]         = "usable",
    [MEMORY_RESERVED]       = "reserved",
    [MEMORY_ACPI_RECLAIM]   = "acpi reclaimable",
    [MEMORY_ACPI_NVS]       = "acpi nvs",
    [MEMORY_BAD]            = "bad*",
    [MEMORY_BOOTLOADER]     = "bootloader",
    [MEMORY_KERNEL]         = "stoskrnl.sys",
    [MEMORY_FRAMEBUFFER]    = "framebuffer",
    [MEMORY_ACPI_TABLES]    = "acpi tables"
};

/*
 * Initialize component tracing for the physical segment
 * manager.
 */
static VOID
PhysMemInitCTrace(VOID)
{
    ST_STATUS Status;

    Status = CTraceAllocFromRoot(&CTracePmm);
    if (Status != STATUS_SUCCESS) {
        NucBugCheck("failed to allocate CTracePmm\n");
    }

    Status = CTraceInitObject("physseg", CTRACE_GCONS_SYNC, CTracePmm);
    if (Status != STATUS_SUCCESS) {
        NucBugCheck("failed to initialize CTracePmm\n");
    }
}

/*
 * Probe physical memory
 */
static VOID
PhysMemProbe(VOID)
{
    BAL_HANDLE BalHandle;
    MEMMAP_ENTRY Entry;
    ST_STATUS Status;
    UPTR Base, End;
    USIZE Index;

    BalGetHandle(&BalHandle);
    if (BalHandle.MemEntryIdx == NULL) {
        NucBugCheck("no associated MemEntryIdx callback in BAL\n");
    }

    for (Index = 0;; ++Index) {
        Status = BalHandle.MemEntryIdx(Index, &Entry);
        if (Status != STATUS_SUCCESS) {
            break;
        }

        Base = Entry.Base;
        End = Base + Entry.Length;

        /* Log this entry */
        CTraceDbgWrite(
            CTracePmm,
            "[%p - %p] : %s\n",
            Base,
            End,
            MEM_TYPE(Entry.Type)
        );
    }

    CTraceDbgWrite(CTracePmm, "detected %d entries\n", Index);
}

VOID
RsmPhysMemInit(VOID)
{
    /* Initialize CTrace for this component */
    PhysMemInitCTrace();

    /* Begin scanning physical memory */
    CTraceDbgWrite(CTracePmm, "sniffing out physical memory...\n");
    PhysMemProbe();
}
