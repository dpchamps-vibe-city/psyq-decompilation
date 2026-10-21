#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

int MargePrim(void *p0, void *p1) {
    s32 len;

    len = (*(u8 *) ((u8 *) p0 + 3)) + (*(u8 *) ((u8 *) p1 + 3)) + 1;
    if (len > 0x10) {
        return -1;
    }
    (*(u8 *) ((u8 *) p0 + 3)) = (u8) len;
    (*(s32 *) ((u8 *) p1 + 0)) = 0;
    return 0;
}
