#include "common.h"
#include <sys/types.h>
#include <libetc.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>

extern MATRIX _LC;
extern GsOT_TAG B_000005D0[8];
extern volatile long HWD0, VWD0;

void func_00000268(u16 x, u16 y) {
    long q;
    s16 *m;
    s16 *pos;
    s16 *clip;
    GsOT_TAG *tag;
    GsOT_TAG *tag2;

    HWD0 = x & 0xFFFF;
    VWD0 = y & 0xFFFF;
    q = (VWD0 << 14) / HWD0;
    m = &GsIDMATRIX.m[2][2];
    m[-6] = 0;
    GsIDMATRIX.m[0][1] = 0;
    GsIDMATRIX.m[1][2] = 0;
    GsIDMATRIX.m[1][0] = 0;
    GsIDMATRIX.m[2][1] = 0;
    GsIDMATRIX.m[2][0] = 0;
    GsIDMATRIX.t[2] = 0;
    GsIDMATRIX.t[1] = 0;
    GsIDMATRIX.t[0] = 0;
    GsIDMATRIX.m[0][0] = 0x1000;
    GsIDMATRIX.m[1][1] = 0x1000;
    GsIDMATRIX.m[2][2] = 0x1000;
    GsIDMATRIX2 = GsIDMATRIX;
    GsLIGHTWSMATRIX = GsIDMATRIX;
    GsLIGHTWSMATRIX.m[2][2] = 0;
    GsLIGHTWSMATRIX.m[1][1] = 0;
    GsLIGHTWSMATRIX.m[0][0] = 0;
    _LC = GsLIGHTWSMATRIX;
    PSDBASEX[0] = 0;
    PSDBASEX[1] = 0;
    PSDBASEY[0] = 0;
    PSDBASEY[1] = 0;
    pos = (s16 *) &POSITION;
    pos[1] = 0;
    POSITION.offx = 0;
    clip = (s16 *) &CLIP2;
    clip[1] = 0;
    GsIDMATRIX2.m[1][1] = q / 3;
    CLIP2.x = 0;
    tag = B_000005D0;
    tag[0].num = 3;
    tag[1].num = 2;
    tag2 = tag + 4;
    tag2[0].num = 3;
    tag2[1].num = 2;
    PSDCNT = 1;
    CLIP2.w = *(u16 *) &HWD0;
    CLIP2.h = *(u16 *) &VWD0;
}
