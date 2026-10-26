#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <inline_c.h>
#include <libgpu.h>
#include <libgs.h>
#include <libhmd.h>

/* Retained DAG3_CM.C: sukima, with extracted private name. */
static void func_0000075C(VERTC *v0, VERTC *v1, VERTC *v2, GsADIV_G3 *ifo)
{
    POLY_G3 *si;

    gte_ldv3(&v0->vx, &v1->vx, &v2->vx);
    gte_rtpt();
    si = (POLY_G3 *)ifo->pk;
    *(u_long *)&si->r0 = *(u_long *)&v0->col.r;
    setPolyG3(si);

    gte_stflg(&ifo->flg);

    if (ifo->flg < 0)
        return;

    gte_avsz3();
    gte_stsxy3_g3((long *)si);
    gte_stotz(&ifo->otz);
    *(u_long *)&si->r1 = *(u_long *)&v1->col.r;
    *(u_long *)&si->r2 = *(u_long *)&v2->col.r;
    ifo->tag = ifo->org + (ifo->otz >> ifo->shift);
    *(u_long *)si = (*ifo->tag & 0x00ffffff) | 0x06000000;
    *ifo->tag = (u_long)si & 0x00ffffff;
    ifo->pk += sizeof(POLY_G3) / 4;
}
