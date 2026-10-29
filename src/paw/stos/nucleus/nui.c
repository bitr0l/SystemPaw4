/*
 * Copyright (c) 2026, Chloe M., et al.
 * Provided under the BSD-3 clause.
 */

#include <stdef.h>
#include <pexpert/serial.h>

VOID
KernelMain(VOID)
{
    /* Initialize the platform serial driver */
    PxSerialInit();
}
