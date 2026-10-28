#include "common.h"
#include <libmcx.h>
#include "libmcx_command_setup.h"

int McxGetUIFS(int port, unsigned char *buf) {
    if (_mcxChkRsrv(port) == 0) {
        return 0;
    }
    _mcxParam = 2;
    _mcxFuncNo = McxFuncGetUIFS;
    _mcxFuncGetTx = _mcxTxReadDev;
    _mcxPtrBuff = 0;
    _mcxPtrCmdBuf0 = (long *)buf;
    _mcxDataLen = 0;
    _mcxFlag = 0;
    _mcxFuncApplyRx = _mcxRxReadDev;
    _mcxStat = 2;
    return 1;
}
