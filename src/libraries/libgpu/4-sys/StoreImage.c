#include "common.h"
#include <sys/types.h>
#include <libetc.h>
#include <libgte.h>
#include <libgpu.h>
#include <memory.h>
#include <stdio.h>

extern char RO_STR_000030C0[];

int StoreImage(RECT *rect, u_long *p) {
    func_0000046C(RO_STR_000030C0, rect);
    return ((s32 (*)(u32, RECT *, s32, u_long *)) D_000031F0->unk8)(D_000031F0->unk1C, rect, 8, p);
}
