#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>

static void func_00000958(SVECTOR *out, SVECTOR *v0, SVECTOR *v1)
{
    out->vx = (v0->vx + v1->vx) / 2;
    out->vy = (v0->vy + v1->vy) / 2;
    out->vz = (v0->vz + v1->vz) / 2;
}
