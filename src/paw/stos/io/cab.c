/*
 * Copyright (c) 2026, Chloe M., et al.
 * Provided under the BSD-3 clause.
 */

#include <io/cab.h>
#include <aux/string.h>

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
    USIZE NrFlush;

    if (List == NULL || Cabio == NULL) {
        return 0;
    }

    NrFlush = List->FlushCb(
        List,
        Cabio,
        &Cabio->Chunk[Cabio->Deq],
        Offset,
        Cabio->Enq - Cabio->Deq,
        Flags
    );

    Cabio->Deq = (Cabio->Deq + NrFlush) & (X_MPG_CAB_WIDTH - 1);
    return NrFlush;
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
MpgCabioInit(MPG_CABIO *Cabio, VOID *Data)
{
    if (Cabio == NULL) {
        return STATUS_INVALID_PARAM;
    }

    Cabio->Enq = 0;
    Cabio->Deq = 0;
    Cabio->Data = Data;
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
MpgCabioListFlush(MPG_CABIO_LIST *List, USHORT Flags, BOOLEAN Reset)
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
        if (Reset) {
            MpgCabioReset(Tail);
        }
        Tail = Tail->Next;
        Offset += X_MPG_CAB_WIDTH;
    }

    return NrBytes;
}

ST_STATUS
MpgCabioReset(MPG_CABIO *Cabio)
{
    if (Cabio == NULL) {
        return STATUS_INVALID_PARAM;
    }

    Cabio->Enq = 0;
    Cabio->Deq = 0;
    return STATUS_SUCCESS;
}

SSIZE
MpgCabioWrite(MPG_CABIO *Cabio, const CHAR *Data, USIZE Length)
{
    USIZE RealLength = Length;

    if (Cabio == NULL || Data == NULL) {
        return -1;
    }

    if ((Length + Cabio->Enq) > X_MPG_CAB_WIDTH) {
        RealLength = (Length + Cabio->Enq) - X_MPG_CAB_WIDTH;
    }

    MemCpy(&Cabio->Chunk[Cabio->Enq], Data, RealLength);
    Cabio->Enq += RealLength;
    return RealLength;
}
