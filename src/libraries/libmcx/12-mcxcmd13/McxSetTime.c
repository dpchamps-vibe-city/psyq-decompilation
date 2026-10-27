#include "common.h"
#include <libmcx.h>
#include "libmcx_internal.h"
#include "libmcx_transfer.h"

int McxSetTime(int port, unsigned char *time) {
    if (_mcxChkRsrv(port) == 0) {
        return 0;
    }
    _mcxParam = 0;
    _mcxPtrBuff = 0;
    _mcxPtrCmdBuf0 = (long *)B_00000170;
    _mcxDataLen = 0;
    _mcxFlag = 0;
    B_00000170[0] = time[3];
    B_00000170[1] = time[2];
    B_00000170[2] = time[1];
    B_00000170[3] = time[0];
    B_00000170[4] = time[7];
    B_00000170[5] = time[6];
    B_00000170[6] = time[5];
    B_00000170[7] = time[4] + 1;
    _mcxFuncNo = McxFuncSetTime;
    _mcxFuncGetTx = _mcxTxWriteDev;
    _mcxFuncApplyRx = _mcxRxWriteDev;
    _mcxStat = 2;
    return 1;
}
