/*
 * Copyright (c) 2026, Chloe M., et al.
 * Provided under the BSD-3 clause.
 */

#include <aux/string.h>

BOOLEAN
StrEq(const CHAR *StringA, const CHAR *StringB)
{
    if (StringA == NULL || StringB == NULL) {
        return FALSE;
    }

    /* Compare the two strings */
    while (*StringA != '\0' && *StringB != '\0') {
        if (*StringA++ != *StringB++) {
            return FALSE;
        }
    }

    /* Check the tail */
    if (*StringA != *StringB) {
        return FALSE;
    }

    return TRUE;
}
