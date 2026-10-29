#include "common.h"
#include <sys/types.h>
#include <libpress.h>

static void func_00000070(u16 *src, s16 *dest, u16 *shift, s32 swap, s32 *work);

extern s16 D_000004F0;

static s32 func_000001F4(u16 *src, u16 *dest, s32 size, s32 loop_start, s32 loop,
                  s32 swap, s32 proceed, s16 *work) {
    s16 samples[28];
    s32 workspace[28];
    u16 shift;
    s16 *smp;
    s32 *ws;
    s32 i;
    s32 out;
    s32 j;
    u16 flags;
    s32 last;
    u16 *p;
    s32 result;

    out = 0;
    last = 0;
    smp = samples;
    ws = workspace;
    shift = 0;
    if (work != 0) {
        smp = work;
        ws = (s32 *)(work + 28);
    }

    switch (proceed) {
    case ENCSPU_ENCODE_WHOLE:
    case ENCSPU_ENCODE_START:
        for (i = 0; i < 8; i++)
            dest[out++] = 0;
        break;
    case ENCSPU_ENCODE_CONTINUE:
    case ENCSPU_ENCODE_END:
        if (D_000004F0 < 0)
            return ENCSPU_ENCODE_ERROR;
        shift = D_000004F0;
        break;
    default:
        return ENCSPU_ENCODE_ERROR;
    }

    i = 0;
    p = src;
    for (;;) {
        func_00000070(p, smp, &shift, swap, ws);
        flags = 0x200;
        if (loop && loop_start >= 0 && i >= loop_start && i < loop_start + 28)
            flags = 0x600;
        if ((proceed == ENCSPU_ENCODE_WHOLE || proceed == ENCSPU_ENCODE_END) &&
            i >= size - 28) {
            last = 1;
            if (loop)
                flags |= 0x100;
        }
        dest[out++] = flags | shift;
        for (j = 0; j < 28; j += 4) {
            dest[out++] = (smp[j + 3] & 0xF000) | ((smp[j + 2] >> 4) & 0xF00) |
                          ((smp[j + 1] >> 8) & 0xF0) | ((u16)smp[j] >> 12);
        }
        i += 28;
        p += 28;
        if (i >= size)
            break;
        if (last)
            break;
    }

    if ((proceed & 3) != 0) {
        result = shift;
    } else {
        if (!loop) {
            dest[out++] = 0x700;
            for (i = 1; i < 8; i++)
                dest[out++] = 0;
        }
        result = ENCSPU_ENCODE_ERROR;
    }
    D_000004F0 = result;
    return out * 2;
}
