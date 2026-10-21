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

extern char RO_STR_000030CC[];
extern s32 *D_00003300;
extern s32 *D_0000330C;
extern s32 D_00003334;
extern s32 D_00003338;
extern GpuDispatch *D_000031F0;

int MoveImage2(RECT *rect, int x, int y) {
    func_0000046C(RO_STR_000030CC, rect);
    D_00003334 = VSync(-1) + 0xF0;
    D_00003338 = 0;
    while ((*(volatile s32 *) D_0000330C & 0x01000000) || !((*(volatile s32 *) D_00003300 & 0x04000000))) {
        if (func_0000293C() != 0) {
            return -1;
        }
    }
    DMACallback(2, _GPU_ResetCallback);
    if (rect->w == 0 || rect->h == 0) {
        return -1;
    }
    D_00003298.x = *(u32 *) &rect->x;
    D_00003298.y = (y << 16) | (x & 0xFFFF);
    D_00003298.z = *(u32 *) &rect->w;
    ((void (*)(void *)) D_000031F0->unk18)((u8 *) &D_00003298 - 8);
    return 0;
}
