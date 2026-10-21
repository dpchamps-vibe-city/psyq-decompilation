#include "common.h"

void DsReadMode(u32 mode) {
    if (mode < 2) {
        D_00000580.mode = mode;
    }
}
