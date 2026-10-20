#include "common.h"
#include <sys/types.h>

extern s32 CChannel;
extern s32 StCHANNEL;
extern s16 Stsector_offset;

s32 StSetChannel(u_long arg0) {
    if (arg0 >= 0x20U) {
        return 1;
    }
    StCHANNEL = arg0;
    if (Stsector_offset != 0) {
        return 0;
    }
    CChannel = arg0;
    return 0;
}
