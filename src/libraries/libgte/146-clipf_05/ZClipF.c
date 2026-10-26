#include "common.h"
#include <sys/types.h>
#include <libgte.h>

extern s32 CLIPKdhx;
extern s32 CLIPKdhy;

void ZClipF(SVECTOR *v0, SVECTOR *v1, EVECTOR *dst, long numerator, long denominator)
{
    long flag;
    long ratio;

    if (denominator == 0) {
        ratio = 0;
    } else {
        ratio = (numerator << 12) / denominator;
    }
    LoadAverageShort12(v0, v1, 4096 - ratio, ratio, &dst->v);
    RotTrans(&dst->v, &dst->sxyz, &flag);
    dst->chx = (dst->sxyz.vz * CLIPKdhx) >> 12;
    dst->chy = (dst->sxyz.vz * CLIPKdhy) >> 12;
}
