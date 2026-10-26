#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <inline_c.h>
#include <libgpu.h>
#include <libgs.h>

static void func_000003A0(GsADIV_P_F3 *p, GsADIV_F3 *s, int level);

PACKET *GsA4divF3L(TMD_P_F3 *op, VERT *vp, VERT *np, PACKET *pk, int n, int shift, GsOT *ot, u_long *scratch)
{
    GsADIV_F3 *s;
    GsADIV_P_F3 *p;
    GsADIV_P_F3 *q;
    PACKET *a;
    long *otz;
    u_long tagmask;
    int i;

    i = 0;
    s = (GsADIV_F3 *)scratch;
    p = (GsADIV_P_F3 *)(scratch + sizeof(GsADIV_F3) / 4);
    q = p;
    s->hwd0 = HWD0 / 2;
    s->vwd0 = VWD0 / 2;
    s->org = (u_long *)ot->org;
    s->shift = shift;
    s->adivz = GsADIVZ;
    s->adivw = GsADIVW;
    s->adivh = GsADIVH;
    s->pk = (u_long *)pk;
    setPolyF3(&s->si);

    a = (PACKET *)s->pk;
    if (i < n) {
        otz = &s->otz;
        tagmask = 0xFFFFFF;
        do {
            gte_ldrgb(&op->r0);
            gte_ldv3(&vp[op->v0], &vp[op->v1], &vp[op->v2]);
            gte_rtpt();
            gte_stflg(&s->flg);
            gte_nclip();
            gte_stopz(otz);
            if (s->otz > 0) {
                if ((s->flg & 0x40000) == 0) {
                    gte_stsxy3_f3(a);
                    gte_avsz3();
                    gte_stotz(otz);
                    gte_ldv0(&np[op->n0]);
                    gte_nccs();
                    s->tag = &s->org[s->otz >> s->shift];
                    gte_strgb(a + 4);
                    if (s->otz >= s->adivz && s->flg >= 0) {
                        *(u_long *)a = (*(u_long *)s->tag & tagmask) | 0x04000000;
                        *(u_long *)s->tag = (u_long)a & tagmask;
                        a += 0x14;
                    } else {
                        gte_strgb(&s->si.r0);
                        q->vt[0] = vp[op->v0];
                        q->vt[1] = vp[op->v1];
                        q->vt[2] = vp[op->v2];
                        s->pk = (u_long *)a;
                        func_000003A0(p, s, 0);
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
