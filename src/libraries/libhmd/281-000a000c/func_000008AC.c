#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <inline_c.h>
#include <libgpu.h>
#include <libgs.h>

/* Retained DAG3_CM.C: outline(), with the extracted private name. */
static int func_000008AC(POLY_G3 *si, GsADIV_G3 *ifo)
{
    minmax3(si->x0, si->x1, si->x2, ifo->minx, ifo->maxx);
    if ((ifo->maxx < -ifo->hwd0) || (ifo->minx > ifo->hwd0))
        return 1;
    minmax3(si->y0, si->y1, si->y2, ifo->miny, ifo->maxy);
    if ((ifo->maxy < -ifo->vwd0) || (ifo->miny > ifo->vwd0))
        return 1;
    return 0;
}
