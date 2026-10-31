/*
 * Copyright (c) 2026, Chloe M., et al.
 * Provided under the BSD-3 clause.
 */

#ifndef _PEXPERT_PIB_H_
#define _PEXPERT_PIB_H_ 1

#include <ctrace/object.h>
#include <pexpert/mpb.h>
#include <stdef.h>

/*
 * A Processor Information Block (PIB) contains machine independent
 * processor information.
 *
 * @LogicalId:   Logical processor identifier assigned by us
 * @LogStore:    Local per-core log store
 * @Mcb:         Machine processor block
 */
typedef struct {
    ULONG LogicalId;
    CTRACE_OBJECT *LogStore;
    MPB Mpb;
} PIB;

/*
 * Phase 1 initialization of current processor
 *
 * @Result:  Result is written here
 *
 * XXX: The logical identifier field is not set by us, the caller must
 *      take care in assigning it themselves before calling us. Furthermore,
 *      the caller of this function must be the exact processor of the PIB to
 *      initialize.
 */
VOID PxPibP1Init(PIB *Result);

/*
 * Obtain a reference to the current Processor Information
 * Block.
 */
PIB *PxGetPib(VOID);

#endif  /* !_PEXPERT_PIB_H_ */
