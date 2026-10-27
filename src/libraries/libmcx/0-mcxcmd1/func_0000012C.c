/* Original member: LIBMCX.LIB[0] MCXCMD1.OBJ */
#include "common.h"
#include "libmcx_internal.h"

extern s32 _mcxRestSize;
extern s32 _mcxRxLen;

static s32 func_0000012C(s32 arg0) {
    switch (_mcxRxLen) {
    case 3:
        _mcxRestSize = arg0 & 0xFF;
        break;
    case 4:
        *_mcxPtrCmdBuf0 = (arg0 & 0xFF) << 8;
        break;
    case 5:
        *_mcxPtrCmdBuf0 += arg0 & 0xFF;
        break;
    }
    return 0;
}
