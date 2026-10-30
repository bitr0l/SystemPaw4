/*
 * Copyright (c) 2026, Chloe M., et al.
 * Provided under the BSD-3 clause.
 */

#ifndef _MACHINE_MSR_H_
#define _MACHINE_MSR_H_ 1

#ifndef __ASSEMBLER__
#include <stdef.h>
#endif  /* !__ASSEMBLER__ */

#define IA32_SPEC_CTL       0x00000048
#define IA32_KERNEL_GS_BASE 0xC0000102
#define IA32_GS_BASE        0xC0000101
#define IA32_FS_BASE        0xC0000100
#define IA32_APIC_BASE_MSR  0x0000001B

#ifndef __ASSEMBLER__
ALWAYS_INLINE static inline UQUAD
MdRdmsr(ULONG Address)
{
    ULONG Low, High;

    ASMV(
        "rdmsr"
        : "=a" (Low), "=d" (High)
        : "c" (Address)
        : "memory"
    );

    return ((UQUAD)High << 32) | Low;
}

ALWAYS_INLINE static inline VOID
MdWrmsr(ULONG Address, UQUAD Value)
{
    ULONG Low, High;

    Low = Value & 0xFFFFFFFF;
    High = (Value >> 32) & 0xFFFFFFFF;

    ASMV(
        "wrmsr"
        :
        : "a" (Low), "d" (High),
          "c" (Address)
        : "memory"
    );
}

#endif  /* !__ASSEMBLER__ */
#endif  /* !_MACHINE_MSR_H_ */
