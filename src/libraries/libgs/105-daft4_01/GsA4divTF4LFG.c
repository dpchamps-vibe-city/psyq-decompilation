#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <inline_c.h>
#include <libgpu.h>
#include <libgs.h>

static void func_0000049C(GsADIV_P_FT4 *p, GsADIV_FT4 *s, int level);

PACKET *GsA4divTF4LFG(TMD_P_TF4 *op, VERT *vp, VERT *np, PACKET *pk, int n, int shift, GsOT *ot, u_long *scratch)
{
    GsADIV_FT4 *s;
    GsADIV_P_FT4 *p;
    GsADIV_P_FT4 *q;
    PACKET *a;
    long *otz;
    u_long t0;
    u_long t1;
    u_long tagmask;
    int i;
    short adivw;
    short adivh;

    adivw = GsADIVW;
    adivh = GsADIVH;
    s = (GsADIV_FT4 *)scratch;
    p = (GsADIV_P_FT4 *)(scratch + sizeof(GsADIV_FT4) / 4);
    q = p;
    s->org = (u_long *)ot->org;
    s->shift = shift;
    s->adivw = adivw;
    s->adivh = adivh;
    s->pk = (u_long *)pk;
    s->adivz = GsADIVZ;
    s->hwd0 = HWD0 / 2;
    s->vwd0 = VWD0 / 2;
    s->si.code = op->cd;
    s->si.r0 = 0x80;
    s->si.g0 = 0x80;
    s->si.b0 = 0x80;
    gte_ldrgb(&s->si.r0);
    a = (PACKET *)s->pk;
    i = 0;
    if (n > 0) {
        otz = &s->otz;
        t1 = 0x40000;
        t0 = 0x80000000;
        tagmask = 0xFFFFFF;
        do {
            gte_ldv3(&vp[op->v0], &vp[op->v1], &vp[op->v2]);
            gte_rtpt();
            *(u_long *)(a + 0x0C) = *(u_long *)&op->tu0;
            *(u_long *)(a + 0x1C) = *(u_long *)&op->tu2;
            gte_stflg(&s->flg0);
            gte_nclip();
            *(u_long *)(a + 0x24) = *(u_long *)&op->tu3;
            gte_stopz(otz);
            if (s->otz > 0) {
                gte_ldv0(&np[op->n0]);
                gte_ncds();
                *(u_long *)(a + 0x14) = *(u_long *)&op->tu1;
                gte_stsxy3_ft4(a);
                gte_ldv0(&vp[op->v3]);
                gte_rtps();
                gte_stflg(&s->flg);
                if ((s->flg & t1) == 0 || (s->flg0 & t1) == 0) {
                    gte_stsxy(a + 0x20);
                    gte_avsz4();
                    gte_stotz(otz);
                    s->tag = &s->org[s->otz >> s->shift];
                    if (s->otz >= s->adivz && !(s->flg0 & t0) && !(s->flg & t0)) {
                        *(u_long *)a = (*(u_long *)s->tag & tagmask) | 0x09000000;
                        *(u_long *)s->tag = (u_long)a & tagmask;
                        gte_strgb(a + 4);
                        a += 0x28;
                    } else {
                        gte_strgb(&s->si.r0);
                        q->vt[0] = vp[op->v0];
                        q->vt[1] = vp[op->v1];
                        q->vt[2] = vp[op->v2];
                        q->vt[3] = vp[op->v3];
                        *(u_short *)&q->vt[0].tu = *(u_short *)&op->tu0;
                        *(u_short *)&q->vt[1].tu = *(u_short *)&op->tu1;
                        *(u_short *)&q->vt[2].tu = *(u_short *)&op->tu2;
                        *(u_short *)&q->vt[3].tu = *(u_short *)&op->tu3;
                        s->si.clut = op->clut;
                        s->si.tpage = op->tpage;
                        s->pk = (u_long *)a;
                        func_0000049C(p, s, 0);
                        a = (PACKET *)s->pk;
                    }
                }
            }
            i++;
            op++;
        } while (i < n);
    }
    s->pk = (u_long *)a;
    return a;
}
