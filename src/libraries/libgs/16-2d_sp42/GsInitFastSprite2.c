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

void GsInitFastSprite2(GsFastSprite2 *sp, u_long *addr, short w, short h, u_long col, u_short clut, u_char u, u_char v, u_char r, u_char g, u_char b) {
    u_long attr;
    u_long cb;
    u_long tp;
    u_long idx;
    u_long code;
    u_long c0;
    u_long c1;
    u_char len;
    u_char sprct;
    SPRT *p;
    int i;
    int opk;
    int osp;

    i = 0;
    cb = col & 0x1F;
    attr = sp->attribute;
    tp = ((attr >> 17) & 0x180) | 0xE1000200;
    c0 = cb | tp | ((attr >> 23) & 0x60);
    len = 4;
    sprct = 0x64;
    idx = (attr >> 5) & 0x02000000;
    code = ((attr << 18) & 0x01000000) | 0x64000000;
    c1 = idx | code | (b << 16) | (g << 8) | r;
    for (osp = 0x20, opk = 8; i < 2; osp += 20, opk += 12, i++) {
        *(u_long *)((u_char *)sp + opk + 4) = c0;
        p = (SPRT *)((u_char *)sp + osp);
        setlen(p, len);
        setcode(p, sprct);
        p->clut = clut;
        p->u0 = u;
        p->v0 = v;
        p->w = w;
        p->h = h;
        ((u_long *)p)[1] = c1;
    }
}
