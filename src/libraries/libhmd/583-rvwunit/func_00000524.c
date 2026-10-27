#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>
#include <libhmd.h>
#include <abs.h>

static s32 func_00000524(GsRVIEWUNIT *arg0) {
    s32 m;
    s32 v;

    m = ABS(arg0->vpx);
    v = ABS(arg0->vpy);
    if (m < v)
        m = v;
    v = ABS(arg0->vpz);
    if (m < v)
        m = v;
    v = ABS(arg0->vrx);
    if (m < v)
        m = v;
    v = ABS(arg0->vry);
    if (m < v)
        m = v;
    v = ABS(arg0->vrz);
    if (m < v)
        m = v;
    return m;
}
