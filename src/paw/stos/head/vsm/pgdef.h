/*
 * Copyright (c) 2026, Chloe M., et al.
 * Provided under the BSD-3 clause.
 */

#ifndef _VSM_PGDEF_H_
#define _VSM_PGDEF_H_ 1

#include <sys/tree.h>
#include <stdef.h>
#include <nucleus/bal.h>

/*
 * Represents the page allocation base address, this range is outside
 * of the direct map and thus cannot be converted between physical/virtual
 * using PMA_TO_VMA() or VMA_TO_PMA().
 */
#define PG_ALLOC_BASE 0xFFFF804000000000

/*
 * Macros used to convert virtual addresses to physical addresses and
 * vice versa. These macros can only be used for addresses that are
 * within the direct map.
 */
#define PMA_TO_VMA(PMA) \
    (VOID *)PTR_OFFSET((PMA), BalGetDirectMap())
#define VMA_TO_PMA(VMA) \
    (UPTR)PTR_NOFFSET((VMA), BalGetDirectMap())

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

#endif  /* !_VSM_PGDEF_H_ */
