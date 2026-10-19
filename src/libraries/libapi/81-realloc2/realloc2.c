/* Original TU: library-input/psyq/LIB/LIBAPI.LIB[81] REALLOC2.OBJ
 * sha256: 5929aa526a5c6872d4e3c96d3c54ab5959f625a40c8b9ecb3cca24e3ebf2230b
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: realloc2
 */
#include "common.h"
#include "include_asm.h"

#include "common.h"

extern void free2(void *);
extern u8 *malloc2(s32);
static u8 *func_000000F8(u8 *arg0, s32 arg1);
static u8 *func_00000280(u8 *arg0, u8 *arg1, s32 arg2);

u8 *realloc2(u8 *ptr, s32 size) {
    u8 *newptr;

    if (ptr == 0) {
        newptr = malloc2(size);
    } else if (size != 0) {
        newptr = func_000000F8(ptr, size);
        if (newptr == 0) {
            newptr = malloc2(size);
            if (newptr != 0) {
                func_00000280(ptr, newptr, size);
                free2(ptr);
            }
        }
    } else {
        free2(ptr);
    }
    return newptr;
}
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
#include "common.h"

static u8 *func_00000280(u8 *arg0, u8 *arg1, s32 arg2) {
    s32 var_a2;
    u8 *temp_v1;
    u8 *var_a0;
    u8 *var_a1;
    u8 *var_v0;
    u8 temp_v0;

    var_a0 = arg0;
    var_a1 = arg1;
    var_a2 = arg2;
    var_v0 = 0;
    if (var_a0 != 0) {
        temp_v1 = var_a0;
        if (var_a2 != 0) {
            do {
                temp_v0 = *var_a0;
                var_a0 += 1;
                var_a2 -= 1;
                *var_a1 = temp_v0;
                var_a1 += 1;
            } while (var_a2 != 0);
        }
        var_v0 = temp_v1;
    }
    return var_v0;
}
