/*
 * Copyright (c) 2026, Chloe M., et al.
 * Provided under the BSD-3 clause.
 */

#include <drivers/wscons/wscons.h>
#include <nucleus/bal.h>
#include "flanterm.h"
#include "flanterm_backends/fb.h"

/* Bootcons attributes */
#define DEFAULT_BG 0x000000
#define DEFAULT_FG 0x55FFFF

static BAL_FRAMEBUFFER Framebuffer;
static struct flanterm_context *FtCtx = NULL;

VOID
WsConsInit(VOID)
{
    BAL_HANDLE BalHandle;
    ULONG Fg, Bg;

    BalGetHandle(&BalHandle);
    Framebuffer = BalHandle.Framebuffer;

    Bg = DEFAULT_BG;
    Fg = DEFAULT_FG;

    FtCtx = flanterm_fb_init(
        NULL,
        NULL,
        Framebuffer.Address,
        Framebuffer.Width,
        Framebuffer.Height,
        Framebuffer.Pitch,
        Framebuffer.RedMaskSize,
        Framebuffer.RedMaskShift,
        Framebuffer.GreenMaskSize,
        Framebuffer.GreenMaskShift,
        Framebuffer.BlueMaskSize,
        Framebuffer.BlueMaskShift,
        NULL,
        NULL,
        NULL,
        &Bg,
        &Fg,
        NULL,
        NULL,
        NULL,
        0, 0, 0,
        0, 0, 0, 0
    );
}

VOID
WsConsWrite(const CHAR *String, USIZE Length)
{
    if (String == NULL) {
        return;
    }

    flanterm_write(FtCtx, String, Length);
}
