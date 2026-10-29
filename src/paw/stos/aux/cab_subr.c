/*
 * Copyright (c) 2026, Chloe M., et al.
 * Provided under the BSD-3 clause.
 */

#include <aux/cab.h>

/*
 * Flush a CABIO
 *
 * @List:       CABIO list
 * @Offset:     Flush offset
 * @Cabio:      CABIO to flush
 * @Flags:      Backend specific flags
 */
static inline USIZE
FlushCabio(MPG_CABIO_LIST *List, USIZE Offset, MPG_CABIO *Cabio, USHORT Flags)
{
    if (List == NULL || Cabio == NULL) {
        return 0;
    }

    return List->FlushCb(List, Cabio->Chunk, Offset, Cabio->Length, Flags);
}

ST_STATUS
MpgCabioListInit(MPG_CABIO_LIST *List, MpgCabioFlushCb FlushCb)
{
    if (List == NULL) {
        return STATUS_INVALID_PARAM;
    }

    List->Head = NULL;
    List->Tail = NULL;
    List->NrEntries = 0;
    List->FlushCb = FlushCb;
    return STATUS_SUCCESS;
}

ST_STATUS
MpgCabioInit(MPG_CABIO *Cabio)
{
    if (Cabio == NULL) {
        return STATUS_INVALID_PARAM;
    }

    Cabio->Length = 0;
    Cabio->Next = NULL;
    return STATUS_SUCCESS;
}

ST_STATUS
MpgCabioListInsert(MPG_CABIO_LIST *List, MPG_CABIO *Cabio)
{
    MPG_CABIO *Head;

    if (List == NULL || Cabio == NULL) {
        return STATUS_INVALID_PARAM;
    }

    /* Is this the first element? */
    if (List->Head == NULL || List->Tail == NULL) {
        List->Head = Cabio;
        List->Tail = Cabio;
        ++List->NrEntries;
        return STATUS_SUCCESS;
    }

    /* Insert to end */
    Head = List->Head;
    Head->Next = Cabio;
    List->Head = Head->Next;
    ++List->NrEntries;
    return STATUS_SUCCESS;
}

SSIZE
MpgCabioListFlush(MPG_CABIO_LIST *List, USHORT Flags)
{
    MPG_CABIO *Tail;
    USIZE NrBytes = 0;
    USIZE Offset = 0;

    if (List == NULL) {
        return -1;
    }

    if ((Tail = List->Tail) == NULL) {
        return -1;
    }

    while (Tail != NULL) {
        NrBytes += FlushCabio(List, Offset, Tail, Flags);
        Tail->Length = 0;

        Tail = Tail->Next;
        Offset += X_MPG_CAB_WIDTH;
    }

    return NrBytes;
}
