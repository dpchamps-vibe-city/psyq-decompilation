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

void GsSortFastSpriteArray(GsFastSprite2 *sp, int n, GsOT *ot, u_short pri) {
    u_long *p;
    u_long *tag;
    u_short *pos;
    u_short *basex;
    u_short *basey;
    u_short sx;
    u_short sy;
    u_long oldtag;
    u_long var, old, mask;

    tag = (u_long *) &ot->org[pri & 0xFFFF] - ot->offset;
    oldtag = *tag;
    *tag = (u_long) &sp->pk[PSDIDX] & 0xFFFFFF;
    var = n - 1;
    if (n & 0xFFFF) {
        do {
            pos = (u_short *) &POSITION;
            mask = 0xFFFF;
            basex = (u_short *) PSDBASEX + (1 - PSDIDX);
            basey = (u_short *) PSDBASEY + (1 - PSDIDX);
            if ((s32) sp->attribute >= 0) {
                sx = sp->x + pos[0] + basex[0];
                sy = sp->y + pos[1] + basey[0];
                p = sp->sp[PSDIDX];
                p[2] = sx | (sy << 16);
                sp = (GsFastSprite2 *) ((u_char *) sp + 0x48);
            }
            old = var;
            var += mask;
        } while (old & 0xFFFF);
    }
    p[0] = oldtag + 0x04000000;
}
