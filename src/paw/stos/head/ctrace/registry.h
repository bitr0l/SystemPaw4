/*
 * Copyright (c) 2026, Chloe M., et al.
 * Provided under the BSD-3 clause.
 */

#ifndef _CTRACE_REGISTRY_H_
#define _CTRACE_REGISTRY_H_ 1

#include <ctrace/object.h>
#include <ctrace/ctracevar.h>
#include <stdef.h>

/*
 * Obtain a CTRACE object by-name from the root domain
 *
 * @Name:   Name of object to obtain
 * @Result: Result is written here
 *
 * XXX: Entries that are marked as disabled result in a NULL sink being
 *      returned instead of that entry.
 */
ST_STATUS CTraceGetRootOb(const CHAR *Name, CTRACE_OBJECT **Result);

/*
 * Allocate an object from the root domain
 *
 * @Result: Result is written here
 */
ST_STATUS CTraceAllocFromRoot(CTRACE_OBJECT **Result);

/*
 * Set the root domain enable mask
 *
 * @Mask:  Mask to set
 */
VOID CTraceSetRootMask(CTRACE_EN_MASK Mask);

/*
 * Obtain the root domain enable mask
 */
CTRACE_EN_MASK CTraceGetRootMask(VOID);

/*
 * Initialize the CTRACE registry
 */
VOID CTraceInitRegistry(VOID);

#endif  /* !_CTRACE_REGISTRY_H_ */
