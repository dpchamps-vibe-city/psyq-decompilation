#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <inline_c.h>
#include <libgpu.h>
#include <libgs.h>

static void func_00000438(GsADIV_P_F4 *p, GsADIV_F4 *s, int level);

PACKET *GsA4divF4LFG(TMD_P_F4 *op, VERT *vp, VERT *np, PACKET *pk, int n, int shift, GsOT *ot, u_long *scratch)
{
    GsADIV_F4 *s;
    GsADIV_P_F4 *p;
    GsADIV_P_F4 *q;
    PACKET *a;
    long *otz;
    u_long t0;
    u_long t1;
    u_long tagmask;
    int i;

    s = (GsADIV_F4 *)scratch;
    p = (GsADIV_P_F4 *)(scratch + sizeof(GsADIV_F4) / 4);
    q = p;

    s->org = (u_long *)ot->org;
    s->shift = shift;
    s->adivz = GsADIVZ;
    s->adivw = GsADIVW;
    s->pk = (u_long *)pk;
    s->adivh = GsADIVH;
    s->hwd0 = HWD0 / 2;
    s->vwd0 = VWD0 / 2;
    setPolyF4(&s->si);

    a = (PACKET *)s->pk;
    i = 0;
    if (n > 0) {
        otz = &s->otz;
        t1 = 0x40000;
        t0 = 0x80000000;
        tagmask = 0xFFFFFF;
        do {
            gte_ldrgb(&op->r0);
            gte_ldv3(&vp[op->v0], &vp[op->v1], &vp[op->v2]);
            gte_rtpt();
            gte_stflg(&s->flg0);
            gte_nclip();
            gte_stopz(otz);
            if (s->otz > 0) {
                gte_ldv0(&np[op->n0]);
                gte_ncds();
                gte_stsxy3_f4(a);
                gte_ldv0(&vp[op->v3]);
                gte_rtps();
                gte_stflg(&s->flg);
                if ((s->flg & t1) == 0 || (s->flg0 & t1) == 0) {
                    gte_stsxy(a + 0x14);
                    gte_avsz4();
                    gte_stotz(otz);
                    s->tag = &s->org[s->otz >> s->shift];
                    if (s->otz >= s->adivz && !(s->flg0 & t0) && !(s->flg & t0)) {
                        *(u_long *)a = (*(u_long *)s->tag & tagmask) | 0x05000000;
                        *(u_long *)s->tag = (u_long)a & tagmask;
                        gte_strgb(a + 4);
                        a += 0x18;
                    } else {
                        gte_strgb(&s->si.r0);
                        q->vt[0] = vp[op->v0];
                        q->vt[1] = vp[op->v1];
                        q->vt[2] = vp[op->v2];
                        q->vt[3] = vp[op->v3];
                        s->pk = (u_long *)a;
                        func_00000438(p, s, 0);
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
