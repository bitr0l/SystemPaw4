/*
 * Copyright (c) 2026, Chloe M., et al.
 * Provided under the BSD-3 clause.
 */

#ifndef _ACPI_TABLES_H_
#define _ACPI_TABLES_H_

#include <stdef.h>

/* MADT APIC header types */
#define APIC_TYPE_LOCAL_APIC            0
#define APIC_TYPE_IO_APIC               1
#define APIC_TYPE_INTERRUPT_OVERRIDE    2

#define OEMID_SIZE 6

typedef struct PACKED {
    CHAR Signature[4];
    ULONG Length;
    UCHAR Revision;
    UCHAR Checksum;
    CHAR Oemid[OEMID_SIZE];
    CHAR OemTableId[8];
    ULONG OemRevision;
    ULONG CreatorId;
    ULONG CreatorRevision;
} ACPI_HEADER;

typedef struct PACKED {
    UQUAD Signature;
    UCHAR Checksum;
    CHAR Oemid[OEMID_SIZE];
    UCHAR Revision;
    ULONG RsdtAddr;

    /* Reserved if revision < 2 */
    ULONG Length;
    UQUAD XsdtAddr;
    UCHAR ExtChecksum;
    UCHAR Reserved[3];
} ACPI_RSDP;

/*
 * XSDT or RSDT depending on header revision
 */
typedef struct PACKED {
    ACPI_HEADER Header;
    ULONG Table[];
} ACPI_ROOT_SDT;

typedef struct PACKED {
    ACPI_HEADER Header;
    ULONG LapicAddr;
    ULONG Flags;
} ACPI_MADT;

typedef struct PACKED {
    UCHAR Type;
    UCHAR Length;
} ACPI_APIC_HEADER;

typedef struct PACKED {
    ACPI_APIC_HEADER Header;
    UCHAR ProcessorId;
    UCHAR ApicId;
    ULONG Flags;
} ACPI_LOCAL_APIC;

typedef struct PACKED {
    ACPI_APIC_HEADER Header;
    UCHAR IoApicId;
    UCHAR Reserved;
    ULONG IoApicAddr;
    ULONG GsiBase;
} IO_APIC;

#endif  /* _ACPI_TABLES_H_ */
