/*
 * Copyright (c) 2026, Chloe M., et al.
 * Provided under the BSD-3 clause.
 */

#ifndef _VSM_PAGEDB_H_
#define _VSM_PAGEDB_H_ 1

#include <sys/tree.h>
#include <sys/status.h>
#include <stdef.h>

/*
 * Represents page metadata that is referenced by a page
 * descriptor.
 *
 * @BasePtr:  Base of page
 * @EndPtr:   End of page
 */
typedef struct {
    UPTR BasePtr;
    UPTR EndPtr;
} PAGE_INFO;

/*
 * A page descriptor represents a single page of memory
 * and is an entry within the page descriptor tree.
 *
 * @Link:   Tree link
 * @Info:   Page metadata
 */
typedef struct _PAGE_DESCRIPTOR {
    RB_ENTRY(_PAGE_DESCRIPTOR) Link;
    PAGE_INFO *Info;
} PAGE_DESCRIPTOR;

/*
 * Represents a page tree database
 *
 * @Head:       Page tree head
 * @NrEntries:  Number of entries in pagedb
 */
typedef struct {
    RB_HEAD(PageDb, _PAGE_DESCRIPTOR) Head;
    USIZE NrEntries;
} PAGE_DB;

/*
 * Insert a page descriptor into the page database
 *
 * @PageDb:  Page database to insert to
 * @Desc:    Page descriptor to insert
 *
 * Returns zero on success
 */
ST_STATUS VsmPageDbInsert(PAGE_DB *PageDb, PAGE_DESCRIPTOR *Desc);

/*
 * Initialize a page database
 *
 * @PageDb:  Page database
 */
ST_STATUS VsmPageDbInit(PAGE_DB *PageDb);

#endif  /* !_VSM_PAGEDB_H_ */
