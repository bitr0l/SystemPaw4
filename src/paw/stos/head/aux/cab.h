/*
 * Copyright (c) 2026, Chloe M., et al.
 * Provided under the BSD-3 clause.
 */

#ifndef _AUX_CAB_H_
#define _AUX_CAB_H_ 1

#include <stdef.h>

/* Width of fixed mpg_cabio, 8K for now */
#define X_MPG_CAB_WIDTH 0x2000

/*
 * Fixed multi-page cock and ball (component address buffer)
 * I/O structure.
 *
 * @Chunk:  Fixed width buffer chunk
 * @Next:   Next I/O buffer
 */
typedef struct _MPG_CABIO {
    UCHAR Chunk[X_MPG_CAB_WIDTH];
    struct _MPG_CABIO *Next;
} MPG_CABIO;

/*
 * Represents a list of multi-paged cock and balls
 * (component address buffers).
 *
 * @Head:       Head of list
 * @Tail:       Tail of list
 * @NrEntries:  Total number of resident entries
 * @FlushCb:    Flush callback
 */
typedef struct _MPG_CABIO_LIST {
    MPG_CABIO *Head;
    MPG_CABIO *Tail;
    USIZE NrEntries;
    SSIZE(*FlushCb)(struct _MPG_CABIO_LIST *List, USHORT Flags);
} MPG_CABIO_LIST;

#endif  /* !_AUX_CAB_H_ */
