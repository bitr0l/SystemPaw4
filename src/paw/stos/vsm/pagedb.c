/*
 * Copyright (c) 2026, Chloe M., et al.
 * Provided under the BSD-3 clause.
 */

#include <sys/status.h>
#include <vsm/pgdb.h>

/* Forward declarations */
static LONG PageDescCmp(PAGE_DESCRIPTOR *D0, PAGE_DESCRIPTOR *D1);

RB_PROTOTYPE(PageDb, _PAGE_DESCRIPTOR, Link, PageDescCmp)
RB_GENERATE(PageDb, _PAGE_DESCRIPTOR, Link, PageDescCmp)

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
