INCLUDE_ASM("build/libraries/nonmatchings/libgs_112", GsA4divG4L);


/* PARKED by /auto_decompilation_loop on 2026-10-26T00:12:53.458Z.
 * Reason: escalation-exhausted.
 * Escalation reached: gpt-6.1-sol.
 * The best non-matching attempt is preserved verbatim below, disabled.
 * Findings and the decision needed: notes/human-needed-approvals/libgs_112::GsA4divG4L.md
 */

#if 0
/* Best non-matching attempt, preserved for the next session. */
#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <inline_c.h>
#include <libgpu.h>
#include <libgs.h>

static void func_000004C8(GsADIV_P_G4 *p, GsADIV_G4 *s, int level);

PACKET *GsA4divG4L(TMD_P_G4 *op, VERT *vp, VERT *np, PACKET *pk, int n, int shift, GsOT *ot, u_long *scratch) {
    GsADIV_G4 *s;
    GsADIV_P_G4 *p;
    GsADIV_P_G4 *q;
    TMD_P_G4 *tp;
    PACKET *a;
    u_long t0;
    u_long t1;
    long *otz;
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
    tp = op;
    i = 0;

    if (n > 0) {
    otz = &s->otz;
    t1 = 0x40000;
    t0 = 0x80000000;
    do {
        gte_ldrgb(&tp->r0);
        gte_ldv3(&vp[tp->v0], &vp[tp->v1], &vp[tp->v2]);
        gte_rtpt();
        gte_stflg((u_long *)&s->flg0);
        gte_nclip();
        gte_stopz(otz);
        if (s->otz > 0) {
            gte_stsxy3_g4(a);
            gte_ldv0(&vp[tp->v3]);
            gte_rtps();
            gte_stflg((u_long *)&s->flg);
            if ((s->flg & t1) == 0 || (s->flg0 & t1) == 0) {
                gte_stsxy(a + 0x20);
                gte_avsz4();
                gte_stotz(otz);
                gte_ldv3(&np[tp->n0], &np[tp->n1], &np[tp->n2]);
                gte_ncct();
                s->tag = &s->org[s->otz >> s->shift];
                gte_strgb3(a + 4, a + 0xC, a + 0x14);
                gte_ldv0(&np[tp->n3]);
                gte_nccs();
                gte_strgb(a + 0x1C);
                if (s->otz >= s->adivz && !(s->flg0 & t0) && !(s->flg & t0)) {
                    *(u_long *)a = (*s->tag & 0x00FFFFFF) | 0x08000000;
                    *s->tag = (u_long)a & 0x00FFFFFF;
                    a += 0x24;
                } else {
                    (*(VERT *)&q->vt[0].vx) = (*(VERT *)&vp[tp->v0].vx);
                    (*(u_long *)&q->vt[0].col) = *(u_long *)(a + 4);
                    (*(VERT *)&q->vt[1].vx) = (*(VERT *)&vp[tp->v1].vx);
                    (*(u_long *)&q->vt[1].col) = *(u_long *)(a + 0xC);
                    (*(VERT *)&q->vt[2].vx) = (*(VERT *)&vp[tp->v2].vx);
                    (*(u_long *)&q->vt[2].col) = *(u_long *)(a + 0x14);
                    (*(VERT *)&q->vt[3].vx) = (*(VERT *)&vp[tp->v3].vx);
                    (*(u_long *)&q->vt[3].col) = *(u_long *)(a + 0x1C);
                    s->pk = (u_long *)a;
                    func_000004C8(p, s, 0);
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
#endif
