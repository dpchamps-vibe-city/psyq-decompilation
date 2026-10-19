/* Original TU: CALLOC2.OBJ (LIBAPI.LIB[82]) */
#include "common.h"

void *malloc2(u32);
static void *memzero(s8 *, s32);

void *calloc2(s32 nelem, s32 elsize) {
    s32 size;
    s8 *p;

    size = elsize * nelem;
    p = malloc2(size);
    if (p == 0) {
        return 0;
    }
    memzero(p, size);
    return p;
}
static void *memzero(s8 *p, s32 n) {
    s8 *ret;

    ret = 0;
    if (p != 0) {
        ret = p;
        if (n == 0) {
            return 0;
        }
        do {
            *p = 0;
            n -= 1;
            p += 1;
        } while (n != 0);
    }
    return ret;
}
