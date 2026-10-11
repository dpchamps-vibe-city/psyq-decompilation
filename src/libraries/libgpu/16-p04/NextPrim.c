#include "common.h"

s32 NextPrim(s32 *arg0) {
    return (*arg0 & 0xFFFFFF) | 0x80000000;
}
