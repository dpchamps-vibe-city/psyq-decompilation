#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>

extern s16 GsORGOFSX;
extern s16 GsORGOFSY;
extern s16 PSDGPU;
extern s16 PSDOFSX;
extern s16 PSDOFSY;

void GsSetOffset(long x, long y) {
    s16 *var_v0;
    s16 *var_v1;
    s32 temp_s0;
    s32 temp_s1;

    if (PSDGPU != 0) {
        GsORGOFSY = 0;
        GsORGOFSX = 0;
        GsDRAWENV.ofs[0] = (u16) (&PSDOFSX)[PSDIDX] + x;
        GsDRAWENV.ofs[1] = (u16) (&PSDOFSY)[PSDIDX] + y;
        PutDrawEnv((DRAWENV *) ((GsDRAWENV.ofs - 4)));
        return;
    }
    var_v0 = &PSDOFSX;
    if (PSDIDX == 0) {
        var_v0 = &PSDOFSX + 1;
    }
    var_v1 = &PSDOFSY;
    temp_s1 = x + *var_v0;
    if (PSDIDX == 0) {
        var_v1 = &PSDOFSY + 1;
    }
    temp_s0 = y + *var_v1;
    SetGeomOffset(temp_s1, temp_s0);
    GsORGOFSX = (s16) temp_s1;
    GsORGOFSY = (s16) temp_s0;
}
