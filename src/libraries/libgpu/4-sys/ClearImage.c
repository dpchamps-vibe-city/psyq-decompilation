#include "common.h"
#include <sys/types.h>
#include <libetc.h>
#include <libgte.h>
#include <libgpu.h>
#include <memory.h>
#include <stdio.h>

extern char RO_STR_0000309C[];

int ClearImage(RECT *rect, u_char r, u_char g, u_char b) {
    func_0000046C(RO_STR_0000309C, rect);
    return ((s32 (*)(u32, RECT *, s32, s32)) D_000031F0->unk8)(D_000031F0->unkC, rect, 8, ((b & 0xFF) << 0x10) | ((g & 0xFF) << 8) | (r & 0xFF));
}
