#include "common.h"
#include "libmcx.h"
#include "libmcx_command_setup.h"

int McxSetMem(int port, unsigned char *buf, unsigned len, unsigned offset) {
    if (chkMemArea(1, len)) {
        if (chkMemArea(1, len + offset - 1)) {
            if (_mcxChkRsrv(port)) {
                _mcxFuncNo = McxFuncSetMem;
                _mcxFuncGetTx = _mcxTxSetMem;
                _mcxFuncApplyRx = _mcxRxSetMem;
                _mcxPtrBuff = buf;
                _mcxParam = len;
                _mcxDataLen = offset;
                _mcxStat = 2;
                return 1;
            }
        }
    }
    return 0;
}
