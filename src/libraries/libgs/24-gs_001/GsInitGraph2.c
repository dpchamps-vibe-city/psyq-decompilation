#include "common.h"
#include <sys/types.h>
#include <libetc.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>

extern s16 PSDGPU;

void GsInitGraph2(u_short x, u_short y, u_short intmode, u_short dith, u_short vrammode) {
    GsDRAWENV.tpage = 0;
    GsDRAWENV.dtd = (u8) dith;
    GsDRAWENV.dfe = 0;
    GsDRAWENV.isbg = 0;
    GsDISPENV.disp.w = (s16) x;
    GsDISPENV.disp.h = (s16) y;
    GsDISPENV.isinter = intmode & 1;
    PSDGPU = intmode & 4;
    GsDISPENV.isrgb24 = (u8) vrammode;
    func_00000268(x & 0xFFFF, y & 0xFFFF);
}
