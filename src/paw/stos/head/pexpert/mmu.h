/*
 * Copyright (c) 2026, Chloe M., et al.
 * Provided under the BSD-3 clause.
 */

#ifndef _PEXPERT_MMU_H_
#define _PEXPERT_MMU_H_ 1

#include <sys/status.h>
#include <sys/memdefs.h>
#include <stdef.h>
#include <machine/vas.h>

/*
 * Valid page sizes that pexpert is capable of
 * understanding
 */
typedef enum {
    MMU_PAGESIZE_4K
} MMU_PAGESIZE;

/*
 * Obtain the current virtual address space
 *
 * @Result:  Result is written here
 */
VOID PxMmuGetVas(MMU_VAS *Result);

/*
 * Set the current virtual address space
 *
 * @Vas:  Virtual address space to set
 */
VOID PxMmuSetVas(MMU_VAS *Vas);

/*
 * Fork a virtual address space into another copy with the user
 * portion zeroed.
 *
 * @Source:  Source VAS to fork
 * @Dest:    Destination VAS structure
 */
VOID PxMmuForkVas(const MMU_VAS *Source, MMU_VAS *Dest);

/*
 * Map a single page of memory using a specified granularity
 *
 * @Vas:        Virtual address space to map within
 * @VmaBase:    Virtual memory base
 * @PmaBase:    Physical memory base
 * @Prot:       Protection flags
 * @PageSize:   Granularity to map with
 *
 * XXX: Addresses are expected to be aligned by the granularity
 */
ST_STATUS PxMmuMapPage(
    MMU_VAS *Vas,
    UPTR VmaBase,
    UPTR PmaBase,
    MEM_PROT Prot,
    MMU_PAGESIZE PageSize
);

#endif  /* !_PEXPERT_MMU_H_ */
