/*
 * Copyright (c) 2026, Chloe M., et al.
 * Provided under the BSD-3 clause.
 */

#include <sys/stdarg.h>
#include <ctrace/object.h>
#include <ctrace/ctracevar.h>
#include <aux/string.h>
#include <aux/printf.h>

ST_STATUS
CTraceInitObject(const CHAR *Name, USHORT Flags, CTRACE_OBJECT *Result)
{
    USIZE NameLen;
    ST_STATUS Status;

    if (Name == NULL || Result == NULL) {
        return STATUS_INVALID_PARAM;
    }

    NameLen = StrLen(Name);
    if (NameLen > CTRACE_OBJECT_NAMELEN - 1) {
        return STATUS_NAME_TOO_LONG;
    }

    /* Initialize the name and MBuf */
    MemCpy(Result->Name, Name, NameLen);
    Status = MpgCabioInit(&Result->MBuf, Result);
    if (Status != STATUS_SUCCESS) {
        return Status;
    }

    /* Initialize the CABIO list */
    Status = MpgCabioListInit(&Result->CabioList, CTraceFlushObject);
    if (Status != STATUS_SUCCESS) {
        return Status;
    }

    /* Insert our MBus */
    Status = MpgCabioListInsert(&Result->CabioList, &Result->MBuf);
    if (Status != STATUS_SUCCESS) {
        return Status;
    }

    Result->Flags = Flags;
    Result->Cookie = CTRACE_COOKIE;
    return STATUS_SUCCESS;
}

SSIZE
CTraceWrite(CTRACE_OBJECT *Object, const CHAR *Data, USIZE Length)
{
    USIZE Index;

    if (Object == NULL || Data == NULL) {
        return -1;
    }

    if (Object->Cookie != CTRACE_COOKIE) {
        return -1;
    }

    /*
     * Write the bytes to the backing store, if we hit a newline we are to
     * flush the CABIO.
     */
    for (Index = 0; Index < Length; ++Index) {
        if ((MpgCabioWrite(&Object->MBuf, &Data[Index], 1)) == 0) {
            MpgCabioListFlush(&Object->CabioList, Object->Flags, TRUE);
            continue;
        }

        if (Data[Index] == '\n') {
            MpgCabioListFlush(&Object->CabioList, Object->Flags, FALSE);
        }
    }

    return Length;
}

SSIZE
CTraceDbgWrite(CTRACE_OBJECT *Object, const CHAR *Fmt, ...)
{
    if (Object == NULL || Fmt == NULL) {
        return -1;
    }

    va_list Ap;
    CHAR Buf[CTRACE_DEBUG_BUFLEN];
    USIZE Length;

    va_start(Ap, Fmt);
    vsnprintf(Buf, sizeof(Buf), Fmt, Ap);

    Length = StrLen(Buf);
    CTraceWrite(Object, Buf, Length);
    va_end(Ap);
    return Length;
}
