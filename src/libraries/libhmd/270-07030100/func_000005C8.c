#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>
#include <libhmd.h>

long func_000005C8(VECTOR *in0, VECTOR *in1)
{
    long ret;

    ret = (in0->vx > 0 ? in0->vx : -in0->vx);
    ret = (ret > (in0->vy > 0 ? in0->vy : -in0->vy) ? ret :
                (in0->vy > 0 ? in0->vy : -in0->vy));
    ret = (ret > (in0->vz > 0 ? in0->vz : -in0->vz) ? ret :
                (in0->vz > 0 ? in0->vz : -in0->vz));
    ret = (ret > (in1->vx > 0 ? in1->vx : -in1->vx) ? ret :
                (in1->vx > 0 ? in1->vx : -in1->vx));
    ret = (ret > (in1->vy > 0 ? in1->vy : -in1->vy) ? ret :
                (in1->vy > 0 ? in1->vy : -in1->vy));
    ret = (ret > (in1->vz > 0 ? in1->vz : -in1->vz) ? ret :
                (in1->vz > 0 ? in1->vz : -in1->vz));
    return ret;
}
