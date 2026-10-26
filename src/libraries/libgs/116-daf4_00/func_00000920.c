#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <inline_c.h>
#include <libgpu.h>
#include <libgs.h>

static s32 func_00000920(POLY_F4 *si, GsADIV_F4 *s)
{
    minmax4(si->x0, si->x1, si->x2, si->x3, s->minx, s->maxx);
    if ((s->maxx < -s->hwd0) || (s->minx > s->hwd0))	/* HW clip */
	return 1;
    minmax4(si->y0, si->y1, si->y2, si->y3, s->miny, s->maxy);
    if ((s->maxy < -s->vwd0) || (s->miny > s->vwd0))
	return 1;
    return 0;
}
