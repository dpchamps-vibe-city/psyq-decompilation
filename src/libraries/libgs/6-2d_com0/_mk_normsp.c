#include "common.h"
#include <sys/types.h>
#include <libgte.h>

void _mk_normsp(void *arg0, GsSPKT *arg1, MATRIX *arg2, void *arg3) {
    int u[4];
    int v[4];
    int pad[8];
    int xofs;
    int yofs;
    int t;
    int t3;
    int i;
    int hv;
    int vv;

    xofs = arg1->x + arg1->mx + GsORGOFSX;
    yofs = arg1->y + arg1->my + GsORGOFSY;
    if (arg1->flag & 1) {
        t = (arg1->v + (s16) arg1->h) - 1;
        v[1] = t;
        v[0] = t;
        vv = arg1->v;
        t3 = vv - 1;
    } else {
        t = arg1->v;
        v[1] = t;
        v[0] = t;
        vv = arg1->v;
        hv = (s16) arg1->h;
        t3 = vv + hv;
    }
    v[3] = t3;
    v[2] = t3;
    if (arg1->flag & 2) {
        t = (arg1->u + (s16) arg1->w) - 1;
        u[2] = t;
        u[0] = t;
        vv = arg1->u;
        t3 = vv - 1;
        u[3] = t3;
    } else {
        t = arg1->u;
        u[2] = t;
        u[0] = t;
        vv = arg1->u;
        hv = (s16) arg1->w;
        t3 = vv + hv;
        u[3] = t3;
    }
    u[1] = t3;
    for (i = 0; i < 4; i++) {
        if (u[i] < 0) {
            u[i] = 0;
        }
        if (v[i] < 0) {
            v[i] = 0;
        }
        if (u[i] >= 0x100) {
            u[i] = 0xFF;
        }
        if (v[i] >= 0x100) {
            v[i] = 0xFF;
        }
    }
    ((FT4 *) arg0)->code = arg1->code;
    ((FT4 *) arg0)->r0 = arg1->r;
    ((FT4 *) arg0)->g0 = arg1->g;
    ((FT4 *) arg0)->b0 = arg1->b;
    ((FT4 *) arg0)->tpage = arg1->tpage;
    ((FT4 *) arg0)->clut = arg1->cba;
    ((FT4 *) arg0)->x0 = xofs;
    ((FT4 *) arg0)->y0 = yofs;
    ((FT4 *) arg0)->u0 = u[0];
    ((FT4 *) arg0)->v0 = v[0];
    ((FT4 *) arg0)->x1 = arg1->w + xofs;
    ((FT4 *) arg0)->y1 = yofs;
    ((FT4 *) arg0)->u1 = u[1];
    ((FT4 *) arg0)->v1 = v[1];
    ((FT4 *) arg0)->x2 = xofs;
    ((FT4 *) arg0)->y2 = arg1->h + yofs;
    ((FT4 *) arg0)->u2 = u[2];
    ((FT4 *) arg0)->v2 = v[2];
    ((FT4 *) arg0)->x3 = arg1->w + xofs;
    ((FT4 *) arg0)->y3 = arg1->h + yofs;
    ((FT4 *) arg0)->u3 = u[3];
    ((FT4 *) arg0)->v3 = v[3];
}
