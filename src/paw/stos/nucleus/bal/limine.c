/*
 * Copyright (c) 2026, Chloe M., et al.
 * Provided under the BSD-3 clause.
 */

#include <nucleus/bal.h>
#include <aux/limine.h>

#define FRAMEBUFFER FbResp->framebuffers[0]
#define TERMINAL TermResp->entries[0]

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

/* Framebuffer request */
static struct limine_framebuffer_response *FbResp = NULL;
static volatile struct limine_framebuffer_request FbReq = {
    .id = LIMINE_FRAMEBUFFER_REQUEST_ID,
    .revision = 0
};

static struct limine_flanterm_fb_init_params_response *TermResp;
static volatile struct limine_flanterm_fb_init_params_request TermReq = {
    .id = LIMINE_FLANTERM_FB_INIT_PARAMS_REQUEST_ID,
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
BpalInitFramebuffer(BAL_HANDLE *Handle)
{
    BAL_FRAMEBUFFER *Framebuffer;

    if (Handle == NULL) {
        return;
    }

    Framebuffer = &Handle->Framebuffer;
    Framebuffer->Address = FRAMEBUFFER->address;
    Framebuffer->Width = FRAMEBUFFER->width;
    Framebuffer->Height = FRAMEBUFFER->height;
    Framebuffer->Pitch = FRAMEBUFFER->pitch;
    Framebuffer->RedMaskSize = FRAMEBUFFER->red_mask_size;
    Framebuffer->RedMaskShift = FRAMEBUFFER->red_mask_shift;
    Framebuffer->GreenMaskSize = FRAMEBUFFER->green_mask_size;
    Framebuffer->GreenMaskShift = FRAMEBUFFER->green_mask_shift;
    Framebuffer->BlueMaskSize = FRAMEBUFFER->blue_mask_size;
    Framebuffer->BlueMaskShift = FRAMEBUFFER->blue_mask_shift;
}

VOID
BalLimineInit(BAL_HANDLE *Handle)
{
    if (Handle == NULL) {
        return;
    }

    HhdmResp = HhdmReq.response;
    MapResp = MapReq.response;
    FbResp = FbReq.response;
    TermResp = TermReq.response;

    BpalInitFramebuffer(Handle);
    Handle->DirectMap = HhdmResp->offset;
    Handle->MemEntryIdx = LimineMemEntryIdx;
    Handle->WsConsCanvas = TERMINAL->canvas;
    BpalInitFramebuffer(Handle);
}
