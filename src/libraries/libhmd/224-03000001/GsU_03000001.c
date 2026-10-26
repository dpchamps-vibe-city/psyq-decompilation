#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>
#include <libhmd.h>

typedef struct {
    long vx, vy, vz;
} MYVECTOR;

typedef struct {
    GsSEQ *base;
    MYVECTOR *src;
    MYVECTOR *dst;
    MYVECTOR *intr;
} GsARGANIM1;

/* hokan driver */
int GsU_03000001(GsARGUNIT_ANIM *sp0)
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
    dtop->matrix.t[0] = (sp->src->vx * rframe + sp->dst->vx * (tframe - rframe)) / tframe;
    dtop->matrix.t[1] = (sp->src->vy * rframe + sp->dst->vy * (tframe - rframe)) / tframe;
    dtop->matrix.t[2] = (sp->src->vz * rframe + sp->dst->vz * (tframe - rframe)) / tframe;
    dtop->flg = 0;

    if (sp->intr) {
        sp->intr->vx = dtop->matrix.t[0];
        sp->intr->vy = dtop->matrix.t[1];
        sp->intr->vz = dtop->matrix.t[2];
    }
    return 0;
}
