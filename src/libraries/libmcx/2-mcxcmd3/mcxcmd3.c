/* Original member: LIBMCX.LIB[2] MCXCMD3.OBJ */
#include "common.h"

extern s32 _mcxRestSize;
extern s32 _mcxRxLen;

s32 _mcxRxRestLen(s32 size) {
    if (_mcxRxLen == 3) {
        _mcxRestSize = size & 0xFF;
    }
    return 0;
}
