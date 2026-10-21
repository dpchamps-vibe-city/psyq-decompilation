#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

extern s32 *D_00000270;
extern s32 *D_00000274;

s32 func_00000238(s32 arg0) {
    *D_00000274 = arg0 | 0x10000000;
    return *D_00000270 & 0xFFFFFF;
}
