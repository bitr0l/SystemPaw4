/*
 * Copyright (c) 2026, Chloe M., et al.
 * Provided under the BSD-3 clause.
 */

#include <aux/string.h>

#if __SIZEOF_SIZE_T__ != 8
#error "64-bit only"
#else
#define WORD_SHIFT 3
#endif  /* __SIZEOF_SIZE_T__ */

VOID *
MemSet(VOID *Buffer, LONG SetValue, USIZE Length)
{
    USIZE WordCount;
    USIZE *WordBuffer = (USIZE *)Buffer;
    UCHAR *ByteBuffer = (UCHAR *)Buffer;
    USIZE Index;

    if (Buffer == NULL) {
        return NULL;
    }

    /* Fill as many words as we can */
    WordCount = Length / sizeof(*WordBuffer);
    for (Index = 0; Index < WordCount; ++Index) {
        WordBuffer[Index] = SetValue;
    }

    /* Fill residual bytes */
    Index <<= WORD_SHIFT;
    for (; Index < Length; ++Index) {
        ByteBuffer[Index] = SetValue;
    }

    return Buffer;
}
