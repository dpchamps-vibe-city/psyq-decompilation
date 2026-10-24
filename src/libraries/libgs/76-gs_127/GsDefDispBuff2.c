#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>

extern s16 PSDGPU;
extern s16 PSDOFSX[2];
extern s16 PSDOFSY[2];

void GsDefDispBuff2(u_short x0, u_short y0, u_short x1, u_short y1) {
    s32 gpu;

    gpu = PSDGPU;
    PSDOFSX[0] = x0;
    PSDOFSX[1] = x1;
    PSDOFSY[0] = y0;
    PSDOFSY[1] = y1;
    if (gpu != 0) {
        PSDBASEX[0] = 0;
        PSDBASEX[1] = 0;
        PSDBASEY[0] = 0;
        PSDBASEY[1] = 0;
        return;
    }
    PSDBASEX[0] = (s16) x0;
    PSDBASEX[1] = (s16) x1;
    PSDBASEY[0] = (s16) y0;
    PSDBASEY[1] = (s16) y1;
}
