/*
 * Copyright (c) 2026, Chloe M., et al.
 * Provided under the BSD-3 clause.
 */

#include <nucleus/bal.h>
#include <aux/limine.h>

/* HHDM request */
static struct limine_hhdm_response *HhdmResp = NULL;
static volatile struct limine_hhdm_request HhdmReq = {
    .id = LIMINE_HHDM_REQUEST_ID,
    .revision = 0
};

/* Memory map request */
static struct limine_memmap_response *MapResp = NULL;
static volatile struct limine_memmap_request MapReq = {
    .id = LIMINE_MEMMAP_REQUEST_ID,
    .revision = 0
};

/*
 * Obtain a memory map entry by index
 *
 * @Idx:  Index of memory map entry to obtain
 * @Result: Result is written here upon success
 */
static ST_STATUS
LimineMemEntryIdx(USIZE Idx, MEMMAP_ENTRY *Result)
{
    struct limine_memmap_entry *Entry;

    if (Idx >= MapResp->entry_count) {
        return STATUS_NOT_FOUND;
    }

    Entry = MapResp->entries[Idx];
    Result->Base = Entry->base;
    Result->Length = Entry->length;
    Result->Type = Entry->type;
    return STATUS_SUCCESS;
}

VOID
BalLimineInit(BAL_HANDLE *Handle)
{
    if (Handle == NULL) {
        return;
    }

    HhdmResp = HhdmReq.response;
    MapResp = MapReq.response;
    Handle->DirectMap = HhdmResp->offset;
    Handle->MemEntryIdx = LimineMemEntryIdx;
}
