#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <inline_c.h>
#include <libgpu.h>
#include <libgs.h>

void func_00000774(VERT *a, VERT *b, VERT *c, GsADIV_FT3 *s);
static int func_0000087C(POLY_FT3 *p, GsADIV_FT3 *s);
static void func_000009C8(VERT *d, VERT *a, VERT *b);

static void func_000003EC(GsADIV_P_FT3 *p, GsADIV_FT3 *s, int level)
{
    POLY_FT3 *si;
    VERT *vp;
    VERT *np;
    VECTOR tmp;

    vp = p->vt;
    np = (VERT *)(++p);

    gte_ldv3(&vp[0], &vp[1], &vp[2]);
    gte_rtpt();

    si = &s->si;
    *(u_short *)&si->u0 = *(u_short *)&vp[0].tu;
    *(u_short *)&si->u1 = *(u_short *)&vp[1].tu;
    *(u_short *)&si->u2 = *(u_short *)&vp[2].tu;
    gte_stflg(&s->flg);

    gte_stsxy3_ft3(si);
    gte_avsz3();
    gte_stszotz(&s->otz);

    if (func_0000087C(si, s) != 0) {
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
    s->pk[1] = *(u_long *)&si->r0;
    s->pk[2] = *(u_long *)&si->x0;
    s->pk[3] = *(u_long *)&si->u0;
    s->pk[4] = *(u_long *)&si->x1;
    s->pk[5] = *(u_long *)&si->u1;
    s->pk[6] = *(u_long *)&si->x2;
    s->pk[7] = *(u_long *)&si->u2;
    s->tag = &s->org[s->otz >> s->shift];
    *(u_long *)s->pk = (*(u_long *)s->tag & 0xFFFFFF) | 0x07000000;
    *(u_long *)s->tag = (u_long)s->pk & 0xFFFFFF;
    s->pk += 8;
    return;

subdiv:
    level++;
    np[0] = vp[0];
    func_000009C8(&np[1], &vp[0], &vp[1]);
    func_000009C8(&np[2], &vp[0], &vp[2]);
    func_000003EC(p, s, level);
    func_00000774(&vp[0], &vp[1], &np[1], s);

    func_000009C8(&np[0], &vp[1], &vp[2]);
    func_000003EC(p, s, level);

    np[2] = vp[1];
    func_000003EC(p, s, level);
    func_00000774(&vp[1], &vp[2], &np[0], s);

    np[1] = vp[2];
    func_000009C8(&np[2], &vp[0], &vp[2]);
    func_000003EC(p, s, level);
    func_00000774(&vp[2], &vp[0], &np[2], s);
}
