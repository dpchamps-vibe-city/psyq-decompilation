#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>

void GsSetClip2D(RECT *rectp) {
    CLIP2.x = (s16) (u16) rectp->x;
    CLIP2.y = (s16) (u16) rectp->y;
    CLIP2.w = (s16) (u16) rectp->w;
    CLIP2.h = (s16) (u16) rectp->h;
}
