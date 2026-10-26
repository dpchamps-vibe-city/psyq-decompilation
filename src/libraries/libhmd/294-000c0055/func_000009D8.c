#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <inline_c.h>
#include <libgpu.h>
#include <libgs.h>
#include <libhmd.h>

/* Retained Sony HMD DATG4_CM.C: sukima. */
void func_000009D8(VERTC *v0, VERTC *v1, VERTC *v2, GsADIV_GT4 *ifo)
{
    POLY_GT3 *si;

    gte_ldv3(&v0->vx, &v1->vx, &v2->vx);
    gte_rtpt();
    si = (POLY_GT3 *)ifo->pk;
    *(u_long *)&si->r0 = *(u_long *)&v0->col.r;
    setPolyGT3(si);
    gte_stflg(&ifo->flg);
    if (ifo->flg < 0)
        return;
    gte_avsz3();
    gte_stsxy3_gt3((long *)si);
    gte_stotz(&ifo->otz);
    *(u_long *)&si->u0 = *(u_short *)&v0->tu;
    *(u_long *)&si->u1 = *(u_short *)&v1->tu;
    *(u_long *)&si->u2 = *(u_short *)&v2->tu;
    *(u_long *)&si->r1 = *(u_long *)&v1->col.r;
    *(u_long *)&si->r2 = *(u_long *)&v2->col.r;
    si->clut = ifo->si.clut;
    si->tpage = ifo->si.tpage;
    ifo->tag = ifo->org + (ifo->otz >> ifo->shift);
    *(u_long *)si = (*ifo->tag & 0x00ffffff) | 0x09000000;
    *ifo->tag = (u_long)si & 0x00ffffff;
    ifo->pk += sizeof(POLY_GT3) / 4;
}
