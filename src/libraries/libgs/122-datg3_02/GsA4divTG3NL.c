#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <inline_c.h>
#include <libgpu.h>
#include <libgs.h>

static void func_000003D4(GsADIV_P_GT3 *p, GsADIV_GT3 *s, int level);

PACKET *GsA4divTG3NL(TMD_P_TG3 *op, VERT *vp, VERT *np, PACKET *pk, int n, int shift, GsOT *ot, u_long *scratch) {
    GsADIV_GT3 *s;
    GsADIV_P_GT3 *p;
    GsADIV_P_GT3 *q;
    TMD_P_TG3 *tp;
    PACKET *a;
    u_long neutral;
    long *otz;
    int i;

    s = (GsADIV_GT3 *)scratch;

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
    p = (GsADIV_P_GT3 *)(scratch + sizeof(GsADIV_GT3) / 4);
    q = p;
    tp = op;

    if (n > 0) {
    neutral = 0x808080;
    otz = &s->otz;
    do {
        gte_ldv3(&vp[tp->v0], &vp[tp->v1], &vp[tp->v2]);
        gte_rtpt();
        *(u_long *)(a + 0x0C) = *(u_long *)&tp->tu0;
        *(u_long *)(a + 0x24) = *(u_long *)&tp->tu2;
        gte_stflg((u_long *)&s->flg);
        gte_nclip();
        *(u_long *)(a + 0x10) = neutral;
        gte_stopz(otz);
        if (s->otz > 0) {
            if ((s->flg & 0x40000) == 0) {
                gte_stsxy3_gt3(a);
                gte_avsz3();
                *(u_long *)(a + 0x1C) = neutral;
                gte_stotz(otz);
                *(u_long *)(a + 0x18) = *(u_long *)&tp->tu1;
                *(u_long *)(a + 0x04) = ((u_long)tp->cd << 24) | neutral;
                s->tag = &s->org[s->otz >> s->shift];
                if (s->otz >= s->adivz && !(s->flg & 0x80000000)) {
                    *(u_long *)a = (*(u_long *)s->tag & 0xFFFFFF) | 0x09000000;
                    *(u_long *)s->tag = (u_long)a & 0xFFFFFF;
                    a += 0x28;
                } else {
                    u_long col;

                    *(VERT *)&q->vt[0] = vp[tp->v0];
                    *(VERT *)&q->vt[1] = vp[tp->v1];
                    *(VERT *)&q->vt[2] = vp[tp->v2];
                    col = ((u_long)tp->cd << 24) | neutral;
                    *(u_long *)&q->vt[2].col = col;
                    *(u_long *)&q->vt[1].col = col;
                    *(u_long *)&q->vt[0].col = col;
                    *(u_short *)&q->vt[0].tu = *(u_short *)&tp->tu0;
                    *(u_short *)&q->vt[1].tu = *(u_short *)&tp->tu1;
                    *(u_short *)&q->vt[2].tu = *(u_short *)&tp->tu2;
                    s->si.clut = tp->clut;
                    s->si.tpage = tp->tpage;
                    s->pk = (u_long *)a;
                    func_000003D4(p, s, 0);
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
