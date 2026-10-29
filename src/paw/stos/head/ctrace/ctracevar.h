/*
 * Copyright (c) 2026, Chloe M., et al.
 * Provided under the BSD-3 clause.
 */

#ifndef _CTRACE_CTRACEVAR_H_
#define _CTRACE_CTRACEVAR_H_ 1

#include <aux/cab.h>
#include <stdef.h>

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

#endif  /* !_CTRACE_CTRACEVAR_H_ */
