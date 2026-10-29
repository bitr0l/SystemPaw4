/*
 * Copyright (c) 2026, Chloe M., et al.
 * Provided under the BSD-3 clause.
 */

#ifndef _SYS_TYPES_H_
#define _SYS_TYPES_H_ 1

/* Boolean values */
#define TRUE    1
#define FALSE   0

/* Boolean type */
typedef _Bool BOOLEAN;

/* Unsigned types */
typedef unsigned char           UCHAR;
typedef unsigned short          USHORT;
typedef unsigned int            ULONG;
typedef unsigned long long      UQUAD;
#if __SIZEOF_SIZE_T__ == 8
typedef UQUAD                   USIZE;
#else
typedef ULONG                   USIZE;
#endif  /* __SIZEOF_SIZE_T__ */

/* Signed types */
typedef char        CHAR;
typedef short       SHORT;
typedef int         LONG;
typedef long long   QUAD;
#if __SIZEOF_SIZE_T__ == 8
typedef QUAD        SSIZE;
#else
#endif  /* !__SIZEOF_SIZE_T__ */

typedef void VOID;

#endif  /* !_SYS_TYPES_H_ */
