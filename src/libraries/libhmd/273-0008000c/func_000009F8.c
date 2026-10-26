#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <inline_c.h>
#include <libgpu.h>
#include <libgs.h>

/* Retained DAG3_CM.C: bunCV, with extracted private name. */
static void func_000009F8(VERTC *out, VERTC *in1, VERTC *in2)
{
    out->vx = (in1->vx + in2->vx) / 2;
    out->vy = (in1->vy + in2->vy) / 2;
    out->vz = (in1->vz + in2->vz) / 2;

    out->col.r = (in1->col.r + in2->col.r) / 2;
    out->col.g = (in1->col.g + in2->col.g) / 2;
    out->col.b = (in1->col.b + in2->col.b) / 2;
    out->col.cd = in1->col.cd;
}
