/* Retained DAF3_CM.C: Adiv_f3 (member 000A0008), were extracted private symbol names. */
#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <inline_c.h>
#include <gtemac.h>
#include <libgpu.h>
#include <libgs.h>
#include <asm.h>
#include <libhmd.h>

static void func_000003F0(u_long *scratch, GsADIV_F3 *ifo, int level);
static void func_0000072C();
static int func_0000080C();
static void func_00000958();

static void func_000003F0(u_long *scratch, GsADIV_F3 *ifo, int level)
{
    register GsADIV_P_F3 *in, *out;
    register POLY_F3 *si;
    VECTOR tmp;

    in = (GsADIV_P_F3 *)scratch;
    scratch += sizeof(GsADIV_P_F3) / 4;
    out = (GsADIV_P_F3 *)scratch;

    gte_ldv3(&in->vt[0].vx, &in->vt[1].vx, &in->vt[2].vx);
    gte_rtpt();
    si = &ifo->si;
    gte_stflg(&ifo->flg);
    gte_stsxy3_f3((long *)si);
    gte_avsz3();
    gte_stszotz(&ifo->otz);

    if (func_0000080C(si, ifo))
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
        *(ifo->pk + 1) = *((u_long *)si + 1);
        *(ifo->pk + 2) = *((u_long *)si + 2);
        *(ifo->pk + 3) = *((u_long *)si + 3);
        *(ifo->pk + 4) = *((u_long *)si + 4);
        ifo->tag = ifo->org + (ifo->otz >> ifo->shift);
        *(u_long *)ifo->pk = (*ifo->tag & 0x00ffffff) | 0x04000000;
        *ifo->tag = (u_long)ifo->pk & 0x00ffffff;
        ifo->pk += sizeof(POLY_F3) / 4;
        return;
    }
    level++;
    out->vt[0] = in->vt[0];
    func_00000958(&out->vt[1], &in->vt[0], &in->vt[1]);
    func_00000958(&out->vt[2], &in->vt[0], &in->vt[2]);
    func_0000072C(&in->vt[0], &in->vt[1], &out->vt[1], ifo);
    func_000003F0(scratch, ifo, level);

    func_00000958(&out->vt[0], &in->vt[1], &in->vt[2]);
    func_000003F0(scratch, ifo, level);

    out->vt[2] = in->vt[1];
    func_0000072C(&in->vt[1], &in->vt[2], &out->vt[0], ifo);
    func_000003F0(scratch, ifo, level);

    out->vt[1] = in->vt[2];
    func_00000958(&out->vt[2], &in->vt[0], &in->vt[2]);
    func_0000072C(&in->vt[2], &in->vt[0], &out->vt[2], ifo);
    func_000003F0(scratch, ifo, level);
}
