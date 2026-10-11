#include "common.h"

extern s32 _spu_transferCallback;

void SpuSetTransferCallback(s32 arg0) {
    if (arg0 != _spu_transferCallback) {
        _spu_transferCallback = arg0;
    }
}
