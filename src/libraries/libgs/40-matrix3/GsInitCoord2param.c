#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>

void GsInitCoord2param(GsCOORD2PARAM *param) {
    param->rotate.vz = 0;
    param->rotate.vy = 0;
    param->rotate.vx = 0;
    param->scale.vz = 0x1000;
    param->scale.vy = 0x1000;
    param->scale.vx = 0x1000;
    param->trans.vz = 0;
    param->trans.vy = 0;
    param->trans.vx = 0;
}
