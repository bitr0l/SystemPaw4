/*
 * Copyright (c) 2026, Chloe M., et al.
 * Provided under the BSD-3 clause.
 */

#ifndef _PEXPERT_SERIAL_H_
#define _PEXPERT_SERIAL_H_ 1

#include <stdef.h>

/*
 * Represents a serial port abstraction
 *
 * @SERIAL_COM0:   First serial port
 * @SERIAL_COM1:   Second serial port
 *
 * XXX: Some platforms may implement one port while others may implement
 *      many, all platforms must start at SERIAL_COM0.
 */
typedef enum {
    SERIAL_COM0,
    SERIAL_COM1
} PX_SERIAL_PORT;

/*
 * Initialize the platform serial driver
 */
VOID PxSerialInit(VOID);

/*
 * Write some data to a specific serial port
 *
 * @Port:       Serial port to write to
 * @Data:       Data to write
 * @Length:     Number of bytes to write
 *
 * Returns the number of bytes transmitted and a less than zero
 * value if the port was not written to.
 */
SSIZE PxSerialDebugLn(PX_SERIAL_PORT Port, const CHAR *Data, USIZE Length);

#endif  /* !_PEXPERT_SERIAL_H_ */
