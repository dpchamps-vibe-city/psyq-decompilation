#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>
#include <libhmd.h>

typedef struct {
    GsSEQ *base;
    u_char *src;
    u_char *dst;
    u_char *intr;
} GsARGANIM1;

int GsU_03010182(GsARGUNIT_ANIM *sp0)
{
    u_char *dtop;
    u_long ofs0, ofs1;
    GsSEQ *seq;
    GsARGANIM1 *sp;
    long rframe, tframe;

    sp = (GsARGANIM1 *)(&(sp0->header_size) + sp0->header_size);
    seq = sp->base;
    if (seq->tframe == 0)
        return 1;

    rframe = seq->rframe;
    tframe = seq->tframe;
    ofs0 = ((seq->rewrite_idx) & 0xff000000) >> 24;
    ofs1 = (seq->rewrite_idx) & 0x00ffffff;
    dtop = (u_char *)((u_long *)(*(&(sp0->header_size) + ofs0)) + ofs1);
    dtop[3] = (*sp->src * rframe + *sp->dst * (tframe - rframe)) / tframe;
    if (sp->intr)
        *sp->intr = dtop[3];
    return 0;
}
