#include "common.h"
#include <sys/types.h>
#include <libgte.h>

long Clip3GP(SVECTOR *v0, SVECTOR *v1, SVECTOR *v2, CVECTOR *rgb0,
             CVECTOR *rgb1, CVECTOR *rgb2, EVECTOR **evmx)
{
    long n;
    long i;
    long flag;

    n = Clip3G(v0, v1, v2, rgb0, rgb1, rgb2, evmx);
    for (i = 0; i < n; i++) {
        EVECTOR *e = evmx[i];
        RotTransPers(&e->v, (long *)&e->sxy, &e->sxyz.pad, &flag);
    }
    return n;
}
