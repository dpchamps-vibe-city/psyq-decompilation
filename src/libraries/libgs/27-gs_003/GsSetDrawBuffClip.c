#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>

extern s16 PSDOFSX;
extern s16 PSDOFSY;

void GsSetDrawBuffClip(void) {
    s32 temp_a0;
    s32 temp_a1;

    temp_a0 = CLIP2.x + (&PSDOFSX)[PSDIDX];
    temp_a1 = CLIP2.y + (&PSDOFSY)[PSDIDX];
    GsDRAWENV.clip.x = temp_a0;
    GsDRAWENV.clip.y = temp_a1;
    GsDRAWENV.clip.w = (u16) CLIP2.w;
    GsDRAWENV.clip.h = (u16) CLIP2.h;
    PutDrawEnv(&GsDRAWENV);
}
