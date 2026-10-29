/*
 * Copyright (c) 2026, Chloe M., et al.
 * Provided under the BSD-3 clause.
 */

#ifndef _AUX_STRING_H_
#define _AUX_STRING_H_ 1

#include <stdef.h>

/*
 * Compute the length of a string in bytes
 *
 * @String:  String to get length of
 */
USIZE StrLen(const CHAR *String);

/*
 * Returns true if the two given strings are equal
 *
 * @StringA:  First string to compare
 * @StringB:  Second string to compare
 */
BOOLEAN StrEq(const CHAR *StringA, const CHAR *StringB);

/*
 * Copy one buffer to another
 *
 * @Dest:   Destination buffer
 * @Source: Source buffer
 * @Length: Number of bytes to copy
 */
VOID *MemCpy(VOID *Dest, const VOID *Source, USIZE Length);

#endif  /* !_AUX_STRING_H_ */
