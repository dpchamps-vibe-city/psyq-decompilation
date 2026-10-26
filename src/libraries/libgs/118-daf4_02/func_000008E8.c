#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>

s32 func_000008E8(POLY_F4 *si, GsADIV_F4 *s)
{
    if (si->x0 > si->x1) {
        s->maxx = si->x0;
        s->minx = si->x1;
    } else {
        s->minx = si->x0;
        s->maxx = si->x1;
    }
    if (si->x2 > s->maxx) s->maxx = si->x2;
    else if (si->x2 < s->minx) s->minx = si->x2;
    if (si->x3 > s->maxx) s->maxx = si->x3;
    else if (si->x3 < s->minx) s->minx = si->x3;
    if (s->maxx < -s->hwd0 || s->hwd0 < s->minx) return 1;
    if (si->y0 > si->y1) {
        s->maxy = si->y0;
        s->miny = si->y1;
    } else {
        s->miny = si->y0;
        s->maxy = si->y1;
    }
    if (si->y2 > s->maxy) s->maxy = si->y2;
    else if (si->y2 < s->miny) s->miny = si->y2;
    if (si->y3 > s->maxy) s->maxy = si->y3;
    else if (si->y3 < s->miny) s->miny = si->y3;
    if (s->maxy < -s->vwd0 || s->vwd0 < s->miny) return 1;
    return 0;
}
