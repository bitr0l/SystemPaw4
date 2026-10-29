/*
 * Copyright (c) 2026, Chloe M., et al.
 * Provided under the BSD-3 clause.
 */

#include <stdef.h>
#include <pexpert/serial.h>

VOID
_putchar(CHAR c)
{
    /* Translate NL TO CRNL */
    if (c == '\n') {
        PxSerialDebugLn(SERIAL_COM0, "\r\n", 2);
        return;
    }

    PxSerialDebugLn(SERIAL_COM0, &c, 1);
}
