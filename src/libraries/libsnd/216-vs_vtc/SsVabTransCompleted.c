#include "common.h"

s16 SpuIsTransferCompleted(s16);                    /* extern */

s16 SsVabTransCompleted(s16 arg0) {
    return SpuIsTransferCompleted(arg0);
}
