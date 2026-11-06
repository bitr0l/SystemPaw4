/*
 * Copyright (c) 2026, Chloe M., et al.
 * Provided under the BSD-3 clause.
 */

#include <pexpert/prim.h>
#include <nucleus/cpulock.h>

VOID
NucCpuLockAcq(CPU_LOCK *Lock, BOOLEAN IntMut)
{
    BOOLEAN IntEn = FALSE;

    if (Lock == NULL) {
        return;
    }

    if (IntMut) {
        IntEn = PxCpuIntEn();
        PxCpuIntMask();
    }

    while (PxCpuAswap(&Lock->Lock, 1)) {
        PxCpuSpinWait();
    }

    if (IntMut && IntEn) {
        PxCpuIntUnmask();
    }
}

VOID
NucCpuLockRel(CPU_LOCK *Lock)
{
    if (Lock == NULL) {
        return;
    }

    PxCpuAswap(&Lock->Lock, 0);
}
