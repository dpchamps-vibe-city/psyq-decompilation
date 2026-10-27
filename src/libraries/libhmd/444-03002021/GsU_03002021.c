/* $PSLibId: Run-time Library Release 4.4$ */

/*
 *	Copyright(C) 1998 Sony Computer Entertainment Inc.
 *  	All rights reserved.
 */

#include "common.h"
#include <sys/types.h>
#include <libetc.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>
#include <libhmd.h>

typedef struct {
    long vx, vy, vz;
    short rx0, ry0, rz0;
    short rx1, ry1, rz1;
    short rx2, ry2, rz2;
} MYVECTOR;

typedef struct {
    GsSEQ *base;
    MYVECTOR *src;
    MYVECTOR *dst;
    MYVECTOR *intr;
} GsARGANIM1;

extern void setBezierCof(int, int, int, int, short *);

/* hokan driver (rotation order YXZ) */
int GsU_03002021(GsARGUNIT_ANIM *sp0)
{
    GsCOORDUNIT *dtop;
    u_long ofs0, ofs1;
    GsSEQ *seq;
    GsARGANIM1 *sp;
    long rframe, tframe;
    long t;
    short co[3][4];

    sp = (GsARGANIM1 *)(&(sp0->header_size) + sp0->header_size);
    seq = sp->base;
    if (seq->tframe == 0)
        return 1;
    ofs0 = ((seq->rewrite_idx) & 0xff000000) >> 24;
    ofs1 = (seq->rewrite_idx) & 0x00ffffff;

    rframe = seq->rframe;
    tframe = seq->tframe;

    t = (tframe - rframe) * 0xffff / tframe;

    setBezierCof(sp->src->rx0, sp->src->rx1, sp->src->rx2, sp->dst->rx0, co[0]);
    setBezierCof(sp->src->ry0, sp->src->ry1, sp->src->ry2, sp->dst->ry0, co[1]);
    setBezierCof(sp->src->rz0, sp->src->rz1, sp->src->rz2, sp->dst->rz0, co[2]);

    dtop = (GsCOORDUNIT *)((u_long *)(*(&(sp0->header_size) + ofs0)) + ofs1);
    dtop->matrix.t[0] = (sp->src->vx * rframe + sp->dst->vx * (tframe - rframe)) / tframe;
    dtop->matrix.t[1] = (sp->src->vy * rframe + sp->dst->vy * (tframe - rframe)) / tframe;
    dtop->matrix.t[2] = (sp->src->vz * rframe + sp->dst->vz * (tframe - rframe)) / tframe;

    dtop->rot.vx = ((((((((co[0][0] * t) >> 16) + co[0][1]) * t) >> 16) + co[0][2])
                     * t) >> 16) + co[0][3];
    dtop->rot.vy = ((((((((co[1][0] * t) >> 16) + co[1][1]) * t) >> 16) + co[1][2])
                     * t) >> 16) + co[1][3];
    dtop->rot.vz = ((((((((co[2][0] * t) >> 16) + co[2][1]) * t) >> 16) + co[2][2])
                     * t) >> 16) + co[2][3];

    RotMatrixYXZ(&dtop->rot, &dtop->matrix);
    dtop->flg = 0;

    if (sp->intr) {
        sp->intr->vx = dtop->matrix.t[0];
        sp->intr->vy = dtop->matrix.t[1];
        sp->intr->vz = dtop->matrix.t[2];
        sp->intr->rx0 = dtop->rot.vx;
        sp->intr->ry0 = dtop->rot.vy;
        sp->intr->rz0 = dtop->rot.vz;
    }

    return 0;
}
