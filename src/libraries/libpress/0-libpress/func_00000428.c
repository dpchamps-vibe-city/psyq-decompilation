#include "common.h"
#include <sys/types.h>
#include <libetc.h>
#include <libpress.h>
#include <stdio.h>

extern u32 **D_00000868;
extern s32 *D_0000086C;
extern s32 *D_00000870;
extern u32 *D_00000898;
extern s32 *D_000008A0;

void func_00000428(u32 *data, u32 words) {
    func_00000544();
    *D_000008A0 |= 0x88;
    *D_00000868 = data + 1;
    *D_0000086C = ((words >> 5) << 0x10) | 0x20;
    *D_00000898 = *data;
    *D_00000870 = 0x01000201;
}
