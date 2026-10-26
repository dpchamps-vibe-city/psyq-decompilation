/* Retained 000C0054.C with extracted private symbol name. */
#include "common.h"
#include <sys/types.h>
#include <libetc.h>
#include <libgte.h>
#include <inline_c.h>
#include <gtemac.h>
#include <libgpu.h>
#include <libgs.h>
#include <asm.h>
#include <libhmd.h>

typedef struct {
    u_char r0, g0, b0, code;
    u_char r1, g1, b1, pad0;
    u_char r2, g2, b2, pad1;
    u_char r3, g3, b3, pad2;
    u_short v0, v1;
    u_short v2, v3;
} HMD_P_NG4;

static void func_00000494(u_long *, GsADIV_G4 *, int);

u_long *GsU_000c0054(GsARGUNIT *sp)
{
    register GsADIV_G4 *ifo;
    register HMD_P_NG4 *tp;
    GsARGUNIT_NORMAL *ap = (GsARGUNIT_NORMAL *)sp;
    SVECTOR *vp = ap->vertop;
    SVECTOR *np = ap->nortop;
    GsADIV_P_G4 *p1;
    POLY_G4 *si;
    u_long *scratch = (u_long *)(ap + 1);
    long *otz;
    u_long t0;
    u_long t1;
    int i;
    int num;

    num = *(ap->primp) >> 16;
    ap->primp++;
    tp = (HMD_P_NG4 *)(ap->primtop + (*(ap->primp) & 0x00ffffff));
    ifo = (GsADIV_G4 *)scratch;
    scratch += sizeof(GsADIV_G4) / 4;
    p1 = (GsADIV_P_G4 *)scratch;

    ifo->limit = (u_long)(*(ap->primp) >> 24);
    ifo->hwd0 = HWD0 / 2;
    ifo->vwd0 = VWD0 / 2;
    ifo->adivz = GsADIVZ;
    ifo->adivw = GsADIVW;
    ifo->adivh = GsADIVH;
    ifo->pk = (u_long *)ap->out_packetp;
    ifo->org = (u_long *)ap->tagp->org;
    ifo->shift = ap->shift;
    setPolyG4(&ifo->si);

    si = (POLY_G4 *)ifo->pk;
    for (i = 0; i < num; i++, tp++) {
        otz = &ifo->otz;
        t1 = 0x00040000;
        t0 = 0x80000000;
        gte_ldv3(&vp[tp->v0], &vp[tp->v1], &vp[tp->v2]);
        gte_rtpt();
        gte_stflg(&ifo->flg0);
        gte_nclip();
        gte_stopz(otz);

        if (ifo->otz <= 0)
            continue;
        gte_stsxy3_g4((u_long *)si);
        gte_ldv0(&vp[tp->v3]);
        gte_rtps();
        *(u_long *)&si->r0 = *(u_long *)&tp->r0;
        gte_stflg(&ifo->flg);
        if ((ifo->flg & t1) && (ifo->flg0 & t1))
            continue;
        gte_stsxy((u_long *)&si->x3);
        gte_avsz4();
        *(u_long *)&si->r1 = *(u_long *)&tp->r1;
        *(u_long *)&si->r2 = *(u_long *)&tp->r2;
        *(u_long *)&si->r3 = *(u_long *)&tp->r3;
        gte_stotz(otz);
        ifo->tag = (u_long *)(ifo->org + (ifo->otz >> ifo->shift));

        if (ifo->otz < ifo->adivz)
            goto divide;
        if ((ifo->flg & t0) || (ifo->flg0 & t0))
            goto divide;
        *(u_long *)si = (*ifo->tag & 0x00ffffff) | 0x08000000;
        *ifo->tag = (u_long)si & 0x00ffffff;
        si++;
        continue;

divide:
        *(SVECTOR *)&p1->vt[0] = vp[tp->v0];
        *(SVECTOR *)&p1->vt[1] = vp[tp->v1];
        *(SVECTOR *)&p1->vt[2] = vp[tp->v2];
        *(SVECTOR *)&p1->vt[3] = vp[tp->v3];
        *(u_long *)&p1->vt[0].col.r = *(u_long *)&si->r0;
        *(u_long *)&p1->vt[1].col.r = *(u_long *)&si->r1;
        *(u_long *)&p1->vt[2].col.r = *(u_long *)&si->r2;
        *(u_long *)&p1->vt[3].col.r = *(u_long *)&si->r3;
        ifo->pk = (u_long *)si;
        func_00000494(scratch, ifo, 0);
        si = (POLY_G4 *)ifo->pk;
        continue;
    }
    GsOUT_PACKET_P = (PACKET *)si;
    return ap->primp + 1;
}
