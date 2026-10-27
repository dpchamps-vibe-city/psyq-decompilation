/* $PSLibId: Run-time Library Release 4.4$ */
/* Copyright(C) 1998 Sony Computer Entertainment Inc. All rights reserved. */
#include "common.h"
#include <sys/types.h>
#include <libetc.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>
#include <libhmd.h>

typedef struct {
    GsSEQ *base;
    SVECTOR *src;
    SVECTOR *dst;
    SVECTOR *intr;
} GsARGANIM1;

/* hokan driver */
int GsU_03000010(GsARGUNIT_ANIM *sp0)
{
    GsCOORDUNIT *dtop;
    u_long ofs0, ofs1;
    GsSEQ *seq;
    GsARGANIM1 *sp;
    long rframe, tframe;

    sp = (GsARGANIM1 *)(&(sp0->header_size) + sp0->header_size);
    seq = sp->base;
    if (seq->tframe == 0)
        return 1;
    ofs0 = ((seq->rewrite_idx) & 0xff000000) >> 24;
    ofs1 = (seq->rewrite_idx) & 0x00ffffff;
    rframe = seq->rframe;
    tframe = seq->tframe;

    dtop = (GsCOORDUNIT *)((u_long *)(*(&(sp0->header_size) + ofs0)) + ofs1);
    dtop->rot.vx = (sp->src->vx * rframe + sp->dst->vx * (tframe - rframe)) / tframe;
    dtop->rot.vy = (sp->src->vy * rframe + sp->dst->vy * (tframe - rframe)) / tframe;
    dtop->rot.vz = (sp->src->vz * rframe + sp->dst->vz * (tframe - rframe)) / tframe;
    RotMatrix(&dtop->rot, &dtop->matrix);
    dtop->flg = 0;

    if (sp->intr) {
        *sp->intr = dtop->rot;
    }
    return 0;
}
