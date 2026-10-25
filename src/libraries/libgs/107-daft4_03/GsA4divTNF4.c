#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <inline_c.h>
#include <libgpu.h>
#include <libgs.h>

static void func_00000478(GsADIV_P_FT4 *p, GsADIV_FT4 *s, int level);

PACKET *GsA4divTNF4(TMD_P_TNF4 *op, VERT *vp, PACKET *pk, int n, int shift, GsOT *ot, u_long *scratch)
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

    s = (GsADIV_FT4 *)scratch;
    p = (GsADIV_P_FT4 *)(scratch + sizeof(GsADIV_FT4) / 4);
    q = p;
    s->org = (u_long *)ot->org;
    s->shift = shift;
    s->adivz = GsADIVZ;
    s->adivw = GsADIVW;
    s->adivh = GsADIVH;
    s->pk = (u_long *)pk;
    s->hwd0 = HWD0 / 2;
    s->vwd0 = VWD0 / 2;
    s->si.code = op->cd & 0xFE;
    a = (PACKET *)s->pk;
    for (i = 0; i < n; i++, op++) {
            otz = &s->otz;
            t1 = 0x40000;
            tagmask = 0xFFFFFF;
            t0 = 0x80000000;
            gte_ldv3(&vp[op->v0], &vp[op->v1], &vp[op->v2]);
            gte_rtpt();
            *(u_long *)(a + 0x0C) = *(u_long *)&op->tu0;
            *(u_long *)(a + 0x14) = *(u_long *)&op->tu1;
            gte_stflg((u_long *)&s->flg0);
            gte_nclip();
            *(u_long *)(a + 0x1C) = *(u_long *)&op->tu2;
            gte_stopz(otz);
            if (s->otz > 0) {
                gte_stsxy3_ft4(a);
                gte_ldv0(&vp[op->v3]);
                gte_rtps();
                *(u_long *)(a + 0x24) = *(u_long *)&op->tu3;
                gte_stflg((u_long *)&s->flg);
                if ((s->flg & t1) == 0 || (s->flg0 & t1) == 0) {
                    gte_stsxy(a + 0x20);
                    gte_avsz4();
                    *(u_long *)(a + 4) = ((op->cd & 0xFE) << 24) | (*(u_long *)&op->r0 & tagmask);
                    gte_stotz(otz);
                    s->tag = &s->org[s->otz >> s->shift];
                    if (s->otz >= s->adivz && !(s->flg0 & t0) && !(s->flg & t0)) {
                        *(u_long *)a = (*(u_long *)s->tag & tagmask) | 0x09000000;
                        *(u_long *)s->tag = (u_long)a & tagmask;
                        a += 0x28;
                    } else {
                        *(u_long *)&s->si.r0 = *(u_long *)(a + 4);
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
                        func_00000478(p, s, 0);
                        a = (PACKET *)s->pk;
                    }
                }
            }
    }
    s->pk = (u_long *)a;
    return a;
}
