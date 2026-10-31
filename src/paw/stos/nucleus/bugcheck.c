/*
 * Copyright (c) 2026, Chloe M., et al.
 * Provided under the BSD-3 clause.
 */

#include <sys/stdarg.h>
#include <aux/fmt.h>
#include <pexpert/pib.h>
#include <nucleus/bugcheck.h>

static PIB *ThisProcessor = NULL;
static CHAR MessageBuffer[256];
static va_list Ap;

VOID
BugCheckHandler(const CHAR *Fmt, ...)
{
    if (Fmt == NULL) {
        return;
    }

    VPrintFmt(MessageBuffer, sizeof(MessageBuffer), Fmt, Ap);
    Print("\033[31;40m** BUGCHECK: %s", MessageBuffer);
    Print("... Ah, fuck!~ I have been railed @.@\n");
    Print("... The kernel kitty pilot has halted the machine to prevent any damage of data.\n");

    /* Attempt to get processor information */
    if ((ThisProcessor = PxGetPib()) == NULL) {
        Print("warning: no processor information available\n");
        return;
    }

    Print("... On processing element %d\n", ThisProcessor->LogicalId);
}
