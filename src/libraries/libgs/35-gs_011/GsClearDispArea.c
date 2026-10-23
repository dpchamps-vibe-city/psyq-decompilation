#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>

extern s16 PSDOFSX;
extern s16 PSDOFSY;

void GsClearDispArea(unsigned char r, unsigned char g, unsigned char b) {
    RECT rect;
    s32 ofs;

    ofs = PSDIDX * 2;
    rect.x = *((s16 *) ((u8 *) &PSDOFSX + ofs));
    rect.y = *((s16 *) ((u8 *) &PSDOFSY + ofs));
    rect.h = VWD0;
    rect.w = HWD0;
    ClearImage(&rect, r & 0xFF, g & 0xFF, b & 0xFF);
}
