#include "common.h"

extern u32 *_AllocRestBlockTop;
extern u32 *_Candidate;
extern u32 *_max_heap;

u8 *func_000000F8(u8 *ptr, s32 bytes) {
    u32 *p;
    u32 *q;
    u32 *newp;
    s32 size;
    s32 n;
    s32 total;
    s32 extra;
    s32 step;
    u8 *ret;

    size = bytes;
    size += 3;
    size &= ~3;
    p = (u32 *) (ptr - 4);
    n = *p & ~1;
    if (n != size) {
        ret = 0;
        if (n != -2) {
            total = n;
            if (n < size) {
                q = &p[*p >> 2] + 1;
                if (*q != (u32) -2) {
                    goto scan;
                }
                extra = size - n;
                if ((((s32) ((s32) _max_heap - (s32) q) >> 2) * 4) - 8 >= extra) {
expand:
                    *p += extra;
                    newp = &q[extra >> 2];
                    _Candidate = newp;
                    _AllocRestBlockTop = newp;
                    *newp = (u32) -2;
                    _AllocRestBlockTop += 1;
                }
                goto shrink;

                do {
scan:
                    step = *q;
                    if (!(step & 1)) {
                        goto shrink;
                    }
                    step = (step & ~1) + 4;
                    total += step;
                    *p += step;
                    if (total >= size) {
                        goto shrink;
                    }
                    q = &q[*q >> 2] + 1;
                } while (*q != (u32) -2);
                extra = size - total;
                if ((((s32) ((s32) _max_heap - (s32) q) >> 2) * 4) - 8 >= extra) {
                    goto expand;
                }
            }
shrink:
            n = *p & ~1;
            if (size < n) {
                p[(size >> 2) + 1] = (n - size - 4) | 1;
                *p = size;
                goto done;
            }
            if (n < size) {
                ptr = 0;
            }
            goto done;
        }
    } else {
done:
        ret = ptr;
    }
    return ret;
}
