#include "common.h"
#include "libmcx_cmd15.h"

static s32 func_00000128(void) {
    if (_mcxPass == 1) {
        switch (_mcxCmdSeq) {
        case 2:
            return 0x5C;
        case 3:
            return _mcxParam;
        }
        if (_mcxCmdSeq < 5) {
            return 0;
        }
        if (_mcxFlag == 0) {
            if (_mcxCmdSeq < _mcxDataLen + 5) {
                return _mcxPtrBuff[_mcxCmdSeq - 5];
            }
            return 0;
        }
        return _mcxPtrBuff[_mcxCmdSeq - _mcxDataLen - 6];
    }
    switch (_mcxCmdSeq) {
    case 2:
        return 0x59;
    case 4:
    case 5:
        if (_mcxPass == 4) {
            return 0xFF;
        }
        return 0;
    case 6:
        return 0x20;
    case 7:
        if (_mcxPass != 0) {
            return 1;
        }
    default:
        return 0;
    }
}
