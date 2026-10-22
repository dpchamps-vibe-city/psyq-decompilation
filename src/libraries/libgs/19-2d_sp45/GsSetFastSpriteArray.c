#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>

typedef struct {
    u_long attribute;
    short x, y;
    u_long pk[2][3];
    u_long sp[2][5];
} GsFastSprite2;

void GsSetFastSpriteArray(GsFastSprite2 *sp, short x, short y, u_long col, u_char u, u_char v, u_short clutx, u_long cluty, u_char r, u_char g, u_char b) {
    SPRT *p;
    u_long attr;
    u_long cb;
    u_long tp;
    u_long c0;
    u_short clut;
    int i;
    int opk;
    int osp;

    i = 0;
    cb = col & 0x1F;
    attr = sp->attribute;
    tp = ((attr >> 17) & 0x180) | 0xE1000200;
    c0 = cb | tp | ((attr >> 23) & 0x60);
    clut = getClut(clutx, cluty);
    for (osp = 0x20, opk = 8; i < 2; osp += 20, opk += 12, i++) {
        *(u_long *)((u_char *)sp + opk + 4) = c0;
        p = (SPRT *)((u_char *)sp + osp);
        p->clut = clut;
        p->u0 = u;
        p->v0 = v;
        p->w = x;
        p->h = y;
        p->r0 = r;
        p->g0 = g;
        p->b0 = b;
    }
}
