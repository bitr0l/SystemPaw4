/*
 * Copyright (c) 2026, Chloe M., et al.
 * Provided under the BSD-3 clause.
 */

#include <aux/string.h>

USIZE
StrLen(const CHAR *String)
{
    USIZE Length = 0;

    if (String == NULL) {
        return 0;
    }

    while (String[Length++] != '\0');
    return Length - 1;
}
