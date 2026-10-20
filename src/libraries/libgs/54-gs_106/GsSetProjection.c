#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>

void GsSetProjection(long h) {
    SetGeomScreen(h);
}
