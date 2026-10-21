#include "common.h"
#include <sys/types.h>
#include <libetc.h>
#include <libgte.h>
#include <libgpu.h>
#include <memory.h>
#include <stdio.h>

typedef struct {
    u32 x;
    u32 y;
    u32 z;
} MovePkt;

extern char RO_STR_000030CC[];
extern MovePkt D_00003298;

int MoveImage(RECT *rect, int x, int y) {
    func_0000046C(RO_STR_000030CC, rect);
    if (rect->w == 0 || rect->h == 0) {
        return -1;
    }
    D_00003298.x = *(u32 *) &rect->x;
    D_00003298.y = (y << 16) | (x & 0xFFFF);
    D_00003298.z = *(u32 *) &rect->w;
    return ((s32 (*)(u32, void *, s32, s32)) D_000031F0->unk8)(D_000031F0->unk18, (u8 *) &D_00003298 - 8, 0x14, 0);
}
