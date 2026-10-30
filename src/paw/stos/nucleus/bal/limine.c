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

VOID
BalLimineInit(BAL_HANDLE *Handle)
{
    if (Handle == NULL) {
        return;
    }

    HhdmResp = HhdmReq.response;
    Handle->DirectMap = HhdmResp->offset;
}
