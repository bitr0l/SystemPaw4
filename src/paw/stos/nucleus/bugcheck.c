/*
 * Copyright (c) 2026, Chloe M., et al.
 * Provided under the BSD-3 clause.
 */

#include <sys/stdarg.h>
#include <aux/fmt.h>
#include <nucleus/bugcheck.h>

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
    Print("... Something has gone wrong during system operation.\n");
    Print("... The kernel kitty pilot has halted the machine to prevent damage of data.\n");
}
