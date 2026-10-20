#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>
#include <libhmd.h>

u_long *GsU_07000100(GsARGUNIT *arg0) {
    SetGeomScreen(*(*(s32 **) ((u8 *) arg0 + 0x14)));
    return (arg0->primp + 1);
}
