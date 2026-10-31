/*
 * Copyright (c) 2026, Chloe M., et al.
 * Provided under the BSD-3 clause.
 */

#ifndef _MACHINE_CPUID_H_
#define _MACHINE_CPUID_H_ 1

#include <sys/cdefs.h>

#define CPUID(level, a, b, c, d)                        \
    ASMV("cpuid\n\t"                                    \
            : "=a" (a), "=b" (b), "=c" (c), "=d" (d)    \
            : "0" (level))

#endif  /* !_MACHINE_CPUID_H_ */
