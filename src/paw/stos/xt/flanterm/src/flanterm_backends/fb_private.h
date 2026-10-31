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

#ifndef FLANTERM_FB_PRIVATE_H
#define FLANTERM_FB_PRIVATE_H 1

#ifndef FLANTERM_IN_FLANTERM
#error "Do not use fb_private.h. Use interfaces defined in fb.h only."
#endif

#include <stdef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define FLANTERM_FB_FONT_GLYPHS 256

struct flanterm_fb_char {
    ULONG c;
    ULONG fg;
    ULONG bg;
};

struct flanterm_fb_queue_item {
    USIZE x, y;
    struct flanterm_fb_char c;
};

struct flanterm_fb_context {
    struct flanterm_context term;

    void (*plot_char)(struct flanterm_context *ctx, struct flanterm_fb_char *c, USIZE x, USIZE y);
    void (*flush_callback)(volatile void *address, USIZE length);

    USIZE font_width;
    USIZE font_height;
    USIZE glyph_width;
    USIZE glyph_height;

    USIZE font_scale_x;
    USIZE font_scale_y;

    USIZE offset_x, offset_y;

    volatile ULONG *framebuffer;
    USIZE pitch;
    USIZE width;
    USIZE height;
    USIZE bpp;

    UCHAR red_mask_size, red_mask_shift;
    UCHAR green_mask_size, green_mask_shift;
    UCHAR blue_mask_size, blue_mask_shift;

    int rotation;

    USIZE font_bits_size;
    UCHAR *font_bits;
    USIZE font_bool_size;
    bool *font_bool;

    ULONG ansi_colours[8];
    ULONG ansi_bright_colours[8];
    ULONG default_fg, default_bg;
    ULONG default_fg_bright, default_bg_bright;

    USIZE canvas_size;
    ULONG *canvas;

    USIZE grid_size;
    USIZE queue_size;
    USIZE map_size;

    struct flanterm_fb_char *grid;

    struct flanterm_fb_queue_item *queue;
    USIZE queue_i;

    struct flanterm_fb_queue_item **map;

    ULONG text_fg;
    ULONG text_bg;
    USIZE cursor_x;
    USIZE cursor_y;

    ULONG saved_state_text_fg;
    ULONG saved_state_text_bg;
    USIZE saved_state_cursor_x;
    USIZE saved_state_cursor_y;

    USIZE old_cursor_x;
    USIZE old_cursor_y;
};

#ifdef __cplusplus
}
#endif

#endif
