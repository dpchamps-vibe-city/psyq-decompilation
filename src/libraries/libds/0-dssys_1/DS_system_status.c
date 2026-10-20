#include "common.h"

extern s32 D_00001260[] __asm__("$LD_00001238+40");

s32 DS_system_status(s32 arg0) {
    return D_00001260[arg0];
}
