#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <inline_c.h>
#include <libgpu.h>
#include <libgs.h>
#include <libhmd.h>

/* Retained DAG3_CM.C: Adiv_g3, with extracted private names. */
static void func_0000042C(u_long *scratch, GsADIV_G3 *ifo, int level)
{
    register GsADIV_P_G3 *in, *out;
    register POLY_G3 *si;
    VECTOR tmp;
    static void func_000007B8();
    static int func_000008AC();
    static void func_000009F8();

    in = (GsADIV_P_G3 *)scratch;
    scratch += sizeof(GsADIV_P_G3) / 4;
    out = (GsADIV_P_G3 *)scratch;

    gte_ldv3(&in->vt[0].vx, &in->vt[1].vx, &in->vt[2].vx);
    gte_rtpt();

    si = &ifo->si;
    gte_stflg(&ifo->flg);

    gte_stsxy3_g3((long *)si);
    gte_avsz3();
    gte_stszotz(&ifo->otz);

    if (func_000008AC(si, ifo))
        return;

    if (ifo->limit == level) {
        if (ifo->flg & 0x7f85e000)
            return;
        else
            goto aaa;
    }

    if (ifo->flg >= 0 && ifo->maxx - ifo->minx < ifo->adivw &&
        ifo->maxy - ifo->miny < ifo->adivh) {
    aaa:
        *ifo->pk = *(u_long *)si;
        *(ifo->pk + 1) = *(u_long *)&in->vt[0].col.r;
        *(ifo->pk + 2) = *(u_long *)((u_long *)si + 2);
        *(ifo->pk + 3) = *(u_long *)&in->vt[1].col.r;
        *(ifo->pk + 4) = *(u_long *)((u_long *)si + 4);
        *(ifo->pk + 5) = *(u_long *)&in->vt[2].col.r;
        *(ifo->pk + 6) = *(u_long *)((u_long *)si + 6);
        ifo->tag = ifo->org + (ifo->otz >> ifo->shift);
        *(u_long *)ifo->pk = (*ifo->tag & 0x00ffffff) | 0x06000000;
        *ifo->tag = (u_long)ifo->pk & 0x00ffffff;
        ifo->pk += sizeof(POLY_G3) / 4;
        return;
    }

    level++;

    out->vt[0] = in->vt[0];
    func_000009F8(&out->vt[1], &in->vt[0], &in->vt[1]);
    func_000009F8(&out->vt[2], &in->vt[0], &in->vt[2]);
    func_000007B8(&in->vt[0], &in->vt[1], &out->vt[1], ifo);
    func_0000042C(scratch, ifo, level);

    func_000009F8(&out->vt[0], &in->vt[1], &in->vt[2]);
    func_0000042C(scratch, ifo, level);

    out->vt[2] = in->vt[1];
    func_000007B8(&in->vt[1], &in->vt[2], &out->vt[0], ifo);
    func_0000042C(scratch, ifo, level);

    out->vt[1] = in->vt[2];
    func_000009F8(&out->vt[2], &in->vt[0], &in->vt[2]);
    func_000007B8(&in->vt[2], &in->vt[0], &out->vt[2], ifo);
    func_0000042C(scratch, ifo, level);
}
