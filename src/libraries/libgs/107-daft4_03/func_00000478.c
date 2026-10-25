#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <inline_c.h>
#include <libgpu.h>
#include <libgs.h>

void func_000008D8(VERT *a, VERT *b, VERT *c, GsADIV_FT4 *s);
int func_000009F0(POLY_FT4 *p, GsADIV_FT4 *s);
void func_00000BAC(VERT *d, VERT *a, VERT *b);

/* Retain the member-local helper while its caller is an assembly fragment. */
static void func_00000478(GsADIV_P_FT4 *p, GsADIV_FT4 *s, int level) __attribute__((unused));
static void func_00000478(GsADIV_P_FT4 *p, GsADIV_FT4 *s, int level)
{
    POLY_FT4 *si;
    VECTOR tmp;
    VERT *vp;
    VERT *np;

    vp = p->vt;
    np = (VERT *)(++p);

    gte_ldv3(&vp[0], &vp[1], &vp[2]);
    gte_rtpt();
    si = &s->si;
    *(u_short *)&si->u0 = *(u_short *)&vp[0].tu;
    *(u_short *)&si->u1 = *(u_short *)&vp[1].tu;
    *(u_short *)&si->u2 = *(u_short *)&vp[2].tu;
    gte_stflg(&s->flg);
    gte_stsxy3_ft4(si);
    gte_ldv0(&vp[3]);
    gte_rtps();
    *(u_short *)&si->u3 = *(u_short *)&vp[3].tu;
    gte_stflg(&s->flg0);
    s->flg |= s->flg0;
    gte_stsxy(&si->x3);
    gte_avsz4();
    gte_stszotz(&s->otz);

    if (func_000009F0(si, s) != 0) {
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
    s->pk[8] = *(u_long *)&si->x3;
    s->pk[9] = *(u_long *)&si->u3;
    s->tag = &s->org[s->otz >> s->shift];
    *(u_long *)s->pk = (*(u_long *)s->tag & 0xFFFFFF) | 0x09000000;
    *(u_long *)s->tag = (u_long)s->pk & 0xFFFFFF;
    s->pk += 0xA;
    return;

subdiv:
    level++;
    np[0] = vp[0];
    func_00000BAC(&np[1], &vp[0], &vp[1]);
    func_00000BAC(&np[2], &vp[0], &vp[2]);
    func_00000BAC(&np[3], &vp[0], &vp[3]);
    func_000008D8(&vp[0], &vp[1], &np[1], s);
    func_00000478(p, s, level);

    np[0] = vp[1];
    func_00000BAC(&np[2], &vp[1], &vp[3]);
    func_000008D8(&vp[1], &vp[3], &np[2], s);
    func_00000478(p, s, level);

    np[0] = vp[3];
    func_00000BAC(&np[1], &vp[3], &vp[2]);
    func_000008D8(&vp[3], &vp[2], &np[1], s);
    func_00000478(p, s, level);

    np[0] = vp[2];
    func_00000BAC(&np[2], &vp[0], &vp[2]);
    func_000008D8(&vp[2], &vp[0], &np[2], s);
    func_00000478(p, s, level);
}
