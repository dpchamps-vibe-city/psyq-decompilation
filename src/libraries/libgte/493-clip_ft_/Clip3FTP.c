#include "common.h"
#include <sys/types.h>
#include <libgte.h>

long Clip3FTP(SVECTOR *v0, SVECTOR *v1, SVECTOR *v2, short *uv0,
              short *uv1, short *uv2, EVECTOR **evmx)
{
    long n;
    long i;
    long flag;

    n = Clip3FT(v0, v1, v2, uv0, uv1, uv2, evmx);
    for (i = 0; i < n; i++) {
        EVECTOR *e = evmx[i];
        RotTransPers(&e->v, (long *)&e->sxy, &e->sxyz.pad, &flag);
    }
    return n;
}
