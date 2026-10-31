/* SPDX-License-Identifier: BSD-2-Clause */

/* Copyright (C) 2022-2026 Mintsuki and contributors.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef FLANTERM_FB_H
#define FLANTERM_FB_H 1

#include <stdef.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../flanterm.h"

#ifdef FLANTERM_IN_FLANTERM

#include "fb_private.h"

#endif

#define FLANTERM_FB_ROTATE_0 0
#define FLANTERM_FB_ROTATE_90 1
#define FLANTERM_FB_ROTATE_180 2
#define FLANTERM_FB_ROTATE_270 3

struct flanterm_context *flanterm_fb_init(
    /* If _malloc and _free are nulled, use the bump allocated instance (1 use only). */
    void *(*_malloc)(USIZE size),
    void (*_free)(void *ptr, USIZE size),
    ULONG *framebuffer, USIZE width, USIZE height, USIZE pitch,
    UCHAR red_mask_size, UCHAR red_mask_shift,
    UCHAR green_mask_size, UCHAR green_mask_shift,
    UCHAR blue_mask_size, UCHAR blue_mask_shift,
    ULONG *canvas, /* If nulled, no canvas. */
    ULONG *ansi_colours, ULONG *ansi_bright_colours, /* If nulled, default. */
    ULONG *default_bg, ULONG *default_fg, /* If nulled, default. */
    ULONG *default_bg_bright, ULONG *default_fg_bright, /* If nulled, default. */
    /* If font is null, use default font and font_width and font_height ignored. */
    void *font, USIZE font_width, USIZE font_height, USIZE font_spacing,
    /* If scale_x and scale_y are 0, automatically scale font based on resolution. */
    USIZE font_scale_x, USIZE font_scale_y,
    USIZE margin,
    /* One of FLANTERM_FB_ROTATE_* values. */
    int rotation
);

void flanterm_fb_set_flush_callback(struct flanterm_context *ctx, void (*flush_callback)(volatile void *address, USIZE length));

#ifdef __cplusplus
}
#endif

#endif
