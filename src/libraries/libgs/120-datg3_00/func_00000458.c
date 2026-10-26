#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <inline_c.h>
#include <libgpu.h>
#include <libgs.h>

static void func_00000838(VERTC *a, VERTC *b, VERTC *c, GsADIV_GT3 *s);
static int func_00000958(POLY_GT3 *p, GsADIV_GT3 *s);
static void func_00000AA4(VERTC *d, VERTC *a, VERTC *b);

static void func_00000458(GsADIV_P_GT3 *p, GsADIV_GT3 *s, int level)
{
    POLY_GT3 *si;
    VERTC *vp;
    VERTC *np;
    VECTOR tmp;

    vp = p->vt;
    np = (VERTC *)(++p);

    gte_ldv3(&vp[0], &vp[1], &vp[2]);
    gte_rtpt();

    si = &s->si;
    *(u_short *)&si->u0 = *(u_short *)&vp[0].tu;
    *(u_short *)&si->u1 = *(u_short *)&vp[1].tu;
    *(u_short *)&si->u2 = *(u_short *)&vp[2].tu;
    gte_stflg(&s->flg);

    gte_stsxy3_gt3(si);
    gte_avsz3();
    gte_stszotz(&s->otz);

    if (func_00000958(si, s) != 0) {
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
    s->tag = &s->org[s->otz >> s->shift];
    *(u_long *)s->pk = (*(u_long *)s->tag & 0xFFFFFF) | 0x09000000;
    *(u_long *)s->tag = (u_long)s->pk & 0xFFFFFF;
    s->pk += 0xA;
    return;

subdiv:
    level++;
    np[0] = vp[0];
    func_00000AA4(&np[1], &vp[0], &vp[1]);
    func_00000AA4(&np[2], &vp[0], &vp[2]);
    func_00000838(&vp[0], &vp[1], &np[1], s);
    func_00000458(p, s, level);

    func_00000AA4(&np[0], &vp[1], &vp[2]);
    func_00000458(p, s, level);

    np[2] = vp[1];
    func_00000838(&vp[1], &vp[2], &np[0], s);
    func_00000458(p, s, level);

    np[1] = vp[2];
    func_00000AA4(&np[2], &vp[0], &vp[2]);
    func_00000838(&vp[2], &vp[0], &np[2], s);
    func_00000458(p, s, level);
}
