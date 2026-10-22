#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>

typedef struct {
    u_long attribute;
    u_short x, y;
    u_long pk[2][3];
    u_long sp[2][5];
} GsFastSprite2;

void GsSortFastSprite2(GsFastSprite2 *sp, u_long *work, GsOT *ot, u_short pri) {
    u_long *p;
    u_long *tag;
    u_short *pos;
    u_short *basex;
    u_short *basey;
    u_short sx;
    u_short sy;

    if ((s32) sp->attribute < 0) {
        return;
    }
    pos = (u_short *) &POSITION;
    basex = (u_short *) PSDBASEX;
    basey = (u_short *) PSDBASEY;
    sx = sp->x + pos[0] + basex[1 - PSDIDX];
    sy = sp->y + pos[1] + basey[1 - PSDIDX];
    p = sp->sp[PSDIDX];
    p[2] = sx | (sy << 16);
    tag = (u_long *) &ot->org[pri & 0xFFFF] - ot->offset;
    p[0] = *tag + 0x04000000;
    *tag = (u_long) p & 0xFFFFFF;
    p = sp->pk[PSDIDX];
    tag = (u_long *) &ot->org[pri & 0xFFFF] - ot->offset;
    p[0] = *tag + 0x01000000;
    *tag = (u_long) p & 0xFFFFFF;
}
