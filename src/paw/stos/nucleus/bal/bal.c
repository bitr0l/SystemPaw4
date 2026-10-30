/*
 * Copyright (c) 2026, Chloe M., et al.
 * Provided under the BSD-3 clause.
 */

#include <nucleus/bal.h>
#include <nucleus/bugcheck.h>
#include <aux/string.h>

#ifndef _BOOT_PROTO
#error "Boot protocol is not defined"
#else
#define BOOT_PROTO _BOOT_PROTO
#endif  /* !_BOOT_PROTO */

/* Initialize the BAL handle */
static BAL_HANDLE BalHandle;

VOID
BalGetHandle(BAL_HANDLE *Result)
{
    if (Result == NULL) {
        return;
    }

    *Result = BalHandle;
}

VOID
NucBalInit(VOID)
{
    const CHAR *BootProto = BOOT_PROTO;

    switch (*BootProto) {
    case 'l':
        if (StrEq(BootProto, "limine")) {
            BalLimineInit(&BalHandle);
            return;
        }
    }

    NucBugCheck("invalid boot protocol\n");
}
