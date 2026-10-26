#include "common.h"
#include <sys/types.h>
#include <libgte.h>

extern EVECTOR *CLIPEvbf;
extern s32 CLIPKdhx;
extern s32 CLIPKdhy;

extern long ClipFT(long n, EVECTOR **evmx);

long Clip4FT(SVECTOR *v0, SVECTOR *v1, SVECTOR *v2, SVECTOR *v3,
             short *uv0, short *uv1, short *uv2, short *uv3,
             EVECTOR **evmx)
{
    long i;
    long flag;

    CLIPEvbf[0].v = *v0;
    CLIPEvbf[1].v = *v1;
    CLIPEvbf[2].v = *v3;
    CLIPEvbf[3].v = *v2;

    CLIPEvbf[0].txuv = *uv0;
    CLIPEvbf[1].txuv = *uv1;
    CLIPEvbf[2].txuv = *uv3;
    CLIPEvbf[3].txuv = *uv2;

    for (i = 0; i < 4; i++) {
        RotTrans(&CLIPEvbf[i].v, &CLIPEvbf[i].sxyz, &flag);
        CLIPEvbf[i].chx = (CLIPEvbf[i].sxyz.vz * CLIPKdhx) >> 12;
        CLIPEvbf[i].chy = (CLIPEvbf[i].sxyz.vz * CLIPKdhy) >> 12;
        evmx[i] = &CLIPEvbf[i];
    }
    return ClipFT(i, evmx);
}
