#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <inline_c.h>
#include <libgpu.h>
#include <libgs.h>

static void func_000006F8(VERTC *a, VERTC *b, VERTC *c, GsADIV_G3 *s);
static int func_00000804(POLY_G3 *p, GsADIV_G3 *s);
static void func_00000950(VERTC *d, VERTC *a, VERTC *b);

static void func_0000036C(GsADIV_P_G3 *p, GsADIV_G3 *s, int level)
{
    POLY_G3 *si;
    VERTC *vp;
    VERTC *np;
    VECTOR tmp;

    vp = p->vt;
    np = (VERTC *)(++p);

    gte_ldv3(&vp[0], &vp[1], &vp[2]);
    gte_rtpt();

    si = &s->si;
    gte_stflg(&s->flg);

    gte_stsxy3_ft4(si);
    gte_avsz3();
    gte_stszotz(&s->otz);

    if (func_00000804(si, s) != 0) {
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
    s->pk[3] = *(u_long *)&vp[1].col;
    s->pk[4] = *(u_long *)&si->x1;
    s->pk[5] = *(u_long *)&vp[2].col;
    s->pk[6] = *(u_long *)&si->x2;
    s->tag = &s->org[s->otz >> s->shift];
    *(u_long *)s->pk = (*(u_long *)s->tag & 0xFFFFFF) | 0x06000000;
    *(u_long *)s->tag = (u_long)s->pk & 0xFFFFFF;
    s->pk += 7;
    return;

subdiv:
    level++;
    np[0] = vp[0];
    func_00000950(&np[1], &vp[0], &vp[1]);
    func_00000950(&np[2], &vp[0], &vp[2]);
    func_000006F8(&vp[0], &vp[1], &np[1], s);
    func_0000036C(p, s, level);

    func_00000950(&np[0], &vp[1], &vp[2]);
    func_0000036C(p, s, level);

    np[2] = vp[1];
    func_000006F8(&vp[1], &vp[2], &np[0], s);
    func_0000036C(p, s, level);

    np[1] = vp[2];
    func_00000950(&np[2], &vp[0], &vp[2]);
    func_000006F8(&vp[2], &vp[0], &np[2], s);
    func_0000036C(p, s, level);
}
