#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>

void GsSetOrign(long x, long y) {
    POSITION.offx = (s16) x;
    POSITION.offy = (s16) y;
}
