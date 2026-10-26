#include "common.h"
#include <sys/types.h>
#include <libgte.h>

extern EVECTOR *CLIPEvbf;
extern s32 CLIPKdhx;
extern s32 CLIPKdhy;

extern long ClipF(long n, EVECTOR **evmx);

long Clip3F(SVECTOR *v0, SVECTOR *v1, SVECTOR *v2, EVECTOR **evmx)
{
    long i;
    long flag;

    CLIPEvbf[0].v = *v0;
    CLIPEvbf[1].v = *v1;
    CLIPEvbf[2].v = *v2;

    for (i = 0; i < 3; i++) {
        RotTrans(&CLIPEvbf[i].v, &CLIPEvbf[i].sxyz, &flag);
        CLIPEvbf[i].chx = (CLIPEvbf[i].sxyz.vz * CLIPKdhx) >> 12;
        CLIPEvbf[i].chy = (CLIPEvbf[i].sxyz.vz * CLIPKdhy) >> 12;
        evmx[i] = &CLIPEvbf[i];
    }
    return ClipF(i, evmx);
}
