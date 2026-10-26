#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <inline_c.h>
#include <libgpu.h>
#include <libgs.h>
#include <libhmd.h>

/* Retained HMD DATG4_CM.C: Adiv_gt4, with extracted private names. */
static void func_00000A68(VERTC *v0, VERTC *v1, VERTC *v2, GsADIV_GT4 *ifo);
static int func_00000B98(POLY_GT4 *si, GsADIV_GT4 *ifo);
static void func_00000D54(VERTC *out, VERTC *in1, VERTC *in2);

static void func_0000059C(u_long *scratch, GsADIV_GT4 *ifo, int level)
{
    GsADIV_P_GT4 *in;
    GsADIV_P_GT4 *out;
    POLY_GT4 *si;
    VECTOR tmp;

    in = (GsADIV_P_GT4 *)scratch;
    scratch += sizeof(GsADIV_P_GT4) / 4;
    out = (GsADIV_P_GT4 *)scratch;

    gte_ldv3(&in->vt[0].vx, &in->vt[1].vx, &in->vt[2].vx);
    gte_rtpt();

    si = &ifo->si;
    *(u_short *)&si->u0 = *(u_short *)&in->vt[0].tu;
    *(u_short *)&si->u1 = *(u_short *)&in->vt[1].tu;
    *(u_short *)&si->u2 = *(u_short *)&in->vt[2].tu;
    gte_stflg(&ifo->flg);

    gte_stsxy3_gt4((long *)si);

    gte_ldv0(&in->vt[3].vx);
    gte_rtps();
    *(u_short *)&si->u3 = *(u_short *)&in->vt[3].tu;
    gte_stflg(&ifo->flg0);
    ifo->flg |= ifo->flg0;
    gte_stsxy((long *)&si->x3);
    gte_avsz4();
    gte_stszotz(&ifo->otz);

    if (func_00000B98(si, ifo) != 0) {
        return;
    }

    if (ifo->limit == level) {
        if (ifo->flg & 0x7F85E000) {
            return;
        }
    } else if (ifo->flg < 0
               || (ifo->maxx - ifo->minx) >= ifo->adivw
               || (ifo->maxy - ifo->miny) >= ifo->adivh) {
        goto subdiv;
    }

    *ifo->pk = *(u_long *)si;
    *(ifo->pk + 1) = *(u_long *)&in->vt[0].col.r;
    *(ifo->pk + 2) = *(u_long *)((u_long *)si + 2);
    *(ifo->pk + 3) = *(u_long *)((u_long *)si + 3);
    *(ifo->pk + 4) = *(u_long *)&in->vt[1].col.r;
    *(ifo->pk + 5) = *(u_long *)((u_long *)si + 5);
    *(ifo->pk + 6) = *(u_long *)((u_long *)si + 6);
    *(ifo->pk + 7) = *(u_long *)&in->vt[2].col.r;
    *(ifo->pk + 8) = *(u_long *)((u_long *)si + 8);
    *(ifo->pk + 9) = *(u_long *)((u_long *)si + 9);
    *(ifo->pk + 10) = *(u_long *)&in->vt[3].col.r;
    *(ifo->pk + 11) = *(u_long *)((u_long *)si + 11);
    *(ifo->pk + 12) = *(u_long *)((u_long *)si + 12);
    ifo->tag = ifo->org + (ifo->otz >> ifo->shift);
    *(u_long *)ifo->pk = (*ifo->tag & 0x00FFFFFF) | 0x0C000000;
    *ifo->tag = (u_long)ifo->pk & 0x00FFFFFF;
    ifo->pk += sizeof(POLY_GT4) / 4;
    return;

subdiv:
    level++;

    out->vt[0] = in->vt[0];
    func_00000D54(&out->vt[1], &in->vt[0], &in->vt[1]);
    func_00000D54(&out->vt[2], &in->vt[0], &in->vt[2]);
    func_00000D54(&out->vt[3], &in->vt[0], &in->vt[3]);
    func_00000A68(&in->vt[0], &in->vt[1], &out->vt[1], ifo);
    func_0000059C(scratch, ifo, level);

    out->vt[0] = in->vt[1];
    func_00000D54(&out->vt[2], &in->vt[1], &in->vt[3]);
    func_00000A68(&in->vt[1], &in->vt[3], &out->vt[2], ifo);
    func_0000059C(scratch, ifo, level);

    out->vt[0] = in->vt[3];
    func_00000D54(&out->vt[1], &in->vt[3], &in->vt[2]);
    func_00000A68(&in->vt[3], &in->vt[2], &out->vt[1], ifo);
    func_0000059C(scratch, ifo, level);

    out->vt[0] = in->vt[2];
    func_00000D54(&out->vt[2], &in->vt[0], &in->vt[2]);
    func_00000A68(&in->vt[2], &in->vt[0], &out->vt[2], ifo);
    func_0000059C(scratch, ifo, level);
}
