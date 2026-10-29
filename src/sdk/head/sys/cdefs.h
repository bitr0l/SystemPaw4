/*
 * Copyright (c) 2026, Chloe M., et al.
 * Provided under the BSD-3 clause.
 */

#ifndef _SYS_CDEFS_H_
#define _SYS_CDEFS_H_ 1

/* Compiler specific definitions */
#define ASMV              __asm__ __volatile__
#define ATTR(X)           __attribute__((X))
#define SECTION(X)        ATTR(section((X)))
#define ALIGN(N)          ATTR(aligned((N)))
#define PACKED            ATTR(packed)
#define NO_RETURN         ATTR(noreturn)
#define ALWAYS_INLINE     ATTR(always_inline)
#define BARRIER()         ASMV("" ::: "memory")

/* Pointer offset macros */
#define PTR_OFFSET(p, off) ((void *)(char *)(p) + (off))
#define PTR_NOFFSET(p, off) ((void *)(char *)(p) - (off))

/* Bit related macros */
#define BIT(n) (1ULL << (n))
#define ISSET(v, f)  ((v) & (f))

/* Align up/down a value */
#define ALIGN_DOWN(value, align)      ((value) & ~((align)-1))
#define ALIGN_UP(value, align)        (((value) + (align)-1) & ~((align)-1))

/* Bitmap helper macros */
#define SETBIT(a, b) ((a)[(b) >> 3] |= BIT(b % 8))
#define CLRBIT(a, b) ((a)[(b) >> 3] &= ~BIT(b % 8))
#define TESTBIT(a, b) (ISSET((a)[(b) >> 3], BIT(b % 8)))

/* Min/max macros */
#define MIN(a,b) (((a) < (b)) ? (a) : (b))
#define MAX(a,b) (((a) > (b)) ? (a) : (b))

/* Get number of array elements */
#define NELEM(a) (sizeof(a) / sizeof(a[0]))

#endif  /* !_SYS_CDEFS_H_ */
