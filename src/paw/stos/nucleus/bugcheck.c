/*
 * Copyright (c) 2026, Chloe M., et al.
 * Provided under the BSD-3 clause.
 */

#include <sys/stdarg.h>
#include <aux/printf.h>
#include <nucleus/bugcheck.h>

static CHAR MessageBuffer[256];
static va_list Ap;

VOID
BugCheckHandler(const CHAR *Fmt, ...)
{
    if (Fmt == NULL) {
        return;
    }

    vsnprintf(MessageBuffer, sizeof(MessageBuffer), Fmt, Ap);
    printf("** BUGCHECK: %s", MessageBuffer);
    printf("... Something has gone wrong during system operation.\n");
    printf("... The kernel kitty pilot has halted the machine to prevent damage of data.\n");
}
