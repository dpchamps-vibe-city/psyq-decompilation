#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <inline_c.h>
#include <libgpu.h>
#include <libgs.h>

static void func_000003E4(GsADIV_P_G3 *p, GsADIV_G3 *s, int level);

PACKET *GsA4divG3LFG(TMD_P_G3 *op, VERT *vp, VERT *np, PACKET *pk, int n, int shift, GsOT *ot, u_long *scratch) {
    GsADIV_G3 *s;
    GsADIV_P_G3 *p;
    GsADIV_P_G3 *q;
    PACKET *a;
    long *otz;
    int i;

    s = (GsADIV_G3 *)scratch;

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
    p = (GsADIV_P_G3 *)(scratch + sizeof(GsADIV_G3) / 4);
    q = p;
    i = 0;

    if (i < n) {
    otz = &s->otz;
    do {
        gte_ldrgb(&op->r0);
        gte_ldv3(&vp[op->v0], &vp[op->v1], &vp[op->v2]);
        gte_rtpt();
        gte_stflg((u_long *)&s->flg);
        gte_nclip();
        gte_stopz(otz);
        if (s->otz > 0) {
            if ((s->flg & 0x40000) == 0) {
                gte_stsxy3_g3(a);
                gte_avsz3();
                gte_stotz(otz);
                gte_ldv3(&np[op->n0], &np[op->n1], &np[op->n2]);
                gte_ncdt();
                s->tag = &s->org[s->otz >> s->shift];
                gte_strgb3(a + 4, a + 0xC, a + 0x14);
                if (s->otz >= s->adivz && !(s->flg & 0x80000000)) {
                    *(u_long *)a = (*s->tag & 0x00FFFFFF) | 0x06000000;
                    *s->tag = (u_long)a & 0x00FFFFFF;
                    a += 0x1C;
                } else {
                    (*(VERT *)&q->vt[0].vx) = (*(VERT *)&vp[op->v0].vx);
                    (*(u_long *)&q->vt[0].col) = *(u_long *)(a + 4);
                    (*(VERT *)&q->vt[1].vx) = (*(VERT *)&vp[op->v1].vx);
                    (*(u_long *)&q->vt[1].col) = *(u_long *)(a + 0xC);
                    (*(VERT *)&q->vt[2].vx) = (*(VERT *)&vp[op->v2].vx);
                    (*(u_long *)&q->vt[2].col) = *(u_long *)(a + 0x14);
                    s->pk = (u_long *)a;
                    func_000003E4(p, s, 0);
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
