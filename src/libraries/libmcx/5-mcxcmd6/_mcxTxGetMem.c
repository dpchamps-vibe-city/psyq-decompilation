#include "common.h"
#include "libmcx_internal.h"
#include "libmcx_transfer.h"

int _mcxTxGetMem(void) {
    switch (_mcxCmdSeq) {
    case 2:
        return 0x5B;
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
    }
    return 0;
}
