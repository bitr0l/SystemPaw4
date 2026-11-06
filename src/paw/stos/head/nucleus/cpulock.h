/*
 * Copyright (c) 2026, Chloe M., et al.
 * Provided under the BSD-3 clause.
 */

#ifndef _NUCLEUS_CPULOCK_H_
#define _NUCLEUS_CPULOCK_H_ 1

#include <stdef.h>

/*
 * Represents a bare spinlock
 */
typedef struct {
    UQUAD Lock;
} CPU_LOCK;

/* Initialize a CPU lock */
#define CPU_LOCK_INIT(LOCK_P) \
    ((LOCK_P)->Lock) = 0

/*
 * Acquire a CPU lock
 *
 * @Lock:   Lock to acquire
 * @IntMut: If true, disable interrupts while acquired
 */
VOID NucCpuLockAcq(CPU_LOCK *Lock, BOOLEAN IntMut);

/*
 * Release a CPU lock
 *
 * @Lock:  Lock to release
 */
VOID NucCpuLockRel(CPU_LOCK *Lock);

#endif  /* !_NUCLEUS_CPULOCK_H_ */
