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

#ifndef FLANTERM_PRIVATE_H
#define FLANTERM_PRIVATE_H 1

#ifndef FLANTERM_IN_FLANTERM
#error "Do not use flanterm_private.h. Use interfaces defined in flanterm.h only."
#endif

#include <stdef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define FLANTERM_MAX_ESC_VALUES 16

struct flanterm_context {
    /* internal use */

    USIZE tab_size;
    bool autoflush;
    bool cursor_enabled;
    bool scroll_enabled;
    bool control_sequence;
    bool escape;
    bool osc;
    bool osc_escape;
    bool rrr;
    bool discard_next;
    bool bold;
    bool bg_bold;
    bool reverse_video;
    bool dec_private;
    bool insert_mode;
    bool csi_unhandled;
    UQUAD code_point;
    USIZE unicode_remaining;
    UCHAR g_select;
    UCHAR charsets[2];
    USIZE current_charset;
    USIZE escape_offset;
    USIZE esc_values_i;
    USIZE saved_cursor_x;
    USIZE saved_cursor_y;
    USIZE current_primary;
    USIZE current_bg;
    USIZE scroll_top_margin;
    USIZE scroll_bottom_margin;
    ULONG esc_values[FLANTERM_MAX_ESC_VALUES];
    UQUAD oob_output;
    bool saved_state_bold;
    bool saved_state_bg_bold;
    bool saved_state_reverse_video;
    USIZE saved_state_current_charset;
    USIZE saved_state_current_primary;
    USIZE saved_state_current_bg;

    /* to be set by backend */

    USIZE rows, cols;

    void (*raw_putchar)(struct flanterm_context *, UCHAR c);
    void (*clear)(struct flanterm_context *, bool move);
    void (*set_cursor_pos)(struct flanterm_context *, USIZE x, USIZE y);
    void (*get_cursor_pos)(struct flanterm_context *, USIZE *x, USIZE *y);
    void (*set_text_fg)(struct flanterm_context *, USIZE fg);
    void (*set_text_bg)(struct flanterm_context *, USIZE bg);
    void (*set_text_fg_bright)(struct flanterm_context *, USIZE fg);
    void (*set_text_bg_bright)(struct flanterm_context *, USIZE bg);
    void (*set_text_fg_rgb)(struct flanterm_context *, ULONG fg);
    void (*set_text_bg_rgb)(struct flanterm_context *, ULONG bg);
    void (*set_text_fg_default)(struct flanterm_context *);
    void (*set_text_bg_default)(struct flanterm_context *);
    void (*set_text_fg_default_bright)(struct flanterm_context *);
    void (*set_text_bg_default_bright)(struct flanterm_context *);
    void (*move_character)(struct flanterm_context *, USIZE new_x, USIZE new_y, USIZE old_x, USIZE old_y);
    void (*scroll)(struct flanterm_context *);
    void (*revscroll)(struct flanterm_context *);
    void (*swap_palette)(struct flanterm_context *);
    void (*save_state)(struct flanterm_context *);
    void (*restore_state)(struct flanterm_context *);
    void (*double_buffer_flush)(struct flanterm_context *);
    void (*full_refresh)(struct flanterm_context *);
    void (*deinit)(struct flanterm_context *, void (*)(void *, USIZE));

    /* to be set by client */

    void (*callback)(struct flanterm_context *, UQUAD, UQUAD, UQUAD, UQUAD);
};

void flanterm_context_reinit(struct flanterm_context *ctx);

#ifdef __cplusplus
}
#endif

#endif
