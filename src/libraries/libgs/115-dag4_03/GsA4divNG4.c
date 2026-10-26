#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <inline_c.h>
#include <libgpu.h>
#include <libgs.h>

static void func_00000484(GsADIV_P_G4 *p, GsADIV_G4 *s, int level);

PACKET *GsA4divNG4(TMD_P_NG4 *op, VERT *vp, PACKET *pk, int n, int shift, GsOT *ot, u_long *scratch) {
    GsADIV_G4 *s;
    GsADIV_P_G4 *p;
    GsADIV_P_G4 *q;
    TMD_P_NG4 *tp;
    PACKET *a;
    u_long t0;
    u_long t1;
    u_long tagmask;
    long *otz;
    int i;

    s = (GsADIV_G4 *)scratch;

    s->hwd0 = HWD0 / 2;
    s->vwd0 = VWD0 / 2;
    i = 0;
    s->org = (u_long *)ot->org;
    s->shift = shift;
    s->adivz = GsADIVZ;
    s->adivw = GsADIVW;
    s->adivh = GsADIVH;
    s->pk = (u_long *)pk;
    s->si.code = op->cd & 0xFE;

    a = (PACKET *)s->pk;
    p = (GsADIV_P_G4 *)(scratch + sizeof(GsADIV_G4) / 4);
    q = p;
    tp = op;

    if (n > 0) {
        otz = &s->otz;
        tagmask = 0xFFFFFF;
        t1 = 0x40000;
        t0 = 0x80000000;
        do {
            gte_ldv3(&vp[tp->v0], &vp[tp->v1], &vp[tp->v2]);
            gte_rtpt();
            gte_stflg((u_long *)&s->flg0);
            gte_nclip();
            gte_stopz(otz);
            if (s->otz > 0) {
                gte_stsxy3_g4(a);
                gte_ldv0(&vp[tp->v3]);
                gte_rtps();
                *(u_long *)(a + 0x04) = ((tp->cd & 0xFE) << 24) | (*(u_long *)&tp->r0 & tagmask);
                gte_stflg((u_long *)&s->flg);
                if ((s->flg & t1) == 0 || (s->flg0 & t1) == 0) {
                    gte_stsxy(a + 0x20);
                    gte_avsz4();
                    *(u_long *)(a + 0x0C) = ((tp->cd & 0xFE) << 24) | (*(u_long *)&tp->r1 & tagmask);
                    *(u_long *)(a + 0x14) = ((tp->cd & 0xFE) << 24) | (*(u_long *)&tp->r2 & tagmask);
                    *(u_long *)(a + 0x1C) = ((tp->cd & 0xFE) << 24) | (*(u_long *)&tp->r3 & tagmask);
                    gte_stotz(otz);
                    s->tag = &s->org[s->otz >> s->shift];
                    if (s->otz >= s->adivz && !(s->flg0 & t0) && !(s->flg & t0)) {
                        *(u_long *)a = (*(u_long *)s->tag & tagmask) | 0x08000000;
                        *(u_long *)s->tag = (u_long)a & tagmask;
                        a += 0x24;
                    } else {
                        *(u_long *)&q->vt[0].col = *(u_long *)(a + 0x04);
                        *(u_long *)&q->vt[1].col = *(u_long *)(a + 0x0C);
                        *(u_long *)&q->vt[2].col = *(u_long *)(a + 0x14);
                        *(u_long *)&q->vt[3].col = *(u_long *)(a + 0x1C);
                        *(VERT *)&q->vt[0] = vp[tp->v0];
                        *(VERT *)&q->vt[1] = vp[tp->v1];
                        *(VERT *)&q->vt[2] = vp[tp->v2];
                        *(VERT *)&q->vt[3] = vp[tp->v3];
                        s->pk = (u_long *)a;
                        func_00000484(p, s, 0);
                        a = (PACKET *)s->pk;
                    }
                }
            }
            i++;
            tp++;
        } while (i < n);
    }
    s->pk = (u_long *)a;
    return a;
}
