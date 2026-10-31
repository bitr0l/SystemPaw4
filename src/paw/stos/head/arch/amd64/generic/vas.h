/*
 * Copyright (c) 2026, Chloe M., et al.
 * Provided under the BSD-3 clause.
 */

#ifndef _MACHINE_VAS_H_
#define _MACHINE_VAS_H_ 1

#include <stdef.h>

/*
 * Represents a virtual address space
 *
 * @Cr3:  Third control register
 */
typedef struct {
    UPTR Cr3;
} MMU_VAS;

#endif  /* !_MACHINE_VAS_H_ */
