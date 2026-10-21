#include "common.h"
#include <sys/types.h>
#include <libetc.h>
#include <libgte.h>
#include <libgpu.h>
#include <memory.h>
#include <stdio.h>

extern char RO_STR_000030A8[];

int ClearImage2(RECT *rect, u_char r, u_char g, u_char b) {
    unsigned long c, d;
    func_0000046C(RO_STR_000030A8, rect);
    d = (b & 0xFF) << 0x10;
    c = ((g & 0xFF) << 8) | 0x80000000;
    return ((s32 (*)(u32, RECT *, s32, s32)) D_000031F0->unk8)(D_000031F0->unkC, rect, 8, d | c | (r & 0xFF));
}
