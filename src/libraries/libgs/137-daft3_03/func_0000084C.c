#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <inline_c.h>
#include <libgpu.h>
#include <libgs.h>

static int func_0000084C(POLY_FT3 *p, GsADIV_FT3 *s)
{
    minmax3(p->x0, p->x1, p->x2, s->minx, s->maxx);
    if ((s->maxx < -s->hwd0) || (s->minx > s->hwd0))
        return 1;
    minmax3(p->y0, p->y1, p->y2, s->miny, s->maxy);
    if ((s->maxy < -s->vwd0) || (s->miny > s->vwd0))
        return 1;
    return 0;
}
