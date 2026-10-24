#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>
#include <abs.h>

static s32 func_00000524(GsRVIEW2 *arg0)
{
    s32 max;
    s32 cur;

    max = ABS(arg0->vpx);
    cur = ABS(arg0->vpy);
    if (max < cur) {
        max = cur;
    }
    cur = ABS(arg0->vpz);
    if (max < cur) {
        max = cur;
    }
    cur = ABS(arg0->vrx);
    if (max < cur) {
        max = cur;
    }
    cur = ABS(arg0->vry);
    if (max < cur) {
        max = cur;
    }
    cur = ABS(arg0->vrz);
    if (max < cur) {
        max = cur;
    }
    return max;
}
