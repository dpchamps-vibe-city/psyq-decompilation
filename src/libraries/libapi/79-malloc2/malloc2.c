/* Original TU: library-input/psyq/LIB/LIBAPI.LIB[79] MALLOC2.OBJ - sha256: 399b7fc3c128a80e42903f3ce93fc1e62ccdbf9e388183a295fb63a0ff6a5af8 */
#include "common.h"

static void *func_00000220(u32 size);

extern u32 *_AllocRestBlockTop;
extern u32 *_Candidate;
extern u32 *_TopAllocArea;

void *malloc2(u32 size) {
    u32 *p;
    u32 *q;
    u32 *ret;
    u32 s;
    u32 h;
    u32 nxt;
    void *blk;
    u32 m;
    u32 *r;
    s32 retry;

    retry = 1;
    if (size == 0) {
        return 0;
    }
    size += 3;
    size &= ~3;
    s = size | 1;
    p = _Candidate;
    if (p == 0) {
        p = _TopAllocArea;
    }
    for (;;) {
        if (*p & 1) {
            if (_Candidate == 0) {
                _Candidate = p;
            }
            h = *p;
            if (h == s) {
                *p = h & ~1;
                ret = p + 1;
                break;
            } else if (size < h) {
                r = &p[size >> 2];
                r[1] = h - size - 4;
                *p = size;
                ret = p + 1;
                break;
            } else if (h < size) {
                q = &p[h >> 2];
                nxt = q[1];
                ret = q + 1;
                if (nxt == (u32)-2) {
                    *p = (u32)-2;
                    _AllocRestBlockTop = p + 1;
                } else if (nxt & 1) {
                    m = h + 4;
                    *p = m + (nxt & ~1);
                } else {
                    p = ret;
                }
            }
        } else {
            if (*p != (u32)-2) {
                p = &p[*p >> 2] + 1;
            } else {
                blk = func_00000220(size);
                retry -= 1;
                if (blk != 0) {
                    _Candidate = _AllocRestBlockTop - 1;
                    ret = (u32 *)blk + 1;
                    break;
                } else if (retry >= 0) {
                    p = _TopAllocArea;
                    _Candidate = 0;
                    continue;
                } else {
                    ret = 0;
                    break;
                }
            }
        }
    }
    return ret;
}

extern u32 *_max_heap;

void *func_00000220(u32 size) {
    u32 *p;

    if ((u32)(((s32)((s32)_max_heap - (s32)_AllocRestBlockTop) >> 2) * 4 - 8) < size) {
        return 0;
    }
    p = _AllocRestBlockTop - 1;
    _AllocRestBlockTop[-1] = size;
    _AllocRestBlockTop = (u32 *)((u8 *)_AllocRestBlockTop + (((size >> 2) << 2) + 4));
    _AllocRestBlockTop[-1] = -2U;
    return p;
}
