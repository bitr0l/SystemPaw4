/*
 * Copyright (c) 2026, Chloe M., et al.
 * Provided under the BSD-3 clause.
 */

#include <sys/status.h>
#include <vsm/pgdb.h>
#include <pexpert/page.h>

/* Forward declarations */
static LONG PageDescCmp(PAGE_DESCRIPTOR *D0, PAGE_DESCRIPTOR *D1);

RB_PROTOTYPE(PageDb, _PAGE_DESCRIPTOR, Link, PageDescCmp)
RB_GENERATE(PageDb, _PAGE_DESCRIPTOR, Link, PageDescCmp)

/*
 * Remove a contigous range of page descriptors from a pagedb
 *
 * @PageDb:     Page database to remove from
 * @Base:       Base descriptor to remove
 * @Count:      Number of page descriptors to remove
 */
static VOID
RemoveContiguous(PAGE_DB *PageDb, PAGE_DESCRIPTOR *Base, USIZE Count)
{
    USIZE Index;
    PAGE_DESCRIPTOR *Desc, *Prev = NULL;

    Desc = Base;
    for (Index = 0; Index <= Count; ++Index) {
        if (Prev != NULL) {
            RB_REMOVE(PageDb, &PageDb->Head, Prev);
        }

        Prev = Desc;
        Desc = RB_NEXT(PageDb, &PageDb->Head, Desc);
    }

    --PageDb->NrEntries;
}

/*
 * Compare two page descriptors
 *
 * @D0:   First page descriptor to compare
 * @D1:   Second page descriptor to compare
 */
static LONG
PageDescCmp(PAGE_DESCRIPTOR *D0, PAGE_DESCRIPTOR *D1)
{
    PAGE_INFO *Info0, *Info1;

    if (D0 == NULL || D1 == NULL) {
        return -1;
    }

    /* Get page information */
    if ((Info0 = D0->Info) == NULL)
        return -1;
    if ((Info1 = D1->Info) == NULL)
        return -1;

    return (Info0->VBasePtr < Info1->VBasePtr)
        ? -1
        : (Info0->VBasePtr > Info1->VBasePtr);
}

/*
 * TODO: Add locking
 */
ST_STATUS
VsmPageDbInsert(PAGE_DB *PageDb, PAGE_DESCRIPTOR *Desc)
{
    if (PageDb == NULL || Desc == NULL) {
        return STATUS_INVALID_PARAM;
    }

    RB_INSERT(PageDb, &PageDb->Head, Desc);
    ++PageDb->NrEntries;
    return STATUS_SUCCESS;
}

/*
 * TODO: Add locking
 */
ST_STATUS
VsmPageDbAllocate(PAGE_DB *PageDb, USIZE PageCount, PAGE_DESCRIPTOR **Result)
{
    PAGE_DESCRIPTOR *Desc, *Base = NULL;
    PAGE_INFO *Info;
    USIZE FoundDescriptors = 0;

    if (PageDb == NULL || Result == NULL) {
        return STATUS_INVALID_PARAM;
    }

    if (PageCount == 0) {
        return STATUS_INVALID_PARAM;
    }

    Desc = RB_MIN(PageDb, &PageDb->Head);
    while (Desc != NULL) {
        Info = Desc->Info;
        if (FoundDescriptors >= PageCount) {
            RemoveContiguous(PageDb, Base, PageCount);
            *Result = Base;
            return STATUS_SUCCESS;
        }

        /* TODO: Handle huge pages */
        if (Info->Size != PAGESIZE) {
            FoundDescriptors = 0;
            Base = NULL;
            continue;
        }

        if (Base == NULL) {
            Base = Desc;
        }

        ++FoundDescriptors;
        Desc = RB_NEXT(PageDb, &PageDb->Head, Desc);
    }

    return STATUS_OUT_OF_RESOURCES;
}

ST_STATUS
VsmPageDbInit(PAGE_DB *PageDb)
{
    if (PageDb == NULL) {
        return STATUS_INVALID_PARAM;
    }

    RB_INIT(&PageDb->Head);
    PageDb->NrEntries = 0;
    return STATUS_SUCCESS;
}
