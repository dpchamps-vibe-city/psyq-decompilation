#include "common.h"
#include <sys/types.h>
#include <libetc.h>
#include <libgte.h>
#include <libgpu.h>
#include <memory.h>
#include <stdio.h>

extern u8 GEnv;
extern char RO_STR_00003108[];

void DrawOTag(u_long *p) {
    if ((u8) (*(u8 *) ((u8 *) &GEnv + 2)) >= 2U) {
        GPU_printf(RO_STR_00003108, p);
    }
    ((s32 (*)(u32, u_long *, s32, s32)) D_000031F0->unk8)(D_000031F0->unk18, p, 0, 0);
}
