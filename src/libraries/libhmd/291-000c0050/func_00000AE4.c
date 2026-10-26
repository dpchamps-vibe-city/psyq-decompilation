/* Retained DAF4_CM.C bunV with extracted private symbol name. */
#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <inline_c.h>
#include <libgpu.h>
#include <libgs.h>

static void func_00000AE4(VERT *out, VERT *in1, VERT *in2)
{
  out->vx=(in1->vx+in2->vx)/2;
  out->vy=(in1->vy+in2->vy)/2;
  out->vz=(in1->vz+in2->vz)/2;
}
