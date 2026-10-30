/*
 * Copyright (c) 2026, Chloe M., et al.
 * Provided under the BSD-3 clause.
 */

#ifndef _CTRACE_CTRACEVAR_H_
#define _CTRACE_CTRACEVAR_H_ 1

#include <ctrace/object.h>
#include <io/cab.h>
#include <stdef.h>

/* Maximum root domain entries */
#define CTRACE_ROOT_ENTRIES 16

/* Enable mask type */
typedef ULONG CTRACE_EN_MASK;

/*
 * Global CTrace flush callback
 *
 * (see aux/cab.h)
 */
SSIZE CTraceFlushObject(
    struct _MPG_CABIO_LIST *List,
    struct _MPG_CABIO *Cabio,
    VOID *Data,
    USIZE Offset,
    USIZE Length,
    USHORT Flags
);

/*
 * Represents a Cumponent Trace Kit root domain which has
 * a fixed number of entries.
 *
 * @NullSink:    Null sink for disabled entries
 * @Storage:     Room domain storage
 * @EnMask:      [1: disabled, 0: enabled]
 * @EnqPtr:      Storage enqueue pointer
 */
typedef struct {
    CTRACE_OBJECT NullSink;
    CTRACE_OBJECT Storage[CTRACE_ROOT_ENTRIES];
    CTRACE_EN_MASK EnMask;
    USHORT EnqPtr;
} CTRACE_ROOT_DOM;

#endif  /* !_CTRACE_CTRACEVAR_H_ */
