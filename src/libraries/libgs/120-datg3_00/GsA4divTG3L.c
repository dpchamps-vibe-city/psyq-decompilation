INCLUDE_ASM("build/libraries/nonmatchings/libgs_120", GsA4divTG3L);


/* PARKED by /auto_decompilation_loop on 2026-10-26T01:24:23.282Z.
 * Reason: escalation-exhausted.
 * Escalation reached: gpt-6.1-sol.
 * The best non-matching attempt is preserved verbatim below, disabled.
 * Findings and the decision needed: notes/human-needed-approvals/libgs_120::GsA4divTG3L.md
 */

#if 0
/* Best non-matching attempt, preserved for the next session. */
#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <inline_c.h>
#include <libgpu.h>
#include <libgs.h>

static void func_00000458(GsADIV_P_GT3 *p, GsADIV_GT3 *s, int level);

PACKET *GsA4divTG3L(TMD_P_TG3 *op, VERT *vp, VERT *np, PACKET *pk, int n, int shift, GsOT *ot, u_long *scratch) {
    GsADIV_GT3 *ifo;
    GsADIV_P_GT3 *p;
    GsADIV_P_GT3 *q;
    TMD_P_TG3 *tp;
    POLY_GT3 *si;
    int i;
    short adivw;
    short adivh;

    adivw = GsADIVW;
    adivh = GsADIVH;
    ifo = (GsADIV_GT3 *)scratch;
    scratch += sizeof(GsADIV_GT3) / 4;
    p = (GsADIV_P_GT3 *)scratch;
    q = p;

    ifo->hwd0 = HWD0 / 2;
    ifo->vwd0 = VWD0 / 2;
    ifo->org = (u_long *)ot->org;
    ifo->shift = shift;
    ifo->adivw = adivw;
    ifo->adivh = adivh;
    ifo->pk = (u_long *)pk;
    ifo->adivz = GsADIVZ;

    ifo->si.code = op->cd;
    ifo->si.r0 = 0x80;
    ifo->si.g0 = 0x80;
    ifo->si.b0 = 0x80;
    ifo->si.r1 = 0x80;
    ifo->si.g1 = 0x80;
    ifo->si.b1 = 0x80;
    ifo->si.r2 = 0x80;
    ifo->si.g2 = 0x80;
    ifo->si.b2 = 0x80;
    gte_ldrgb((u_long *)&ifo->si.r0);

    si = (POLY_GT3 *)ifo->pk;
    tp = op;

    for (i = 0; i < n; i++, tp++) {
        gte_ldv3(&vp[tp->v0], &vp[tp->v1], &vp[tp->v2]);
        gte_rtpt();
        *(u_long *)&si->u0 = *(u_long *)&tp->tu0;
        *(u_long *)&si->u2 = *(u_long *)&tp->tu2;
        gte_stflg((u_long *)&ifo->flg);
        gte_nclip();
        gte_stopz(&ifo->otz);
        if (ifo->otz <= 0)
            continue;
        if (ifo->flg & 0x00040000)
            continue;
        gte_stsxy3_gt3((u_long *)si);
        gte_avsz3();
        gte_stotz(&ifo->otz);
        gte_ldv3(&np[tp->n0], &np[tp->n1], &np[tp->n2]);
        gte_ncct();
        *(u_long *)&si->u1 = *(u_long *)&tp->tu1;
        ifo->tag = (u_long *)(ifo->org + (ifo->otz >> ifo->shift));
        gte_strgb3(&si->r0, &si->r1, &si->r2);
        if (ifo->otz < ifo->adivz)
            goto divide;
        if (ifo->flg & 0x80000000)
            goto divide;
        *(u_long *)si = (*ifo->tag & 0x00ffffff) | 0x09000000;
        *ifo->tag = (u_long)si & 0x00ffffff;
        si++;
        continue;

divide:
        *(VERT *)&q->vt[0] = vp[tp->v0];
        *(u_long *)&q->vt[0].col = *(u_long *)&si->r0;
        *(VERT *)&q->vt[1] = vp[tp->v1];
        *(u_long *)&q->vt[1].col = *(u_long *)&si->r1;
        *(VERT *)&q->vt[2] = vp[tp->v2];
        *(u_long *)&q->vt[2].col = *(u_long *)&si->r2;
        *(u_short *)&q->vt[0].tu = *(u_short *)&tp->tu0;
        *(u_short *)&q->vt[1].tu = *(u_short *)&tp->tu1;
        *(u_short *)&q->vt[2].tu = *(u_short *)&tp->tu2;
        ifo->si.clut = tp->clut;
        ifo->si.tpage = tp->tpage;
        ifo->pk = (u_long *)si;
        func_00000458(p, ifo, 0);
        si = (POLY_GT3 *)ifo->pk;
    }
    ifo->pk = (u_long *)si;
    return (PACKET *)si;
}
#endif
