#include "common.h"
#include "libmcx_transfer.h"

#include "libmcx_command_bytes.h"

int _mcxTxSetMem(void) {
    switch (_mcxCmdSeq) {
    case 2:
        return 0x5C;
    case 3:
        return 1;
    case 5:
        return ((u8 *)&_mcxParam)[0];
    case 6:
        return ((u8 *)&_mcxParam)[1];
    case 7:
        return ((u8 *)&_mcxParam)[2];
    case 8:
        return ((u8 *)&_mcxParam)[3];
    case 9:
        return _mcxDataLen;
    default:
        return _mcxPtrBuff[_mcxCmdSeq - 11];
    case 4:
    case 10:
        return 0;
    }
}
