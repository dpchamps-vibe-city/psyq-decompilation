/* Original TU: library-input/psyq/LIB/LIBAPI.LIB[81] REALLOC2.OBJ */
#include "common.h"

extern void free2(void *);
extern u8 *malloc2(s32);
static u8 *try_resize(u8 *ptr, s32 bytes);
static u8 *copy_bytes(u8 *from, u8 *to, s32 n);

u8 *realloc2(u8 *ptr, s32 size) {
    u8 *newptr;

    if (ptr == 0) {
        newptr = malloc2(size);
    } else if (size != 0) {
        newptr = try_resize(ptr, size);
        if (newptr == 0) {
            newptr = malloc2(size);
            if (newptr != 0) {
                copy_bytes(ptr, newptr, size);
                free2(ptr);
            }
        }
    } else {
        free2(ptr);
    }
    return newptr;
}

extern u32 *_AllocRestBlockTop;
extern u32 *_Candidate;
extern u32 *_max_heap;

static u8 *try_resize(u8 *ptr, s32 bytes) {
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
static u8 *copy_bytes(u8 *from, u8 *to, s32 n) {
    s32 cnt;
    u8 *save_from;
    u8 *p;
    u8 *q;
    u8 *ret;
    u8 b;

    p = from;
    q = to;
    cnt = n;
    ret = 0;
    if (p != 0) {
        save_from = p;
        if (cnt != 0) {
            do {
                b = *p;
                p += 1;
                cnt -= 1;
                *q = b;
                q += 1;
            } while (cnt != 0);
        }
        ret = save_from;
    }
    return ret;
}
