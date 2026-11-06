/*
 * Copyright (c) 2026, Chloe M., et al.
 * Provided under the BSD-3 clause.
 */

#ifndef _MACHINE_PRIM_H_
#define _MACHINE_PRIM_H_ 1

#include <stdef.h>

#define MdCpuSuspend()      ASMV("hlt")
#define MdCpuSpinWait()     ASMV("pause")
#define MdCpuIntMask()      ASMV("cli")
#define MdCpuIntUnmask()    ASMV("sti")

/*
 * Atomic swap operation
 *
 * @Ptr: Location to swap with @Value
 * @Value: Value to swap to @Ptr
 */
ALWAYS_INLINE static inline UQUAD
MdCpuAswap(UQUAD *Ptr, UQUAD Value)
{
    QUAD RetVal;

    if (Ptr == NULL) {
        return 0;
    }

    RetVal = *(volatile UQUAD *)Ptr;
    ASMV(
        "xchg %0, %1\n"
        : "+m" (*Ptr), "+r" (Value)
        :
        : "memory"
    );

    return RetVal;
}

/*
 * Returns true if interrupts are enabled on the current
 * processing element.
 */
ALWAYS_INLINE static inline BOOLEAN
MdCpuIntEn(VOID)
{
    UQUAD RFlags;

    ASMV(
        "pushfq\n"
        "popq %0"
        : "=r" (RFlags)
        :
        : "memory"
    );

    return ISSET(RFlags, BIT(9)) != 0;
}

#endif  /* !_MACHINE_PRIM_H_ */
