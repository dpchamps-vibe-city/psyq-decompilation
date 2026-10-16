#include "common.h"

void *malloc2(u32);
static void *func_000000BC(s8 *, s32);

void *calloc2(s32 arg0, s32 arg1) {
    s32 size;
    s8 *p;

    size = arg1 * arg0;
    p = malloc2(size);
    if (p == 0) {
        return 0;
    }
    func_000000BC(p, size);
    return p;
}
