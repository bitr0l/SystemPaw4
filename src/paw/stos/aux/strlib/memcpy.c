/*
 * Copyright (c) 2026, Chloe M., et al.
 * Provided under the BSD-3 clause.
 */

#include <aux/string.h>

VOID *
MemCpy(VOID *Dest, const VOID *Source, USIZE Length)
{
    UCHAR *ByteDest;
    const UCHAR *ByteSource;
    USIZE Index = 0;

    if (Dest == NULL || Source == NULL) {
        return NULL;
    }

    ByteDest = (UCHAR *)Dest;
    ByteSource = (const UCHAR *)Source;

    while (Index < Length) {
        ByteDest[Index] = ByteSource[Index];
        ++Index;
    }

    return Dest;
}
