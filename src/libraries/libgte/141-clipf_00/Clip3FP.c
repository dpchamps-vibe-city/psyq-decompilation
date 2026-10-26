#include "common.h"
#include <sys/types.h>
#include <libgte.h>

long Clip3FP(SVECTOR *v0, SVECTOR *v1, SVECTOR *v2, EVECTOR **evmx)
{
    long n;
    long i;
    long flag;

    n = Clip3F(v0, v1, v2, evmx);
    for (i = 0; i < n; i++) {
        EVECTOR *e = evmx[i];
        RotTransPers(&e->v, (long *)&e->sxy, &e->sxyz.pad, &flag);
    }
    return n;
}
