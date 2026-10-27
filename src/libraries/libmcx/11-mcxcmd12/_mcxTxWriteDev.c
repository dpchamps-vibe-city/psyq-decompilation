/* Original member: LIBMCX.LIB[11] MCXCMD12.OBJ */
#include "common.h"

extern volatile s32 _mcxCmdSeq;
extern s32 _mcxParam;
extern u8 *_mcxPtrBuff;
extern s32 _mcxFlag;
extern s32 _mcxDataLen;

s32 _mcxTxWriteDev(void) {
    switch (_mcxCmdSeq) {
    case 2:
        return 0x5C;
    case 3:
        return _mcxParam;
    case 5:
        return *_mcxPtrBuff;
    }
    if (_mcxCmdSeq >= 5) {
        if (_mcxFlag == 0) {
            if (_mcxCmdSeq < _mcxDataLen + 5) {
                return _mcxPtrBuff[_mcxCmdSeq - 5];
            }
        } else {
            return _mcxPtrBuff[_mcxCmdSeq - _mcxDataLen - 6];
        }
    }
    return 0;
}
