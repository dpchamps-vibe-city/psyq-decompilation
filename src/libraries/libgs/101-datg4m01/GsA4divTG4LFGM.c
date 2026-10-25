INCLUDE_ASM("build/libraries/nonmatchings/libgs_101", GsA4divTG4LFGM);


/* PARKED by /auto_decompilation_loop on 2026-10-25T20:24:55.882Z.
 * Reason: escalation-exhausted.
 * Escalation reached: gpt-6.1-sol.
 * The best non-matching attempt is preserved verbatim below, disabled.
 * Findings and the decision needed: notes/human-needed-approvals/libgs_101::GsA4divTG4LFGM.md
 */

#if 0
/* Best non-matching attempt, preserved for the next session. */
#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <inline_c.h>
#include <libgpu.h>
#include <libgs.h>

static void func_00000680(GsADIV_P_GT4 *p, GsADIV_GT4 *s, int level);

PACKET *GsA4divTG4LFGM(TMD_P_TG4 *op, VERT *vp, VERT *np, PACKET *pk, int n, int shift, GsOT *ot, u_long *scratch) {
    GsADIV_GT4 *s;
    GsADIV_P_GT4 *p;
    GsADIV_P_GT4 *q;
    TMD_P_TG4 *tp;
    PACKET *a;
    long *otz;
    u_long t0;
    u_long t1;
    u_long tagmask;
    int i;
    int u0;
    int u3;
    int v0;
    int v3;
    int uw;
    int vh;
    int ue;
    int nu0;
    int nv0;
    int nu1;
    int nv2;
    int nvh;

    s = (GsADIV_GT4 *)scratch;
    p = (GsADIV_P_GT4 *)(scratch + sizeof(GsADIV_GT4) / 4);
    q = p;

    s->hwd0 = HWD0 / 2;
    s->vwd0 = VWD0 / 2;
    s->org = (u_long *)ot->org;
    s->shift = shift;
    s->adivz = GsADIVZ;
    s->adivw = GsADIVW;
    s->adivh = GsADIVH;
    s->pk = (u_long *)pk;
    setPolyGT4(&s->si);
    s->si.r0 = 0x80;
    s->si.g0 = 0x80;
    s->si.b0 = 0x80;
    s->si.r1 = 0x80;
    s->si.g1 = 0x80;
    s->si.b1 = 0x80;
    s->si.r2 = 0x80;
    s->si.g2 = 0x80;
    s->si.b2 = 0x80;
    s->si.r3 = 0x80;
    s->si.g3 = 0x80;
    s->si.b3 = 0x80;
    gte_SetRGBcd(&s->si.r0);

    a = (PACKET *)s->pk;
    tp = op;

    for (i = 0; i < n; i++, tp++) {
            otz = &s->otz;
            t1 = 0x40000;
            t0 = 0x80000000;
            tagmask = 0xFFFFFF;
            gte_ldv3(&vp[tp->v0], &vp[tp->v1], &vp[tp->v2]);
            gte_rtpt();
            *(u_long *)(a + 0x0C) = *(u_long *)&tp->tu0;
            *(u_long *)(a + 0x24) = *(u_long *)&tp->tu2;
            gte_stflg((u_long *)&s->flg0);
            gte_nclip();
            *(u_long *)(a + 0x30) = *(u_long *)&tp->tu3;
            gte_stopz(otz);
            if (s->otz > 0) {
                gte_stsxy3_gt4(a);
                gte_ldv0(&vp[tp->v3]);
                gte_rtps();
                *(u_long *)(a + 0x18) = *(u_long *)&tp->tu1;
                gte_stflg((u_long *)&s->flg);
                if ((s->flg & t1) == 0 || (s->flg0 & t1) == 0) {
                    gte_stsxy(a + 0x2C);

                    u0 = a[0x0C];
                    u3 = a[0x30];
                    v0 = a[0x0D];
                    v3 = a[0x31];
                    uw = (u3 - u0 + 1) & 0xFFFE;
                    vh = (v3 - v0 + 1) & 0xFFFE;
                    u0 += uw;

                    if (s->otz < (uw * vh) >> 6) {
                        uw >>= 3;
                        u0 += uw;
                        v0 += vh >> 1;
                        vh >>= 3;
                        v0 += vh;
                        uw--;
                        uw += u0;
                        vh--;
                        nvh = v0 + vh;
                        a[0x0D] = v0;
                        a[0x19] = v0;
                        a[0x0C] = u0;
                        a[0x18] = uw;
                        a[0x24] = u0;
                        a[0x25] = nvh;
                        a[0x30] = uw;
                        a[0x31] = nvh;
                    } else if (s->otz < (uw * vh) >> 4) {
                        nu0 = u0 + (uw >> 2);
                        nv0 = v0 + (vh >> 1);
                        nu1 = nu0 + ((uw >> 2) - 1);
                        nv2 = nv0 + ((vh >> 2) - 1);
                        a[0x0C] = nu0;
                        a[0x24] = nu0;
                        a[0x0D] = nv0;
                        a[0x19] = nv0;
                        a[0x18] = nu1;
                        a[0x25] = nv2;
                        a[0x30] = nu1;
                        a[0x31] = nv2;
                    } else if (s->otz < (uw * vh) >> 2) {
                        uw >>= 1;
                        uw--;
                        uw += u0;
                        vh >>= 1;
                        vh--;
                        nvh = v0 + vh;
                        a[0x0C] = u0;
                        a[0x0D] = v0;
                        a[0x18] = uw;
                        a[0x19] = v0;
                        a[0x24] = u0;
                        a[0x25] = nvh;
                        a[0x30] = uw;
                        a[0x31] = nvh;
                    }

                    gte_avsz4();
                    gte_stotz(otz);
                    gte_ldv3(&np[tp->n0], &np[tp->n1], &np[tp->n2]);
                    gte_ncdt();
                    s->tag = &s->org[s->otz >> s->shift];
                    gte_strgb3(a + 4, a + 0x10, a + 0x1C);
                    gte_ldv0(&np[tp->n3]);
                    gte_ncds();
                    gte_strgb(a + 0x28);
                    if (s->otz >= s->adivz && !(s->flg0 & t0) && !(s->flg & t0)) {
                        *(u_long *)a = (*(u_long *)s->tag & tagmask) | 0x0C000000;
                        *(u_long *)s->tag = (u_long)a & tagmask;
                        a += 0x34;
                    } else {
                        *(VERT *)&q->vt[0] = vp[tp->v0];
                        *(u_long *)&q->vt[0].col = *(u_long *)(a + 4);
                        *(VERT *)&q->vt[1] = vp[tp->v1];
                        *(u_long *)&q->vt[1].col = *(u_long *)(a + 0x10);
                        *(VERT *)&q->vt[2] = vp[tp->v2];
                        *(u_long *)&q->vt[2].col = *(u_long *)(a + 0x1C);
                        *(VERT *)&q->vt[3] = vp[tp->v3];
                        *(u_long *)&q->vt[3].col = *(u_long *)(a + 0x28);
                        *(u_short *)&q->vt[0].tu = *(u_short *)&tp->tu0;
                        *(u_short *)&q->vt[1].tu = *(u_short *)&tp->tu1;
                        *(u_short *)&q->vt[2].tu = *(u_short *)&tp->tu2;
                        *(u_short *)&q->vt[3].tu = *(u_short *)&tp->tu3;
                        s->si.clut = tp->clut;
                        s->si.tpage = tp->tpage;
                        s->pk = (u_long *)a;
                        func_00000680(p, s, 0);
                        a = (PACKET *)s->pk;
                    }
                }
            }
    }
    s->pk = (u_long *)a;
    return a;
}
#endif
