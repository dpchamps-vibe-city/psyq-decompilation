#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>
#include <libhmd.h>

static long func_000005C8(VECTOR *in0, VECTOR *in1);
static long func_00000690(long number);

static void func_000004D0(VECTOR *in0, VECTOR *in1, GsRVIEWUNIT *out)
{
	int len;

	len = func_00000690(func_000005C8(in0, in1));
	if (len > 15) {
		len -= 15;

		out->vpx = in0->vx >> len;
		out->vpy = in0->vy >> len;
		out->vpz = in0->vz >> len;
		out->vrx = in1->vx >> len;
		out->vry = in1->vy >> len;
		out->vrz = in1->vz >> len;
	} else {
		out->vpx = in0->vx;
		out->vpy = in0->vy;
		out->vpz = in0->vz;
		out->vrx = in1->vx;
		out->vry = in1->vy;
		out->vrz = in1->vz;
	}
}
