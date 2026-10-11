#include "common.h"

s32 IsEndPrim(s32 *arg0) {
    return (*arg0 & 0xFFFFFF) == 0xFFFFFF;
}
