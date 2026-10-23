#include "common.h"
#include <sys/types.h>
#include <libetc.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>

extern s16 PSDGPU;

DISPENV *func_000000E4(u16 x, u16 y, u16 intmode, u16 dith, u16 varmmode) {
    s32 temp_v0;
    s32 var_a0;
    RECT *p;
    short *q;

    var_a0 = 0;
    if (((intmode >> 4) & 3) == 3) {
        var_a0 = 3;
    }
    ResetGraph(var_a0);
    q = GsDRAWENV.ofs;
    q[1] = 0;
    q[0] = 0;
    GsDRAWENV.tw.h = 0;
    GsDRAWENV.tw.w = 0;
    GsDRAWENV.tw.y = 0;
    GsDRAWENV.tw.x = 0;
    GsDRAWENV.tpage = 0;
    GsDRAWENV.dtd = dith;
    GsDRAWENV.dfe = 0;
    GsDRAWENV.isbg = 0;
    PutDrawEnv(&GsDRAWENV);
    GsDISPENV.disp.x = 0;
    GsDISPENV.disp.y = 0;
    GsDISPENV.disp.w = x;
    GsDISPENV.disp.h = y;
    p = &GsDISPENV.screen;
    p->x = 0;
    p->y = 0;
    p->w = 0;
    p->h = 0;
    temp_v0 = GetVideoMode();
    if (temp_v0 == 1) {
        GsDISPENV.screen.y = 0x18;
        GsDISPENV.pad0 = (u8) temp_v0;
    }
    GsDISPENV.isinter = intmode & 1;
    PSDGPU = intmode & 4;
    GsDISPENV.isrgb24 = (u8) varmmode;
    return PutDispEnv(&GsDISPENV);
}
