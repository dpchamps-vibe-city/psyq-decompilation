#include "common.h"
#include <sys/types.h>
#include <libgte.h>

extern s16 GsORGOFSX;
extern s16 GsORGOFSY;

/* POLY_FT4 payload (the primitive's tag word is not part of this pointer). */
typedef struct {
    u_char r0, g0, b0, code;
    short x0, y0;
    u_char u0, v0;
    u_short clut;
    short x1, y1;
    u_char u1, v1;
    u_short tpage;
    short x2, y2;
    u_char u2, v2;
    u_short pad1;
    short x3, y3;
    u_char u3, v3;
    u_short pad2;
} FT4;

void _mk_xpndsp(void *arg0, GsSPKT *arg1, MATRIX *arg2, void *arg3) {
    SVECTOR sv;
    VECTOR vec;
    int u[4];
    int v[4];
    int pad[8];
    int xofs;
    int yofs;
    int t;
    int t3;

    xofs = arg1->x + GsORGOFSX;
    yofs = arg1->y + GsORGOFSY;
    if (arg1->flag & 1) {
        t = (arg1->v + (s16) arg1->h) - 1;
        v[1] = t;
        v[0] = t;
        t3 = arg1->v;
        v[3] = t3;
    } else {
        t = arg1->v;
        v[1] = t;
        v[0] = t;
        t3 = (arg1->v + (s16) arg1->h) - 1;
        v[3] = t3;
    }
    v[2] = t3;
    if (arg1->flag & 2) {
        t = (arg1->u + (s16) arg1->w) - 1;
        u[2] = t;
        u[0] = t;
        t3 = arg1->u;
        u[3] = t3;
    } else {
        t = arg1->u;
        u[2] = t;
        u[0] = t;
        t3 = (arg1->u + (s16) arg1->w) - 1;
        u[3] = t3;
    }
    u[1] = t3;
    ((FT4 *) arg0)->code = arg1->code;
    ((FT4 *) arg0)->r0 = arg1->r;
    ((FT4 *) arg0)->g0 = arg1->g;
    ((FT4 *) arg0)->b0 = arg1->b;
    ((FT4 *) arg0)->tpage = arg1->tpage;
    ((FT4 *) arg0)->clut = arg1->cba;
    sv.vx = arg1->mx;
    sv.vy = arg1->my;
    sv.vz = 0;
    ApplyMatrix(arg2, &sv, &vec);
    ((FT4 *) arg0)->x0 = (u16) vec.vx + xofs;
    ((FT4 *) arg0)->y0 = (u16) vec.vy + yofs;
    ((FT4 *) arg0)->u0 = u[0];
    ((FT4 *) arg0)->v0 = v[0];
    sv.vx = arg1->mx + arg1->w;
    ApplyMatrix(arg2, &sv, &vec);
    ((FT4 *) arg0)->x1 = (u16) vec.vx + xofs;
    ((FT4 *) arg0)->y1 = (u16) vec.vy + yofs;
    ((FT4 *) arg0)->u1 = u[1];
    ((FT4 *) arg0)->v1 = v[1];
    sv.vy = arg1->my + arg1->h;
    ApplyMatrix(arg2, &sv, &vec);
    ((FT4 *) arg0)->x3 = (u16) vec.vx + xofs;
    ((FT4 *) arg0)->y3 = (u16) vec.vy + yofs;
    ((FT4 *) arg0)->u3 = u[3];
    ((FT4 *) arg0)->v3 = v[3];
    sv.vx = arg1->mx;
    ApplyMatrix(arg2, &sv, &vec);
    ((FT4 *) arg0)->x2 = (u16) vec.vx + xofs;
    ((FT4 *) arg0)->y2 = (u16) vec.vy + yofs;
    ((FT4 *) arg0)->u2 = u[2];
    ((FT4 *) arg0)->v2 = v[2];
}
