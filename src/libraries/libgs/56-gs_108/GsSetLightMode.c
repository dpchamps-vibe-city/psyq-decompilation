#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>
#include <stdio.h>

extern char RO_STR_000000F0[];

void GsSetLightMode(int mode) {
    switch (mode) {
    case 0:
        GsLIGHT_MODE = 0;
        break;
    case 1:
        GsLIGHT_MODE = mode;
        break;
    case 2:
        GsLIGHT_MODE = mode;
        break;
    case 3:
        GsLIGHT_MODE = mode;
        break;
    default:
        printf(RO_STR_000000F0, mode);
        break;
    }
}
