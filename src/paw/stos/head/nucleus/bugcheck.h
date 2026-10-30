/*
 * Copyright (c) 2026, Chloe M., et al.
 * Provided under the BSD-3 clause.
 */

#ifndef _NUCLEUS_BUGCHECK_H_
#define _NUCLEUS_BUGCHECK_H_ 1

#include <stdef.h>

/*
 * Signal to the operator that something has gone wrong during
 * system operation.
 *
 * @Fmt:    Format specifier
 * @<...>:  Variadic arguments
 */
VOID NucBugCheck(const CHAR *Fmt, ...);

#endif  /* !_NUCLEUS_BUGCHECK_H_ */
