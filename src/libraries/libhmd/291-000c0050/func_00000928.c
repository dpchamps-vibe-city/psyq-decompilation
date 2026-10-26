/* Retained DAF4_CM.C outline with extracted private symbol name. */
#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <inline_c.h>
#include <libgpu.h>
#include <libgs.h>

static int func_00000928(POLY_F4 *si, GsADIV_F4 *ifo)
{
  minmax4(si->x0,si->x1,si->x2,si->x3,ifo->minx,ifo->maxx);
  if((ifo->maxx<-ifo->hwd0) || (ifo->minx>ifo->hwd0))
    return 1;
  minmax4(si->y0,si->y1,si->y2,si->y3,ifo->miny,ifo->maxy);
  if((ifo->maxy<-ifo->vwd0) || (ifo->miny>ifo->vwd0))
    return 1;
  return 0;
}
