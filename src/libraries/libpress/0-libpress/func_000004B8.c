#include "common.h"
#include <sys/types.h>
#include <libetc.h>
#include <libpress.h>
#include <stdio.h>

static int func_000005D8(void);
extern u_long **D_00000874;
extern s32 *D_00000878;
extern volatile u_long *D_0000087C;
extern s32 *D_000008A0;

static void func_000004B8(u_long *buf, int size) {
    func_000005D8();
    *D_000008A0 |= 0x88;
    *D_0000087C = 0;
    *D_00000874 = buf;
    *D_00000878 = (((u32) size >> 5) << 0x10) | 0x20;
    *D_0000087C = 0x01000200;
}
