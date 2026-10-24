#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>

void GsScaleScreen(SVECTOR *scale) {
    VECTOR v;
    s32 t;

    v.vx = scale->vx;
    v.vy = scale->vy;
    v.vz = scale->vz;
    GsWSMATRIX = GsWSMATRIX_ORG;
    ScaleMatrix(&GsWSMATRIX, &v);
    t = GsWSMATRIX.t[0] * scale->vx;
    if (t < 0) {
        t += 0xFFF;
    }
    GsWSMATRIX.t[0] = t >> 12;
    t = GsWSMATRIX.t[1] * scale->vy;
    if (t < 0) {
        t += 0xFFF;
    }
    GsWSMATRIX.t[1] = t >> 12;
    t = GsWSMATRIX.t[2] * scale->vz;
    if (t < 0) {
        t += 0xFFF;
    }
    GsWSMATRIX.t[2] = t >> 12;
}
