#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <inline_c.h>
#include <libgpu.h>
#include <libgs.h>

static void func_000003B8(GsADIV_P_FT3 *p, GsADIV_FT3 *s, int level);

PACKET *GsA4divTF3NL(TMD_P_TF3 *op, VERT *vp, VERT *np, PACKET *pk, int n, int shift, GsOT *ot, u_long *scratch)
{
    GsADIV_FT3 *s;
    GsADIV_P_FT3 *p;
    GsADIV_P_FT3 *q;
    PACKET *a;
    long *otz;
    u_long tagmask;
    int i;

    s = (GsADIV_FT3 *)scratch;
    p = (GsADIV_P_FT3 *)(scratch + sizeof(GsADIV_FT3) / 4);
    q = p;
    s->hwd0 = HWD0 / 2;
    s->vwd0 = VWD0 / 2;
    s->org = (u_long *)ot->org;
    s->shift = shift;
    s->adivz = GsADIVZ;
    s->adivw = GsADIVW;
    s->adivh = GsADIVH;
    s->pk = (u_long *)pk;
    s->si.code = op->cd;
    s->si.r0 = 0x80;
    s->si.g0 = 0x80;
    s->si.b0 = 0x80;
    gte_ldrgb(&s->si.r0);
    a = (PACKET *)s->pk;
    i = 0;
    if (n > 0) {
        otz = &s->otz;
        tagmask = 0xFFFFFF;
        do {
            gte_ldv3(&vp[op->v0], &vp[op->v1], &vp[op->v2]);
            gte_rtpt();
            *(u_long *)(a + 0x0C) = *(u_long *)&op->tu0;
            *(u_long *)(a + 0x1C) = *(u_long *)&op->tu2;
            gte_stflg(&s->flg);
            gte_nclip();
            gte_stopz(otz);
            if (s->otz > 0) {
                if ((s->flg & 0x40000) == 0) {
                    gte_stsxy3_ft3(a);
                    gte_avsz3();
                    gte_stotz(otz);
                    *(u_long *)(a + 0x14) = *(u_long *)&op->tu1;
                    s->tag = &s->org[s->otz >> s->shift];
                    *(u_long *)(a + 4) = *(u_long *)&s->si.r0;
                    if (s->otz >= s->adivz && s->flg >= 0) {
                        *(u_long *)a = (*(u_long *)s->tag & tagmask) | 0x07000000;
                        *(u_long *)s->tag = (u_long)a & tagmask;
                        a += 0x20;
                    } else {
                        q->vt[0] = vp[op->v0];
                        q->vt[1] = vp[op->v1];
                        q->vt[2] = vp[op->v2];
                        *(u_short *)&q->vt[0].tu = *(u_short *)&op->tu0;
                        *(u_short *)&q->vt[1].tu = *(u_short *)&op->tu1;
                        *(u_short *)&q->vt[2].tu = *(u_short *)&op->tu2;
                        s->si.clut = op->clut;
                        s->si.tpage = op->tpage;
                        s->pk = (u_long *)a;
                        func_000003B8(p, s, 0);
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
