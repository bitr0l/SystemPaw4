/*
 * Copyright (c) 2026, Chloe M., et al.
 * Provided under the BSD-3 clause.
 */

#ifndef _PEXPERT_MMU_H_
#define _PEXPERT_MMU_H_ 1

#include <stdef.h>
#include <machine/vas.h>

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

#endif  /* !_PEXPERT_MMU_H_ */
