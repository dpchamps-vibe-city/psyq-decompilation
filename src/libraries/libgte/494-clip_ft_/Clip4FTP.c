#include "common.h"
#include <sys/types.h>
#include <libgte.h>

long Clip4FTP(SVECTOR *v0, SVECTOR *v1, SVECTOR *v2, SVECTOR *v3, short *uv0,
              short *uv1, short *uv2, short *uv3, EVECTOR **evmx)
{
    long n;
    long i;
    long flag;

    n = Clip4FT(v0, v1, v2, v3, uv0, uv1, uv2, uv3, evmx);
    for (i = 0; i < n; i++) {
        EVECTOR *e = evmx[i];
        RotTransPers(&e->v, (long *)&e->sxy, &e->sxyz.pad, &flag);
    }
    return n;
}
