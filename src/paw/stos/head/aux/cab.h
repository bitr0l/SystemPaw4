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
struct _MPG_CABIO;

/*
 * Represents a cock and balls flush callback, this is used to
 * flush the buffer contents into some kind backing store. In
 * other words,, cum !!
 *
 * @List:   Fixed multi-page CABIO list to flush.
 * @Cabio:  CABIO being flushed
 * @Data:   The cum (data).
 * @Offset: Cum (data) offset.
 * @Length: Length of cum (data).
 * @Flags:  Backend specific flags.
 */
typedef SSIZE(*MpgCabioFlushCb)(
    struct _MPG_CABIO_LIST *List,
    struct _MPG_CABIO *Cabio,
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
 * @Data:   Backend specific data
 * @Next:   Next I/O buffer
 */
typedef struct _MPG_CABIO {
    UCHAR Chunk[X_MPG_CAB_WIDTH];
    USIZE Length;
    VOID *Data;
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
 * Reset an MPG_CABIO structure
 *
 * @Cabio:  CABIO to reset
 */
ST_STATUS MpgCabioReset(MPG_CABIO *Cabio);

/*
 * Write data to a CABIO
 *
 * @Cabio:  CABIO to write to
 * @Data:   Data to write
 * @Length: Length of data to write
 *
 * Returns the number of bytes written on success, zero if full
 * and less than zero on error.
 */
SSIZE MpgCabioWrite(MPG_CABIO *Cabio, const CHAR *Data, USIZE Length);

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
 * @Data:   Backend specific data
 */
ST_STATUS MpgCabioInit(MPG_CABIO *Cabio, VOID *Data);

#endif  /* !_AUX_CAB_H_ */
