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

void GsSetDrawBuffOffset(void) {
    s16 *ox;
    s16 *oy;
    s32 xofs;
    s32 yofs;
    s32 temp_s0;
    s32 temp_s1;

    if (PSDGPU != 0) {
        GsORGOFSY = 0;
        GsORGOFSX = 0;
        GsDRAWENV.ofs[0] = (u16) POSITION.offx + (u16) (&PSDOFSX)[PSDIDX];
        GsDRAWENV.ofs[1] = (u16) POSITION.offy + (u16) (&PSDOFSY)[PSDIDX];
        PutDrawEnv((DRAWENV *) ((GsDRAWENV.ofs - 4)));
        return;
    }
    ox = &PSDOFSX;
    xofs = POSITION.offx;
    if (PSDIDX == 0) {
        ox++;
    }
    temp_s1 = xofs + *ox;
    oy = &PSDOFSY;
    yofs = POSITION.offy;
    if (PSDIDX == 0) {
        oy++;
    }
    temp_s0 = yofs + *oy;
    SetGeomOffset(temp_s1, temp_s0);
    GsORGOFSX = (s16) temp_s1;
    GsORGOFSY = (s16) temp_s0;
}
