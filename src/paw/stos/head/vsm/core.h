/*
 * Copyright (c) 2026, Chloe M., et al.
 * Provided under the BSD-3 clause.
 */

#ifndef _VSM_CORE_H_
#define _VSM_CORE_H_ 1

#include <sys/status.h>
#include <vsm/pgdb.h>
#include <stdef.h>

/*
 * Initialize the virtual address space and VSM core
 * subsystem.
 */
VOID VsmInitMemory(VOID);

/*
 * Allocate a number of pages
 *
 * @PageCount:   Number of pages to allocate
 * @Result:      Result is written here
 */
ST_STATUS VsmAllocatePages(USIZE PageCount, PAGE_DESCRIPTOR **Result);

#endif  /* !_VSM_CORE_H_ */
