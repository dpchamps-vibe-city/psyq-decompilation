#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <inline_c.h>
#include <libgpu.h>
#include <libgs.h>

static int func_00000BD8(POLY_GT4 *p, GsADIV_GT4 *s)
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
    if (p->x3 > s->maxx) {
        s->maxx = p->x3;
    } else if (p->x3 < s->minx) {
        s->minx = p->x3;
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
    if (p->y3 > s->maxy) {
        s->maxy = p->y3;
    } else if (p->y3 < s->miny) {
        s->miny = p->y3;
    }
    if (s->maxy < -s->vwd0 || s->vwd0 < s->miny) {
        return 1;
    }
    return 0;
}
