#include "common.h"
#include <sys/types.h>
#include <libetc.h>
#include <libgte.h>
#include <libgpu.h>
#include <memory.h>
#include <stdio.h>

void DMACallback(int, void *);
void _GPU_ResetCallback(void);
s32 func_0000293C(void);

extern u8 GEnv;
extern char RO_STR_00003108[];
extern s32 *D_00003300;
extern s32 *D_0000330C;
extern s32 D_00003334;
extern s32 D_00003338;
extern GpuDispatch *D_000031F0;

int DrawOTag2(u_long *p) {
    if ((u8) (*(u8 *) ((u8 *) &GEnv + 2)) >= 2U) {
        GPU_printf(RO_STR_00003108, p);
    }
    D_00003334 = VSync(-1) + 0xF0;
    D_00003338 = 0;
    while ((*(volatile s32 *) D_0000330C & 0x01000000) || !((*(volatile s32 *) D_00003300 & 0x04000000))) {
        if (func_0000293C() != 0) {
            goto fail;
        }
    }
    goto done;
fail:
    return -1;
done:
    DMACallback(2, _GPU_ResetCallback);
    ((void (*)(u_long *)) D_000031F0->unk18)(p);
    return 0;
}
