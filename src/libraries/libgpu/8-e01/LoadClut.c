#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

u_short LoadClut(u_long *clut, int x, int y) {
    RECT rect;

    rect.x = x;
    rect.y = y;
    rect.w = 0x100;
    rect.h = 1;
    LoadImage(&rect, clut);
    return GetClut(x, y);
}
