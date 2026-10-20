#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>

extern s32 GsCLIP3far;
extern s32 GsCLIP3near;

void GsInit3D(void) {
    POSITION.offx = (s16) ((s32) (HWD0 + ((u32) HWD0 >> 0x1F)) >> 1);
    POSITION.offy = (s16) ((s32) VWD0 / 2);
    GsSetDrawBuffOffset();
    GsCLIP3near = 0xA;
    GsLIGHT_MODE = 0;
    GsCLIP3far = 0x3FFF;
}
