/*
 * Copyright (c) 2026, Chloe M., et al.
 * Provided under the BSD-3 clause.
 */

#ifndef _NUCLEUS_BAL_H_
#define _NUCLEUS_BAL_H_ 1

#include <stdef.h>

/*
 * Valid memory types
 */
typedef enum {
    MEMORY_USABLE,
    MEMORY_RESERVED,
    MEMORY_ACPI_RECLAIM,
    MEMORY_ACPI_NVS,
    MEMORY_BAD,
    MEMORY_BOOTLOADER,
    MEMORY_KERNEL,
    MEMORY_FRAMEBUFFER,
    MEMORY_ACPI_TABLES
} MEM_TYPE;

/*
 * Represents a framebuffer
 */
typedef struct {
    VOID *Address;
    UQUAD Width;
    UQUAD Height;
    UQUAD Pitch;
    SHORT Bpp;
    UCHAR RedMaskSize;
    UCHAR RedMaskShift;
    UCHAR GreenMaskSize;
    UCHAR GreenMaskShift;
    UCHAR BlueMaskSize;
    UCHAR BlueMaskShift;
} BAL_FRAMEBUFFER;

/*
 * Memory map entry
 *
 * @Base:   Entry base
 * @Length: Entry length
 * @Type:   Entry type
 */
typedef struct {
    UQUAD Base;
    UQUAD Length;
    UQUAD Type;
} MEMMAP_ENTRY;

/*
 * Represents the boot abstraction layer handle
 *
 * @DirectMap:      Direct map base
 * @MemEntryIdx:    Obtain a memory map entry by index
 * @Framebuffer:    Framebuffer information
 */
typedef struct {
    UPTR DirectMap;
    ST_STATUS(*MemEntryIdx)(USIZE Idx, MEMMAP_ENTRY *Result);
    BAL_FRAMEBUFFER Framebuffer;
} BAL_HANDLE;

/*
 * Initialize the boot abstraction layer
 */
VOID NucBalInit(VOID);

/*
 * Obtain a copy of the BAL handle
 *
 * @Result:  Result is written here
 */
VOID BalGetHandle(BAL_HANDLE *Result);

/* Backend init functions */
VOID BalLimineInit(BAL_HANDLE *Handle);

/*
 * Obtain the direct map base address
 */
ALWAYS_INLINE static inline UPTR
BalGetDirectMap(VOID)
{
    BAL_HANDLE Handle;

    BalGetHandle(&Handle);
    return Handle.DirectMap;
}

#endif  /* !_NUCLEUS_BAL_H_ */
