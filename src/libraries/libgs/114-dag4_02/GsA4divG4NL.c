#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <inline_c.h>
#include <libgpu.h>
#include <libgs.h>

static void func_0000042C(GsADIV_P_G4 *p, GsADIV_G4 *s, int level);

PACKET *GsA4divG4NL(TMD_P_G4 *op, VERT *vp, VERT *np, PACKET *pk, int n, int shift, GsOT *ot, u_long *scratch) {
    GsADIV_G4 *s;
    GsADIV_P_G4 *p;
    GsADIV_P_G4 *q;
    TMD_P_G4 *tp;
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
    s->si.code = op->cd;

    a = (PACKET *)s->pk;
    p = (GsADIV_P_G4 *)(scratch + sizeof(GsADIV_G4) / 4);
    q = p;
    tp = op;

    if (n > 0) {
        otz = &s->otz;
        t1 = 0x40000;
        t0 = 0x80000000;
        tagmask = 0xFFFFFF;
        do {
            gte_ldv3(&vp[tp->v0], &vp[tp->v1], &vp[tp->v2]);
            gte_rtpt();
            *(u_long *)(a + 0x04) = *(u_long *)&tp->r0;
            *(u_long *)(a + 0x0C) = *(u_long *)&tp->r0;
            gte_stflg((u_long *)&s->flg0);
            gte_nclip();
            *(u_long *)(a + 0x14) = *(u_long *)&tp->r0;
            gte_stopz(otz);
            if (s->otz > 0) {
                gte_stsxy3_g4(a);
                gte_ldv0(&vp[tp->v3]);
                gte_rtps();
                gte_stflg((u_long *)&s->flg);
                if ((s->flg & t1) == 0 || (s->flg0 & t1) == 0) {
                    gte_stsxy(a + 0x20);
                    gte_avsz4();
                    *(u_long *)(a + 0x1C) = *(u_long *)&tp->r0;
                    gte_stotz(otz);
                    s->tag = &s->org[s->otz >> s->shift];
                    if (s->otz >= s->adivz && !(s->flg0 & t0) && !(s->flg & t0)) {
                        *(u_long *)a = (*(u_long *)s->tag & tagmask) | 0x08000000;
                        *(u_long *)s->tag = (u_long)a & tagmask;
                        a += 0x24;
                    } else {
                        u_long col;

                        *(VERT *)&q->vt[0] = vp[tp->v0];
                        col = *(u_long *)&tp->r0;
                        *(u_long *)&q->vt[0].col = col;
                        *(u_long *)&q->vt[1].col = col;
                        *(u_long *)&q->vt[2].col = col;
                        *(u_long *)&q->vt[3].col = col;
                        *(VERT *)&q->vt[1] = vp[tp->v1];
                        *(VERT *)&q->vt[2] = vp[tp->v2];
                        *(VERT *)&q->vt[3] = vp[tp->v3];
                        s->pk = (u_long *)a;
                        func_0000042C(p, s, 0);
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
