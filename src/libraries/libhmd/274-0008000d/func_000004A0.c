#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <inline_c.h>
#include <libgpu.h>
#include <libgs.h>
#include <libhmd.h>

static void func_00000880(VERTC *a, VERTC *b, VERTC *c, GsADIV_GT3 *ifo);
static int func_000009B0(POLY_GT3 *si, GsADIV_GT3 *ifo);
static void func_00000AFC(VERTC *d, VERTC *a, VERTC *b);

static void func_000004A0(u_long *scratch, GsADIV_GT3 *ifo, int level)
{
    register GsADIV_P_GT3 *in, *out;
    register POLY_GT3 *si;
    VECTOR tmp;

    in = (GsADIV_P_GT3 *)scratch;
    scratch += sizeof(GsADIV_P_GT3) / 4;
    out = (GsADIV_P_GT3 *)scratch;

    gte_ldv3(&in->vt[0].vx, &in->vt[1].vx, &in->vt[2].vx);
    gte_rtpt();

    si = &ifo->si;
    *(u_short *)&si->u0 = *(u_short *)&in->vt[0].tu;
    *(u_short *)&si->u1 = *(u_short *)&in->vt[1].tu;
    *(u_short *)&si->u2 = *(u_short *)&in->vt[2].tu;
    gte_stflg(&ifo->flg);

    gte_stsxy3_gt3(si);
    gte_avsz3();
    gte_stszotz(&ifo->otz);

    if (func_000009B0(si, ifo) != 0) {
        return;
    }
    if (ifo->limit == level) {
        if (ifo->flg & 0x7F85E000) {
            return;
        }
    } else if (ifo->flg < 0 || (ifo->maxx - ifo->minx) >= ifo->adivw ||
               (ifo->maxy - ifo->miny) >= ifo->adivh) {
        goto subdiv;
    }

    ifo->pk[0] = *(u_long *)&si->tag;
    ifo->pk[1] = *(u_long *)&in->vt[0].col;
    ifo->pk[2] = *(u_long *)&si->x0;
    ifo->pk[3] = *(u_long *)&si->u0;
    ifo->pk[4] = *(u_long *)&in->vt[1].col;
    ifo->pk[5] = *(u_long *)&si->x1;
    ifo->pk[6] = *(u_long *)&si->u1;
    ifo->pk[7] = *(u_long *)&in->vt[2].col;
    ifo->pk[8] = *(u_long *)&si->x2;
    ifo->pk[9] = *(u_long *)&si->u2;
    ifo->tag = &ifo->org[ifo->otz >> ifo->shift];
    *(u_long *)ifo->pk = (*(u_long *)ifo->tag & 0xFFFFFF) | 0x09000000;
    *(u_long *)ifo->tag = (u_long)ifo->pk & 0xFFFFFF;
    ifo->pk += 0xA;
    return;

subdiv:
    level++;
    out->vt[0] = in->vt[0];
    func_00000AFC(&out->vt[1], &in->vt[0], &in->vt[1]);
    func_00000AFC(&out->vt[2], &in->vt[0], &in->vt[2]);
    func_00000880(&in->vt[0], &in->vt[1], &out->vt[1], ifo);
    func_000004A0(scratch, ifo, level);

    func_00000AFC(&out->vt[0], &in->vt[1], &in->vt[2]);
    func_000004A0(scratch, ifo, level);

    out->vt[2] = in->vt[1];
    func_00000880(&in->vt[1], &in->vt[2], &out->vt[0], ifo);
    func_000004A0(scratch, ifo, level);

    out->vt[1] = in->vt[2];
    func_00000AFC(&out->vt[2], &in->vt[0], &in->vt[2]);
    func_00000880(&in->vt[2], &in->vt[0], &out->vt[2], ifo);
    func_000004A0(scratch, ifo, level);
}
