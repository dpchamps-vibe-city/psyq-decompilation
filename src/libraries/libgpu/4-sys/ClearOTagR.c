#include "common.h"
#include <sys/types.h>
#include <libetc.h>
#include <libgte.h>
#include <libgpu.h>
#include <memory.h>
#include <stdio.h>

extern u8 GEnv;
extern char RO_STR_000030F0[];
extern u32 D_000032A4;
extern u_long D_000032B8;

u_long *ClearOTagR(u_long *ot, int n) {
    u_long *p;

    if ((u8) (*(u8 *) ((u8 *) &GEnv + 2)) >= 2U) {
        GPU_printf(RO_STR_000030F0, ot, n);
    }
    ((void (*)(u_long *, int)) D_000031F0->unk2C)(ot, n);
    p = &D_000032B8;
    *p = ((u_long) &D_000032A4 & 0xFFFFFF) | 0x04000000;
    *ot = (u_long) p & 0xFFFFFF;
    return ot;
}
