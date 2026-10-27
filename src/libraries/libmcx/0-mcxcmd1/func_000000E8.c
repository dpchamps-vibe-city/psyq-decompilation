/* Original member: LIBMCX.LIB[0] MCXCMD1.OBJ */
#include "common.h"

extern s32 _mcxCmdSeq;

static s32 func_000000E8(void) {
    switch (_mcxCmdSeq) {
    case 2:
        return 0x59;
    case 4:
    case 5:
        return 0xFF;
    }
    return 0;
}
