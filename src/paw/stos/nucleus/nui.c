/*
 * Copyright (c) 2026, Chloe M., et al.
 * Provided under the BSD-3 clause.
 */

#include <stdef.h>
#include <ctrace/object.h>
#include <ctrace/registry.h>
#include <pexpert/serial.h>

/* Kernel name and version parameters */
#define KNAME "Slut Technology"
#define KVER  "v0.0.1"

/* CTrace Nucleus Object */
static CTRACE_OBJECT *CTraceNuc = NULL;

/*
 * Initializes the CTRACE buffer for the nucleus
 */
static VOID
InitNucleusTrace(VOID)
{
    /* XXX: Should not fail as we are first */
    CTraceAllocFromRoot(&CTraceNuc);
    CTraceInitObject("nucleus", CTRACE_GCONS_SYNC, CTraceNuc);
}

VOID
KernelMain(VOID)
{
    /* Initialize the platform serial driver */
    PxSerialInit();

    /* Initialize the Nucleus trace buffer */
    InitNucleusTrace();

    /* Print the boot message */
    CTraceDbgWrite(CTraceNuc, "booting %s %s\n", KNAME, KVER);
}
