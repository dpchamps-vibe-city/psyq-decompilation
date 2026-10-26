#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>

static void func_00000914(VERTC *v0, VERTC *v1, VERTC *v2)
{
    v0->vx = (v1->vx + v2->vx) / 2;
    v0->vy = (v1->vy + v2->vy) / 2;
    v0->vz = (v1->vz + v2->vz) / 2;
}
