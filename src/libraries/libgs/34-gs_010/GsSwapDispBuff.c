#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>

extern s16 PSDOFSX;
extern s16 PSDOFSY;

void GsSwapDispBuff(void) {
    s32 temp_v0;

    temp_v0 = PSDIDX * 2;
    GsDISPENV.disp.x = (s16) *((u16 *) ((u8 *) &PSDOFSX + temp_v0));
    GsDISPENV.disp.y = (s16) *((u16 *) ((u8 *) &PSDOFSY + temp_v0));
    PutDispEnv(&GsDISPENV);
    SetDispMask(1);
    GsIncFrame();
    GsSetDrawBuffClip();
    GsSetDrawBuffOffset();
}
