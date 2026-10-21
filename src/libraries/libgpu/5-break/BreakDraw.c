#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

extern volatile u_long *D_00000290;
extern volatile u_long *D_00000298;

u_long *BreakDraw(void) {
    u_long * volatile p;

    if (!(*D_00000298 & 0x01000000)) {
        return 0;
    }
    if (((*D_00000298 & 0x700) >> 8) != 4) {
        return (u_long *)-1;
    }
    *D_00000298 &= 0xFEFFFFFF;
    p = (u_long *)*D_00000298;
    p = (u_long *)*D_00000290;
    if (((u_long)p & 0xFFFFFF) == 0xFFFFFF) {
        return 0;
    }
    return p;
}
