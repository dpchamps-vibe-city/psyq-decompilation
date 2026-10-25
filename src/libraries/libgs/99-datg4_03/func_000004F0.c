#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <inline_c.h>
#include <libgpu.h>
#include <libgs.h>

static void func_000009BC(VERTC *a, VERTC *b, VERTC *c, GsADIV_GT4 *s);
static int func_00000AEC(POLY_GT4 *p, GsADIV_GT4 *s);
static void func_00000CA8(VERTC *d, VERTC *a, VERTC *b);

static void func_000004F0(GsADIV_P_GT4 *p, GsADIV_GT4 *s, int level)
{
    POLY_GT4 *si;
    VECTOR tmp;
    VERTC *vp;
    VERTC *np;

    vp = p->vt;
    np = (VERTC *)(++p);

    gte_ldv3(&vp[0], &vp[1], &vp[2]);
    gte_rtpt();
    si = &s->si;
    *(u_short *)&si->u0 = *(u_short *)&vp[0].tu;
    *(u_short *)&si->u1 = *(u_short *)&vp[1].tu;
    *(u_short *)&si->u2 = *(u_short *)&vp[2].tu;
    gte_stflg(&s->flg);
    gte_stsxy3_gt4(si);
    gte_ldv0(&vp[3]);
    gte_rtps();
    *(u_short *)&si->u3 = *(u_short *)&vp[3].tu;
    gte_stflg(&s->flg0);
    s->flg |= s->flg0;
    gte_stsxy(&si->x3);
    gte_avsz4();
    gte_stszotz(&s->otz);

    if (func_00000AEC(si, s) != 0) {
        return;
    }
    if (s->limit == level) {
        if (s->flg & 0x7F85E000) {
            return;
        }
    } else if (s->flg < 0 || (s->maxx - s->minx) >= s->adivw ||
               (s->maxy - s->miny) >= s->adivh) {
        goto subdiv;
    }

    s->pk[0] = *(u_long *)&si->tag;
    s->pk[1] = *(u_long *)&vp[0].col;
    s->pk[2] = *(u_long *)&si->x0;
    s->pk[3] = *(u_long *)&si->u0;
    s->pk[4] = *(u_long *)&vp[1].col;
    s->pk[5] = *(u_long *)&si->x1;
    s->pk[6] = *(u_long *)&si->u1;
    s->pk[7] = *(u_long *)&vp[2].col;
    s->pk[8] = *(u_long *)&si->x2;
    s->pk[9] = *(u_long *)&si->u2;
    s->pk[10] = *(u_long *)&vp[3].col;
    s->pk[11] = *(u_long *)&si->x3;
    s->pk[12] = *(u_long *)&si->u3;
    s->tag = &s->org[s->otz >> s->shift];
    *(u_long *)s->pk = (*(u_long *)s->tag & 0xFFFFFF) | 0x0C000000;
    *(u_long *)s->tag = (u_long)s->pk & 0xFFFFFF;
    s->pk += 0xD;
    return;

subdiv:
    level++;
    np[0] = vp[0];
    func_00000CA8(&np[1], &vp[0], &vp[1]);
    func_00000CA8(&np[2], &vp[0], &vp[2]);
    func_00000CA8(&np[3], &vp[0], &vp[3]);
    func_000009BC(&vp[0], &vp[1], &np[1], s);
    func_000004F0(p, s, level);

    np[0] = vp[1];
    func_00000CA8(&np[2], &vp[1], &vp[3]);
    func_000009BC(&vp[1], &vp[3], &np[2], s);
    func_000004F0(p, s, level);

    np[0] = vp[3];
    func_00000CA8(&np[1], &vp[3], &vp[2]);
    func_000009BC(&vp[3], &vp[2], &np[1], s);
    func_000004F0(p, s, level);

    np[0] = vp[2];
    func_00000CA8(&np[2], &vp[0], &vp[2]);
    func_000009BC(&vp[2], &vp[0], &np[2], s);
    func_000004F0(p, s, level);
}
