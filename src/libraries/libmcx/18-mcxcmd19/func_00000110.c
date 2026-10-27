/* Original member: LIBMCX.LIB[18] MCXCMD19.OBJ */
#include "common.h"
#include "libmcx_internal.h"
#include "libmcx_transfer.h"

static s32 func_00000110(void) {
    switch (_mcxCmdSeq) {
    case 2:
        return 0x5E;
    case 4:
        return _mcxParam;
    case 5:
        return _mcxDataLen;
    case 6:
        return _mcxFlag;
    }
    return 0;
}
