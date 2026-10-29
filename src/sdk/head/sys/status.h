/*
 * Copyright (c) 2026, Chloe M., et al.
 * Provided under the BSD-3 clause.
 */

#ifndef _SYS_STATUS_H_
#define _SYS_STATUS_H_ 1

#include <sys/types.h>

/*
 * All slut technology status codes are to be of this type, below is
 * a listing of values that are valid for this type.
 */
typedef ULONG ST_STATUS;

/* Valid status codes */
#define STATUS_SUCCESS          0x00000000      /* Successful */
#define STATUS_NOT_FOUND        0x00000001      /* Resource not found */
#define STATUS_INVALID_PARAM    0x00000002      /* Invalid parameter */
#define STATUS_IS_FULL          0x00000003      /* Resource is full */
#define STATUS_NAME_TOO_LONG    0x00000004      /* Name is too long */

#endif  /* !_SYS_STATUS_H_ */
