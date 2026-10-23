#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>

void GsInitCoordinate2(GsCOORDINATE2 *super, GsCOORDINATE2 *base) {
    base->coord = GsIDMATRIX;
    base->super = super;
    base->flg = 0;
    if (super >= 2) {
        base->super->sub = base;
    }
}
