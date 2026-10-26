#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <inline_c.h>
#include <libgpu.h>
#include <libgs.h>
#include <libhmd.h>

static void func_00000964(VERT *v0, VERT *v1, VERT *v2, GsADIV_FT4 *ifo)
{
    POLY_FT3 *si;

    gte_ldv3(&v0->vx, &v1->vx, &v2->vx);
    gte_rtpt();
    si = (POLY_FT3 *)ifo->pk;
    *(u_long *)&si->r0 = *(u_long *)&ifo->si.r0;
    setPolyFT3(si);
    gte_stflg(&ifo->flg);
    if (ifo->flg < 0)
        return;
    gte_avsz3();
    gte_stsxy3_ft3((long *)si);
    gte_stotz(&ifo->otz);
    *(u_long *)&si->u0 = *(u_short *)&v0->tu;
    *(u_long *)&si->u1 = *(u_short *)&v1->tu;
    *(u_long *)&si->u2 = *(u_short *)&v2->tu;
    si->clut = ifo->si.clut;
    si->tpage = ifo->si.tpage;
    ifo->tag = ifo->org + (ifo->otz >> ifo->shift);
    *(u_long *)si = (*ifo->tag & 0x00ffffff) | 0x07000000;
    *ifo->tag = (u_long)si & 0x00ffffff;
    ifo->pk += sizeof(POLY_FT3) / 4;
}
