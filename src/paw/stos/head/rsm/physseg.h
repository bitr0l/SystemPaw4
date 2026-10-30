/*
 * Copyright (c) 2026, Chloe M., et al.
 * Provided under the BSD-3 clause.
 */

#ifndef _RSM_PHYSSEG_H_
#define _RSM_PHYSSEG_H_ 1

#include <stdef.h>

/*
 * Initialize the RSM physical memory management
 */
VOID RsmPhysMemInit(VOID);

/*
 * Allocate a single frame of physical memory.
 *
 * XXX: We only support handing out single frames of memory due
 *      to the underlying architecture being a freelist and not
 *      guaranteed contiguous. For contigous memory allocation,
 *      consider using the allocation facilities in the VSM
 *      subsystem.
 *
 *  A returned value of zero indicates insufficient resources.
 */
UPTR RsmAllocateFrame(VOID);

#endif  /* !_RSM_PHYSSEG_H_ */
