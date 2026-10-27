#include "common.h"

extern volatile s32 _mcxCmdSeq;
extern s32 _mcxParam;
extern u8 *_mcxPtrBuff;

static s32 func_00000114(void) {
    switch (_mcxCmdSeq) {
    case 2:
        return 0x59;
    case 4:
        return ((u8 *)&_mcxParam)[1];
    case 5:
        return ((u8 *)&_mcxParam)[0];
    }
    if (_mcxCmdSeq >= 6) {
        if (_mcxCmdSeq < 10) {
            return _mcxPtrBuff[_mcxCmdSeq - 6];
        }
    }
    return 0;
}
