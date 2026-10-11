#include "common.h"

extern s32 GsOUT_PACKET_P;

s32 GsGetWorkBase(void) {
    return GsOUT_PACKET_P;
}
