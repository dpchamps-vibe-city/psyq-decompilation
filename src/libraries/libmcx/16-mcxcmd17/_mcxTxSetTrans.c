#include "common.h"
#include "libmcx_internal.h"
#include "libmcx_transfer.h"

int _mcxTxSetTrans(void) {
    switch (_mcxCmdSeq) {
    case 2:
        return 0x5D;
    case 4:
        return _mcxParam;
    case 5:
        return _mcxFlag;
    case 6:
        return _mcxDataLen;
    }
    return 0;
}
