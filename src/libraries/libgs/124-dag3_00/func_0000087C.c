#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <inline_c.h>
#include <libgpu.h>
#include <libgs.h>

static int func_0000087C(POLY_G3 *p, GsADIV_G3 *s)
{
    if (p->x0 > p->x1) {
        s->maxx = p->x0;
        s->minx = p->x1;
    } else {
        s->minx = p->x0;
        s->maxx = p->x1;
    }
    if (p->x2 > s->maxx) {
        s->maxx = p->x2;
    } else if (p->x2 < s->minx) {
        s->minx = p->x2;
    }
    if (s->maxx < -s->hwd0 || s->hwd0 < s->minx) {
        return 1;
    }
    if (p->y0 > p->y1) {
        s->maxy = p->y0;
        s->miny = p->y1;
    } else {
        s->miny = p->y0;
        s->maxy = p->y1;
    }
    if (p->y2 > s->maxy) {
        s->maxy = p->y2;
    } else if (p->y2 < s->miny) {
        s->miny = p->y2;
    }
    if (s->maxy < -s->vwd0 || s->vwd0 < s->miny) {
        return 1;
    }
    return 0;
}
