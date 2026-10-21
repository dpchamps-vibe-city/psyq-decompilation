#include "common.h"

extern s32 D_000000A0;

long SetVideoMode(long mode) {
    s32 temp_v0;

    temp_v0 = D_000000A0;
    D_000000A0 = mode;
    return temp_v0;
}
