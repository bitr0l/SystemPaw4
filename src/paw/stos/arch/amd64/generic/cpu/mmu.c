/*
 * Copyright (c) 2026, Chloe M., et al.
 * Provided under the BSD-3 clause.
 */

#include <stdef.h>
#include <vsm/pgdef.h>
#include <rsm/physseg.h>
#include <pexpert/mmu.h>
#include <machine/mmu.h>

/* 57-bit linear addresses */
#define CR4_LA57 BIT(12)

/*
 * Safe macro to extract page size from lookup table
 */
#define MMU_PAGESIZE(PS)                \
    ((PS) >= NELEM(PageSizeTable))      \
        ? PageSizeTable[0]              \
        : PageSizeTable[(PS)]

/*
 * Represents a page table level
 */
typedef enum {
    MMU_TABLE_PML1,
    MMU_TABLE_PML2,
    MMU_TABLE_PML3,
    MMU_TABLE_PML4,
    MMU_TABLE_PML5
} PAGE_TABLE_LEVEL;

/*
 * Lookup table to convert page size identifiers into
 * actual page sizes.
 */
static USIZE PageSizeTable[] = {
    [MMU_PAGESIZE_4K] = 0x1000
};

/*
 * Returns true if the given page size is understood by us
 *
 * @PageSize:  Page size to test
 */
static inline BOOLEAN
IsPsValid(MMU_PAGESIZE PageSize)
{
    switch (PageSize) {
    case MMU_PAGESIZE_4K:
        return TRUE;
    }

    return FALSE;
}

/*
 * Obtain the toplevel index
 */
static inline PAGE_TABLE_LEVEL
GetTopLevel(VOID)
{
    UPTR Cr4;

    ASMV(
        "mov %%cr4, %0"
        : "=r" (Cr4)
        :
        : "memory"
    );

    return ISSET(Cr4, CR4_LA57)
        ? MMU_TABLE_PML5
        : MMU_TABLE_PML4;
}

/*
 * Invalidate an entry from the TLB
 *
 * @Vma: Virtual memory address to flush
 */
static inline VOID
Invlpg(UPTR Vma)
{
    ASMV(
        "invlpg (%0)"
        :
        : "r" (Vma)
        : "memory"
    );
}

/*
 * Convert protection flags to page table flags
 *
 * @Prot:  Protection flags to convert
 */
static inline UQUAD
ProtToPte(MEM_PROT Prot)
{
    UQUAD Pte = 0;

    if (ISSET(Prot, PROT_READ))
        Pte |= PTE_P;
    if (ISSET(Prot, PROT_WRITE))
        Pte |= PTE_RW;
    if (ISSET(Prot, PROT_USER))
        Pte |= PTE_US;

    return Pte;
}

/*
 * Obtain the page table index of a specific level
 *
 * @VirtualBase:  Virtual base address
 * @Level:        Level of index to extract
 */
static inline USHORT
GetTableIndex(UPTR VirtualBase, PAGE_TABLE_LEVEL Level)
{
    switch (Level) {
    case MMU_TABLE_PML5:  return (VirtualBase >> 48) & 0x1FF;
    case MMU_TABLE_PML4:  return (VirtualBase >> 39) & 0x1FF;
    case MMU_TABLE_PML3:  return (VirtualBase >> 30) & 0x1FF;
    case MMU_TABLE_PML2:  return (VirtualBase >> 21) & 0x1FF;
    case MMU_TABLE_PML1:  return (VirtualBase >> 12) & 0x1FF;
    default:
        return 0xFFFF;
    }
}

/*
 * Extract a table at a specific index
 *
 * @Vas:            Virtual address space to extract from
 * @VirtualBase:    Virtual base address
 * @Level:          Level to extract
 * @Alloc:          If true, allocate new levels if needed
 */
static inline UPTR *
GetTable(MMU_VAS *Vas, UPTR VirtualBase, PAGE_TABLE_LEVEL Level, BOOLEAN Alloc)
{
    UPTR Pma, *PageMap;
    PAGE_TABLE_LEVEL CurrentLevel;
    USHORT Index;

    if (Vas == NULL) {
        return NULL;
    }

    CurrentLevel = GetTopLevel();
    PageMap = PMA_TO_VMA((Vas->Cr3 & PTE_ADDR_MASK));

    while (CurrentLevel > Level) {
        Index = GetTableIndex(VirtualBase, CurrentLevel);

        if (ISSET(PageMap[Index], PTE_P)) {
            Pma = PageMap[Index] & PTE_ADDR_MASK;
            PageMap = PMA_TO_VMA(Pma);
            --CurrentLevel;
            continue;
        }

        if (!Alloc) {
            return NULL;
        }

        if ((Pma = RsmAllocateFrame()) == 0) {
            return NULL;
        }

        PageMap[Index] = Pma | (PTE_P | PTE_RW | PTE_US);
        PageMap = PMA_TO_VMA(Pma);
        --CurrentLevel;
    }

    return PageMap;
}

VOID
PxMmuGetVas(MMU_VAS *Result)
{
    if (Result == NULL) {
        return;
    }

    ASMV(
        "mov %%cr3, %0"
        : "=r" (Result->Cr3)
        :
        : "memory"
    );
}

VOID
PxMmuSetVas(MMU_VAS *Vas)
{
    if (Vas == NULL) {
        return;
    }

    ASMV(
        "mov %0, %%cr3"
        :
        : "r" (Vas->Cr3)
        : "memory"
    );
}

VOID
PxMmuForkVas(const MMU_VAS *Source, MMU_VAS *Dest)
{
    const UPTR *SourcePtr;
    UPTR *DestPtr;
    USIZE Index;

    if (Source == NULL || Dest == NULL) {
        return;
    }

    if ((Dest->Cr3 = RsmAllocateFrame()) == 0) {
        return;
    }

    SourcePtr = PMA_TO_VMA((Source->Cr3) & PTE_ADDR_MASK);
    DestPtr = PMA_TO_VMA((Dest->Cr3) & PTE_ADDR_MASK);

    /* Copy it */
    for (Index = 0; Index < 512; ++Index) {
        if (Index < 256) {
            DestPtr[Index] = 0;
        } else {
            DestPtr[Index] = SourcePtr[Index];
        }
    }
}

ST_STATUS
PxMmuMapPage(MMU_VAS *Vas, UPTR VmaBase, UPTR PmaBase,
    MEM_PROT Prot, MMU_PAGESIZE PageSize)
{
    USIZE PageGran;
    USHORT Index;
    UQUAD PteFlags;
    UPTR *PageTable;

    if (Vas == NULL) {
        return STATUS_INVALID_PARAM;
    }

    if (!IsPsValid(PageSize)) {
        return STATUS_INVALID_PARAM;
    }

    /* Align addresses on page boundary */
    PageGran = MMU_PAGESIZE(PageSize);
    VmaBase = ALIGN_DOWN(VmaBase, PageGran);
    PmaBase = ALIGN_DOWN(PmaBase, PageGran);

    /* Extract the page table */
    PageTable = GetTable(Vas, VmaBase, MMU_TABLE_PML1, TRUE);
    if (PageTable == NULL) {
        return STATUS_OUT_OF_RESOURCES;
    }

    PteFlags = ProtToPte(Prot);
    Index = GetTableIndex(VmaBase, MMU_TABLE_PML1);

    PageTable[Index] = PmaBase | PteFlags;
    Invlpg(VmaBase);
    return STATUS_SUCCESS;
}
