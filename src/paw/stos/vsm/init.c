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
#include <nucleus/bugcheck.h>

/* Number of pages to have ready for allocation */
#define N_VALLOC_PAGES 256

/* Globals */
static MMU_VAS KVas;
static TAILQ_HEAD(, _PAGE_INFO) PageInfoList;

/*
 * Initialize the shadow page database
 */
static VOID
InitShadowDb(VOID)
{
    UPTR InfoFrameBase, FrameBase;
    USIZE InfoPerPage, Index;
    USIZE InfoIndex;
    PAGE_INFO *InfoBall, *Info;

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

            Info->BasePtr = FrameBase;
            Info->EndPtr = FrameBase + PAGESIZE;
            TAILQ_INSERT_TAIL(&PageInfoList, Info, Link);
        }
    }
}

VOID
VsmInitMemory(VOID)
{
    MMU_VAS CurVas;

    /* Create a forked address space */
    PxMmuGetVas(&CurVas);
    PxMmuForkVas(&CurVas, &KVas);
    PxMmuSetVas(&KVas);

    /* Initialize page databases */
    TAILQ_INIT(&PageInfoList);
    InitShadowDb();

    /* TODO: Populate pagedb from page info structures */
}
