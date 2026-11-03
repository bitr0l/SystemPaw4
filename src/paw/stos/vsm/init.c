/*
 * Copyright (c) 2026, Chloe M., et al.
 * Provided under the BSD-3 clause.
 */

#include <vsm/core.h>
#include <vsm/pgdef.h>
#include <vsm/pgdb.h>
#include <rsm/physseg.h>
#include <pexpert/page.h>
#include <pexpert/mmu.h>
#include <ctrace/object.h>
#include <ctrace/registry.h>
#include <nucleus/bugcheck.h>

/* Number of pages to have ready for allocation */
#define N_VALLOC_PAGES 256

/* Globals */
static MMU_VAS KVas;
static TAILQ_HEAD(, _PAGE_INFO) PageInfoList;
static PAGE_DB PageDb;
static CTRACE_OBJECT *VsmMessages;
static UPTR VAllocBump = PG_ALLOC_BASE;

/*
 * Initialize the shadow page database
 */
static VOID
InitShadowDb(VOID)
{
    UPTR InfoFrameBase, FrameBase;
    USIZE InfoPerPage, Index;
    USIZE InfoIndex, InfoCount = 0;
    PAGE_INFO *InfoBall, *Info;
    ST_STATUS Status;

    InfoPerPage = PAGESIZE / sizeof(PAGE_INFO);
    for (Index = 0; Index < N_VALLOC_PAGES; ++Index) {
        if ((InfoFrameBase = RsmAllocateFrame()) == 0) {
            NucBugCheck("out of memory during vsm init\n");
        }

        /*
         * Try to fit as many information structures into a single
         * frame to minimize wastage.
         */
        InfoBall = PMA_TO_VMA(InfoFrameBase);
        for (InfoIndex = 0; InfoIndex < InfoPerPage; ++InfoIndex) {
            Info = &InfoBall[InfoIndex];

            if ((FrameBase = RsmAllocateFrame()) == 0) {
                NucBugCheck("out of memory during vsm init\n");
            }

            /* Creating a mapping to back this frame */
            Status = PxMmuMapPage(
                &KVas,
                VAllocBump,
                FrameBase,
                PROT_READ | PROT_WRITE,
                MMU_PAGESIZE_4K
            );

            if (Status != STATUS_SUCCESS) {
                NucBugCheck("out of memory during vsm init\n");
            }

            Info->VBasePtr = VAllocBump;
            Info->PBasePtr = FrameBase;
            Info->Size = PAGESIZE;
            TAILQ_INSERT_TAIL(&PageInfoList, Info, Link);

            ++InfoCount;
            VAllocBump += PAGESIZE;
        }
    }

    CTraceDbgWrite(
        VsmMessages,
        "added %d entries to shadow db\n",
        InfoCount
    );
}

/*
 * Initialize the page database
 */
static VOID
InitPageDb(VOID)
{
    PAGE_INFO *PageInfo;
    PAGE_DESCRIPTOR *PageDesc;
    ST_STATUS Status;

    TAILQ_FOREACH(PageInfo, &PageInfoList, Link) {
        PageDesc = (VOID *)PageInfo->VBasePtr;
        PageDesc->Info = PageInfo;

        Status = VsmPageDbInsert(&PageDb, PageDesc);
        if (Status != STATUS_SUCCESS) {
            NucBugCheck("failed to initialize pagedb; insert failure\n");
        }
    }

    CTraceDbgWrite(VsmMessages, "pagedb init OK\n");
}

ST_STATUS
VsmAllocatePages(USIZE PageCount, PAGE_DESCRIPTOR **Result)
{
    if (PageCount == 0 || Result == NULL) {
        return STATUS_INVALID_PARAM;
    }

    return VsmPageDbAllocate(&PageDb, PageCount, Result);
}

VOID
VsmInitMemory(VOID)
{
    MMU_VAS CurVas;
    ST_STATUS Status;

    Status = CTraceAllocFromRoot(&VsmMessages);
    if (Status != STATUS_SUCCESS) {
        NucBugCheck("failed to allocate vsm ctrace object\n");
    }

    Status = CTraceInitObject("vsm.init", CTRACE_GCONS_SYNC, VsmMessages);
    if (Status != STATUS_SUCCESS) {
        NucBugCheck("failed to initialize vsm ctrace object\n");
    }

    /* Create a forked address space */
    PxMmuGetVas(&CurVas);
    PxMmuForkVas(&CurVas, &KVas);
    PxMmuSetVas(&KVas);
    CTraceDbgWrite(VsmMessages, "kvas switch OK\n");

    /* Initialize page databases */
    TAILQ_INIT(&PageInfoList);
    VsmPageDbInit(&PageDb);
    InitShadowDb();
    InitPageDb();
}
