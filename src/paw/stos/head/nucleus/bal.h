/*
 * Copyright (c) 2026, Chloe M., et al.
 * Provided under the BSD-3 clause.
 */

#ifndef _NUCLEUS_BPAL_H_
#define _NUCLEUS_BPAL_H_ 1

#include <stdef.h>

/*
 * Represents the boot abstraction layer handle
 *
 * @DirectMap:  Direct map base
 */
typedef struct {
    UPTR DirectMap;
} BAL_HANDLE;

/*
 * Initialize the boot abstraction layer
 */
VOID NucBalInit(VOID);

/*
 * Obtain a copy of the BAL handle
 *
 * @Result:  Result is written here
 */
VOID BalGetHandle(BAL_HANDLE *Result);

/* Backend init functions */
VOID BalLimineInit(BAL_HANDLE *Handle);

/*
 * Obtain the direct map base address
 */
ALWAYS_INLINE static inline UPTR
BalGetDirectMap(VOID)
{
    BAL_HANDLE Handle;

    BalGetHandle(&Handle);
    return Handle.DirectMap;
}

#endif  /* !_NUCLEUS_BPAL_H_ */
