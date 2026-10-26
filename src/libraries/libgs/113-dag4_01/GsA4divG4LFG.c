#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <inline_c.h>
#include <libgpu.h>
#include <libgs.h>

static void func_000004C8(GsADIV_P_G4 *p, GsADIV_G4 *s, int level);

PACKET *GsA4divG4LFG(TMD_P_G4 *op, VERT *vp, VERT *np, PACKET *pk, int n, int shift, GsOT *ot, u_long *scratch) {
    GsADIV_G4 *s;
    GsADIV_P_G4 *p;
    GsADIV_P_G4 *q;
    PACKET *a;
    long *otz;
    u_long t0;
    u_long t1;
    u_long tagmask;
    int i;

    s = (GsADIV_G4 *)scratch;

    s->hwd0 = HWD0 / 2;
    s->vwd0 = VWD0 / 2;
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
    for (i = 0; i < n; i++, op++) {
        otz = &s->otz;
        t1 = 0x40000;
        t0 = 0x80000000;
        tagmask = 0xFFFFFF;
        gte_ldrgb(&op->r0);
        gte_ldv3(&vp[op->v0], &vp[op->v1], &vp[op->v2]);
        gte_rtpt();
        gte_stflg((u_long *)&s->flg0);
        gte_nclip();
        gte_stopz(otz);
        if (s->otz > 0) {
            gte_stsxy3_g4(a);
            gte_ldv0(&vp[op->v3]);
            gte_rtps();
            gte_stflg((u_long *)&s->flg);
            if ((s->flg & t1) == 0 || (s->flg0 & t1) == 0) {
                gte_stsxy(a + 0x20);
                gte_avsz4();
                gte_stotz(otz);
                gte_ldv3(&np[op->n0], &np[op->n1], &np[op->n2]);
                gte_ncdt();
                s->tag = &s->org[s->otz >> s->shift];
                gte_strgb3(a + 0x4, a + 0xC, a + 0x14);
                gte_ldv0(&np[op->n3]);
                gte_ncds();
                gte_strgb(a + 0x1C);
                if (s->otz >= s->adivz && !(s->flg0 & t0) && !(s->flg & t0)) {
                    *(u_long *)a = (*(u_long *)s->tag & tagmask) | 0x08000000;
                    *(u_long *)s->tag = (u_long)a & tagmask;
                    a += 0x24;
                } else {
                    *(VERT *)&q->vt[0] = vp[op->v0];
                    *(u_long *)&q->vt[0].col = *(u_long *)(a + 0x4);
                    *(VERT *)&q->vt[1] = vp[op->v1];
                    *(u_long *)&q->vt[1].col = *(u_long *)(a + 0xC);
                    *(VERT *)&q->vt[2] = vp[op->v2];
                    *(u_long *)&q->vt[2].col = *(u_long *)(a + 0x14);
                    *(VERT *)&q->vt[3] = vp[op->v3];
                    *(u_long *)&q->vt[3].col = *(u_long *)(a + 0x1C);
                    s->pk = (u_long *)a;
                    func_000004C8(p, s, 0);
                    a = (PACKET *)s->pk;
                }
            }
        }
    }
    s->pk = (u_long *)a;
    return a;
}
