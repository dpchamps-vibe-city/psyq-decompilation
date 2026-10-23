#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>

extern s16 PSDOFSX;
extern s16 PSDOFSY;

DRAWENV *GsSetClip2(RECT *clip) {
    s32 ofs;
    s32 x;
    s32 y;

    ofs = PSDIDX * 2;
    x = clip->x + *((s16 *) ((u8 *) &PSDOFSX + ofs));
    y = clip->y + *((s16 *) ((u8 *) &PSDOFSY + ofs));
    GsDRAWENV.clip.x = x;
    GsDRAWENV.clip.y = y;
    GsDRAWENV.clip.w = (s16) (u16) clip->w;
    GsDRAWENV.clip.h = (s16) (u16) clip->h;
    return &GsDRAWENV;
}
