/*
 * Copyright (c) 2026, Chloe M., et al.
 * Provided under the BSD-3 clause.
 */

#include <sys/queue.h>
#include <rsm/physseg.h>
#include <vsm/pgdef.h>
#include <ctrace/registry.h>
#include <ctrace/object.h>
#include <nucleus/bal.h>
#include <nucleus/bugcheck.h>
#include <pexpert/page.h>

/* Use to convert type constants to strings */
#define MEM_TYPE(TYPE)          \
    ((TYPE) < NELEM(TypeTab))   \
        ? TypeTab[(TYPE)]       \
        : "invalid"

/*
 * Represents a page  frame descriptor
 *
 * @Link:  TAILQ link
 */
typedef struct _PFD {
    TAILQ_ENTRY(_PFD) Link;
} PFD;

/*
 * Represents a page frame descriptor list
 *
 * @Head:       Head of the PFD list
 * @NrEntries:  Total number of entries
 */
typedef struct {
    TAILQ_HEAD(, _PFD) Head;
    USIZE NrEntries;
} PFD_LIST;

/* Globals */
static CTRACE_OBJECT *CTracePmm = NULL;
static PFD_LIST AvlList;

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
 * Insert a page frame descriptor list into a page frame
 * descriptor.
 *
 * @List:  Page frame descriptor list
 * @Pfd:   Page frame to push
 *
 * TODO: Add locking
 */
static VOID
PfdListInsert(PFD_LIST *List, PFD *Pfd)
{
    if (List == NULL || Pfd == NULL) {
        return;
    }

    TAILQ_INSERT_TAIL(&List->Head, Pfd, Link);
    ++List->NrEntries;
}

/*
 * Pop a page frame descriptor from a page frame descriptor list
 *
 * @List:  Page frame descriptor list to pop from
 */
static PFD *
PfdListPop(PFD_LIST *List)
{
    PFD *Pfd;

    if (List == NULL) {
        return NULL;
    }

    if ((Pfd = TAILQ_FIRST(&List->Head)) == NULL) {
        return NULL;
    }

    TAILQ_REMOVE(&List->Head, Pfd, Link);
    --List->NrEntries;
    return Pfd;
}

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
    PFD *PfdBase, *Pfd;
    USIZE Index, Off;

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

        /* Usable entries from this point on */
        if (Entry.Type != MEMORY_USABLE) {
            continue;
        }

        PfdBase = PMA_TO_VMA(Entry.Base);
        for (Off = 0; Off < Entry.Length; Off += PAGESIZE) {
            Pfd = PTR_OFFSET(PfdBase, Off);
            PfdListInsert(&AvlList, Pfd);
        }
    }

    CTraceDbgWrite(CTracePmm, "detected %d entries\n", Index);
}

UPTR
RsmAllocateFrame(VOID)
{
    PFD *Pfd;

    /* Acquire a page frame descriptor */
    if ((Pfd = PfdListPop(&AvlList)) == NULL) {
        return 0;
    }

    return VMA_TO_PMA(Pfd);
}

VOID
RsmReclaimFrame(UPTR BasePtr)
{
    PFD *Pfd;

    if (BasePtr == 0) {
        return;
    }

    BasePtr = ALIGN_DOWN(BasePtr, PAGESIZE);
    Pfd = PMA_TO_VMA(BasePtr);
    PfdListInsert(&AvlList, Pfd);
}

VOID
RsmPhysMemInit(VOID)
{
    /* Initialize freelists */
    TAILQ_INIT(&AvlList.Head);

    /* Initialize CTrace for this component */
    PhysMemInitCTrace();

    /* Begin scanning physical memory */
    CTraceDbgWrite(CTracePmm, "sniffing out physical memory...\n");
    PhysMemProbe();
}
