/* library-input/psyq/LIB/LIBAPI.LIB[85] MALLOC3.OBJ */
#include "common.h"

extern u32 *_freep;

void *malloc3(u32 size) {
    s32 *p;
    s32 *q;
    s32 n;
    s32 rem;
    u32 alignment;

    alignment = size & 7;
    if (size == 0) {
        goto no_memory;
    }
    goto alignment_test;
    do {
        size++;
        alignment = size & 7;
alignment_test:
        ;
    } while (alignment != 0);
    n = ((size + 7) >> 3) + 1;
    q = (s32 *)_freep;
    p = (s32 *)*q;
    for (;;) {
        if (p[1] >= n) {
            if (p[1] == n) {
                *q = *p;
            } else {
                rem = p[1] - n;
                p[1] = rem;
                p = &p[rem * 2];
                p[1] = n;
            }
            _freep = (u32 *)q;
            return p + 2;
        }
        if (p == (s32 *)_freep) {
            goto no_memory;
        }
        q = p;
        p = (s32 *)*p;
    }
no_memory:
    return 0;
}
