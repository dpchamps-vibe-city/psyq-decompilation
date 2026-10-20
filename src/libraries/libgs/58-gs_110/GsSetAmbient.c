#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>

void GsSetAmbient(long r, long g, long b) {
    SetBackColor(r >> 4, g >> 4, b >> 4);
}
