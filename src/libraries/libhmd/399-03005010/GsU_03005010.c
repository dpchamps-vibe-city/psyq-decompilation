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
} GsARGANIM2;

/* hokan driver (ZYX) */
int GsU_03005010(GsARGUNIT_ANIM *sp0)
{
    GsCOORDUNIT *dtop;
    u_long ofs0, ofs1;
    GsSEQ *seq;
    GsARGANIM2 *sp;
    long rframe, tframe;

    sp = (GsARGANIM2 *)(&(sp0->header_size) + sp0->header_size);
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
    RotMatrixZYX(&dtop->rot, &dtop->matrix);
    dtop->flg = 0;

    if (sp->intr) {
        *sp->intr = dtop->rot;
    }
    return 0;
}
