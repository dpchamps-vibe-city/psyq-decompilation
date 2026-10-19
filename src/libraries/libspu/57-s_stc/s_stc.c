/* Original member: LIBSPU.LIB S_STC.OBJ */
#include "common.h"

extern s32 _spu_transferCallback;

void SpuSetTransferCallback(s32 func) {
    if (func != _spu_transferCallback) {
        _spu_transferCallback = func;
    }
}
