/*
 * Copyright (c) 2026, Chloe M., et al.
 * Provided under the BSD-3 clause.
 */

#ifndef _AUX_CAB_H_
#define _AUX_CAB_H_ 1

#include <stdef.h>

/* Width of fixed mpg_cabio, 8K for now */
#define X_MPG_CAB_WIDTH 0x2000

/* Forward declarations */
struct _MPG_CABIO_LIST;

/*
 * Represents a cock and balls flush callback, this is used to
 * flush the buffer contents into some kind backing store. In
 * other words,, cum !!
 *
 * @List:   Fixed multi-page CABIO list to flush.
 * @Data:   The cum (data).
 * @Offset: Cum (data) offset.
 * @Length: Length of cum (data).
 * @Flags:  Backend specific flags.
 */
typedef SSIZE(*MpgCabioFlushCb)(
    struct _MPG_CABIO_LIST *List,
    VOID *Data,
    USIZE Offset,
    USIZE Length,
    USHORT Flags
);

/*
 * Fixed multi-page cock and ball (component address buffer)
 * I/O structure.
 *
 * @Chunk:  Fixed width buffer chunk
 * @Length: Length of chunk
 * @Next:   Next I/O buffer
 */
typedef struct _MPG_CABIO {
    UCHAR Chunk[X_MPG_CAB_WIDTH];
    USIZE Length;
    struct _MPG_CABIO *Next;
} MPG_CABIO;

/*
 * Represents a list of multi-paged cock and balls
 * (component address buffers).
 *
 * @Head:       Head of list (last element)
 * @Tail:       Tail of list (first element)
 * @NrEntries:  Total number of resident entries
 * @FlushCb:    Flush callback
 *
 * XXX: Probably should add some locking
 */
typedef struct _MPG_CABIO_LIST {
    MPG_CABIO *Head;
    MPG_CABIO *Tail;
    USIZE NrEntries;
    MpgCabioFlushCb FlushCb;
} MPG_CABIO_LIST;

/*
 * Initialize a Cock and Balls I/O structure list
 *
 * @List:       Cock and ball list to initialize
 * @FlushCb:    Callback for cumming
 */
ST_STATUS MpgCabioListInit(MPG_CABIO_LIST *List, MpgCabioFlushCb FlushCb);

/*
 * Insert a CABIO structure into a CABIO list
 *
 * @List:  CABIO list to insert to
 * @Cabio: I/O chunk to insert
 */
ST_STATUS MpgCabioListInsert(MPG_CABIO_LIST *List, MPG_CABIO *Cabio);

/*
 * Flush a CABIO list
 *
 * @List:  List to flush
 * @Flags: Backend specific flags
 *
 * XXX: This function only clears each chunks length but does
 *      not remove them from the list.
 */
SSIZE MpgCabioListFlush(MPG_CABIO_LIST *List, USHORT Flags);

/*
 * Initialzie a chunk buffer
 *
 * @Cabio:  CAB I/O chunk to initialize
 */
ST_STATUS MpgCabioInit(MPG_CABIO *Cabio);

#endif  /* !_AUX_CAB_H_ */
