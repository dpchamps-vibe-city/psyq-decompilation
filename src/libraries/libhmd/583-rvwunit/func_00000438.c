#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>
#include <libhmd.h>

static s32 func_00000524(GsRVIEWUNIT *arg0);
static s32 func_000005EC(s32 arg0);

static void func_00000438(GsRVIEWUNIT *arg0, GsRVIEWUNIT *arg1)
{
    s32 shift;

    shift = func_000005EC(func_00000524(arg0));
    if (shift >= 0x10) {
        shift -= 15;
        arg1->vpx = arg0->vpx >> shift;
        arg1->vpy = arg0->vpy >> shift;
        arg1->vpz = arg0->vpz >> shift;
        arg1->vrx = arg0->vrx >> shift;
        arg1->vry = arg0->vry >> shift;
        arg1->vrz = arg0->vrz >> shift;
    } else {
        arg1->vpx = arg0->vpx;
        arg1->vpy = arg0->vpy;
        arg1->vpz = arg0->vpz;
        arg1->vrx = arg0->vrx;
        arg1->vry = arg0->vry;
        arg1->vrz = arg0->vrz;
    }
}
