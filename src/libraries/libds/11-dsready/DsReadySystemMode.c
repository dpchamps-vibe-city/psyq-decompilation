#include "common.h"

int DsReadySystemMode(int mode) {
    s32 temp_v0;

    temp_v0 = D_00000610.mode;
    D_00000610.mode = mode;
    return temp_v0;
}
