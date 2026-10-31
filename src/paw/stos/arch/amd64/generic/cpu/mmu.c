/*
 * Copyright (c) 2026, Chloe M., et al.
 * Provided under the BSD-3 clause.
 */

#include <stdef.h>
#include <pexpert/mmu.h>

VOID
PxMmuGetVas(MMU_VAS *Result)
{
    if (Result == NULL) {
        return;
    }

    ASMV(
        "mov %%cr3, %0"
        : "=r" (Result->Cr3)
        :
        : "memory"
    );
}

VOID
PxMmuSetVas(MMU_VAS *Vas)
{
    if (Vas == NULL) {
        return;
    }

    ASMV(
        "mov %0, %%cr3"
        :
        : "r" (Vas->Cr3)
        : "memory"
    );
}
