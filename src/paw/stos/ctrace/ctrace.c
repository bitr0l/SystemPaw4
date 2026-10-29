/*
 * Copyright (c) 2026, Chloe M., et al.
 * Provided under the BSD-3 clause.
 */

#include <ctrace/ctracevar.h>
#include <ctrace/object.h>
#include <aux/printf.h>

SSIZE
CTraceFlushObject(struct _MPG_CABIO_LIST *List, struct _MPG_CABIO *Cabio,
    VOID *Data, USIZE Offset, USIZE Length, USHORT Flags)
{
    CTRACE_OBJECT *Object;
    USIZE Index;
    CHAR *ByteData = (CHAR *)Data;

    if (List == NULL || Data == NULL) {
        return -1;
    }

    if ((Object = Cabio->Data) == NULL) {
        return -1;
    }

    /* Cookie must match */
    if (Object->Cookie != CTRACE_COOKIE) {
        return -1;
    }

    /*
     * If we are flushing to the global console, do it, otherwise
     * just reset the CABIO.
     */
    if (ISSET(Flags, CTRACE_GCONS_SYNC)) {
        printf("[%s] : ", Object->Name);
        for (Index = 0; Index < Length; ++Index) {
            printf("%c", ByteData[Index]);
        }

        return Length;
    }

    MpgCabioReset(Cabio);
    return Length;
}
