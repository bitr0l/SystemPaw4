/*
 * Copyright (c) 2026, Chloe M., et al.
 * Provided under the BSD-3 clause.
 */

#include <ctrace/registry.h>
#include <ctrace/ctracevar.h>
#include <aux/string.h>

static CTRACE_ROOT_DOM RootDom = {0};

ST_STATUS
CTraceGetRootOb(const CHAR *Name, CTRACE_OBJECT **Result)
{
    CTRACE_OBJECT *Object;
    USIZE Index;

    if (Name == NULL || Result == NULL) {
        return STATUS_INVALID_PARAM;
    }

    for (Index = 0; Index < CTRACE_ROOT_ENTRIES; ++Index) {
        Object = &RootDom.Storage[Index];

        /* Must have a valid cookie */
        if (Object->Cookie != CTRACE_COOKIE) {
            continue;
        }

        /* First byte filter */
        if (Object->Name[0] != *Name) {
            continue;
        }

        /* Is it not a match? */
        if (!StrEq(Object->Name, Name)) {
            continue;
        }

        /* Is it disabled? */
        if (ISSET(RootDom.EnMask, 1 << Index)) {
            *Result = &RootDom.NullSink;
            return STATUS_SUCCESS;
        }

        *Result = Object;
        return STATUS_SUCCESS;
    }

    return STATUS_NOT_FOUND;
}

VOID
CTraceInitRegistry(VOID)
{
    ST_STATUS Status;

    Status = CTraceInitObject("__null", 0, &RootDom.NullSink);
    if (Status != STATUS_SUCCESS) {
        /* TODO: Panic here */
        return;
    }
}

/*
 * TODO: Add locking here
 */
ST_STATUS
CTraceAllocFromRoot(CTRACE_OBJECT **Result)
{
    if (Result == NULL) {
        return STATUS_INVALID_PARAM;
    }

    if (RootDom.EnqPtr >= CTRACE_ROOT_ENTRIES) {
        return STATUS_OUT_OF_RESOURCES;
    }

    *Result = &RootDom.Storage[RootDom.EnqPtr++];
    return STATUS_SUCCESS;
}

VOID
CTraceSetRootMask(CTRACE_EN_MASK Mask)
{
    RootDom.EnMask = Mask;
}

CTRACE_EN_MASK
CTraceGetRootMask(VOID)
{
    return RootDom.EnMask;
}
