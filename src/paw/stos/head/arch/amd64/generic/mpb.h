/*
 * Copyright (c) 2026, Chloe M., et al.
 * Provided under the BSD-3 clause.
 */

#ifndef _MACHINE_MPB_H_
#define _MACHINE_MPB_H_ 1

/*
 * Valid processor vendors
 */
typedef enum {
    CPU_VENDOR_UNKNOWN,
    CPU_VENDOR_INTEL,
    CPU_VENDOR_UMC,
    CPU_VENDOR_AMD
} CPU_VENDOR;

/*
 * Represents the machine processor block which contains machine
 * specific processor information.
 *
 * @Vendor:     Processor OEM
 * @Model:      Processor model number
 * @Family:     Family ID
 * @ExtModel:   Processor extended model number
 */
typedef struct {
    CPU_VENDOR Vendor;
    UCHAR Model    : 4;
    UCHAR Family   : 4;
    UCHAR ExtModel : 4;
} MPB;

#endif  /* !_MACHINE_MPB_H_ */
