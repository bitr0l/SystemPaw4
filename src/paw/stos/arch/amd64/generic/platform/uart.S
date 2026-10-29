/*
 * Copyright (c) 2026, Chloe M., et al.
 * Provided under the BSD-3 clause.
 */

/* Platform COM ports */
#define PLATFORM_COM0 0x3F8

    .text
    .globl PxSerialInit
PxSerialInit:
    /*
     * The serial port is usually initialized by BIOS, we'll only find use of it
     * on this platform for emulators anyways so just return.
     */
    ret

    .globl PxSerialDebugLn
PxSerialDebugLn:
    pushfq
    cld
    mov %rdx, %rcx
    mov $PLATFORM_COM0, %dx
    rep outsb
    popfq
    retq
