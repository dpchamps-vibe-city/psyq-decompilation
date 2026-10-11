#include "common.h"

extern s32 _mcxRestSize;
extern s32 _mcxRxLen;

s32 _mcxRxRestLen(s32 arg0) {
    if (_mcxRxLen == 3) {
        _mcxRestSize = arg0 & 0xFF;
    }
    return 0;
}
