/*
 * Copyright (c) 2026, Chloe M., et al.
 * Provided under the BSD-3 clause.
 */

#include <vsm/core.h>
#include <pexpert/mmu.h>

/* Globals */
static MMU_VAS KVas;

VOID
VsmInitMemory(VOID)
{
    MMU_VAS CurVas;

    /* Create a forked address space */
    PxMmuGetVas(&CurVas);
    PxMmuForkVas(&CurVas, &KVas);
    PxMmuSetVas(&KVas);
}
