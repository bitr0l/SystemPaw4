/*
 * Copyright (c) 2026, Chloe M., et al.
 * Provided under the BSD-3 clause.
 */

#ifndef _SYS__NULL_H_
#define _SYS__NULL_H_ 1

#if !defined(__cplusplus)
#define NULL  ((void *)0)
#else
#if __cplusplus >= 201103L
#define NULL  nullptr
#else
#define NULL ((void *)0)
#endif  /* __cplusplus >= 201103L */
#endif  /* __cplusplus */

#endif  /* !_SYS__NULL_H_ */
