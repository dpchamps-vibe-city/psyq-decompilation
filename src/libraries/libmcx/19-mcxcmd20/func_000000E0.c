/* Original member: LIBMCX.LIB[19] MCXCMD20.OBJ */
#include "common.h"
#include "libmcx_internal.h"

static s32 func_000000E0(void) {
    switch (_mcxCmdSeq) {
    case 2:
        return 0x5F;
    case 4:
        return _mcxParam;
    }
    return 0;
}
