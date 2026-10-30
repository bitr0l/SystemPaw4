/*
 * Copyright (c) 2026, Chloe M., et al.
 * Provided under the BSD-3 clause.
 */

#ifndef _CTRACE_OBJECT_H_
#define _CTRACE_OBJECT_H_ 1

#include <stdef.h>
#include <io/cab.h>

/* Object flags */
#define CTRACE_GCONS_SYNC  BIT(0)   /* Sync to global console */

/* Maximum name of CTRACE object name (includes NUL) */
#define CTRACE_OBJECT_NAMELEN 256

/* CTRACE_OBJECT cookie */
#define CTRACE_COOKIE 0xCA7F00D

/*
 * Represents a CTRACE buffer
 *
 * @Cookie:      Cookie for identification
 * @Name:        Name of object
 * @CabioList:   Single entry CABIO list
 * @MBuf:        Message buffer
 * @Flags:       Object specific flags
 */
typedef struct {
    ULONG Cookie;
    CHAR Name[CTRACE_OBJECT_NAMELEN];
    MPG_CABIO_LIST CabioList;
    MPG_CABIO MBuf;
    USHORT Flags;
} CTRACE_OBJECT;

/*
 * Initialize a CTRACE object
 *
 * @Name:       Name of CTRACE object
 * @Flags:      Object specific flags
 * @Result:     Result is written here
 */
ST_STATUS CTraceInitObject(const CHAR *Name, USHORT Flags, CTRACE_OBJECT *Result);

/*
 * Write to a CTRACE object
 *
 * @Object:  Object to write to
 * @Data:    Data to write
 * @Length:  Length of data to write
 *
 * Returns the number of bytes written on success, zero if full
 * and less than zero on error.
 */
SSIZE CTraceWrite(CTRACE_OBJECT *Object, const CHAR *Data, USIZE Length);

#endif  /* !_CTRACE_OBJECT_H_ */
