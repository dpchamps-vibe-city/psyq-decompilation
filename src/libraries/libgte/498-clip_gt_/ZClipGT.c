#include "common.h"
#include <sys/types.h>
#include <libgte.h>

extern s32 CLIPKdhx;
extern s32 CLIPKdhy;

void ZClipGT(EVECTOR *a, EVECTOR *b, EVECTOR *out, long numerator, long denominator)
{
    long flag;
    long ratio;

    if (denominator == 0) {
        ratio = 0;
    } else {
        ratio = (numerator << 12) / denominator;
    }
    LoadAverageShort12(&a->v, &b->v, 4096 - ratio, ratio, &out->v);
    LoadAverageByte((u_char *)&a->txuv, (u_char *)&b->txuv, 4096 - ratio, ratio,
                    (u_char *)&out->txuv);
    LoadAverageCol((u_char *)&a->rgb, (u_char *)&b->rgb, 4096 - ratio, ratio,
                   (u_char *)&out->rgb);
    RotTrans(&out->v, &out->sxyz, &flag);
    out->chx = (out->sxyz.vz * CLIPKdhx) >> 12;
    out->chy = (out->sxyz.vz * CLIPKdhy) >> 12;
}
