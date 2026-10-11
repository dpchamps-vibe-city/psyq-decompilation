#include "common.h"

extern s32 _spu_inTransfer;

s32 _spu_getInTransfer(void) {
    return _spu_inTransfer != 1;
}
