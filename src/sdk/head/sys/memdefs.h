/*
 * Copyright (c) 2026, Chloe M., et al.
 * Provided under the BSD-3 clause.
 */

#ifndef _SYS_MEMDEFS_H_
#define _SYS_MEMDEFS_H_ 1

#include <stdef.h>

/* Valid page protection flags */
#define PROT_NONE   0x00
#define PROT_READ   BIT(0)
#define PROT_WRITE  BIT(1)
#define PROT_EXEC   BIT(2)
#define PROT_USER   BIT(3)

/* All protection flags are of this type */
typedef UCHAR MEM_PROT;

#endif  /* !_SYS_MEMDEFS_H_ */
