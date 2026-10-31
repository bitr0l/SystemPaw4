/*
 * Copyright (c) 2026, Chloe M., et al.
 * Provided under the BSD-3 clause.
 */

#ifndef _WSCONS_WSCONS_H_
#define _WSCONS_WSCONS_H_ 1

#include <stdef.h>

/*
 * Initialize the workstation console
 */
VOID WsConsInit(VOID);

/*
 * Write a number of bytes to the workstation console
 *
 * @String:  String to write
 * @Length:  Number of bytes to write
 */
VOID WsConsWrite(const CHAR *String, USIZE Length);

#endif  /* !_WSCONS_WSCONS_H_ */
