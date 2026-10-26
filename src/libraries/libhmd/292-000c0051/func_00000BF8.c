/* Retained DAFT4_CM.C midpoint helper with the extracted private symbol name. */
#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <inline_c.h>
#include <libgpu.h>
#include <libgs.h>

void func_00000BF8(VERT *v0, VERT *v1, VERT *v2)
{
    v0->vx = (v1->vx + v2->vx) / 2;
    v0->vy = (v1->vy + v2->vy) / 2;
    v0->vz = (v1->vz + v2->vz) / 2;
    v0->tu = (v1->tu + v2->tu) >> 1;
    v0->tv = (v1->tv + v2->tv) >> 1;
}
