#include "common.h"
#include <libmcx.h>
#include "libmcx_command_setup.h"

extern int _mcxTxSetTrans(void);
extern s32 _mcxRxRestLen(s32 size);

int McxShowTrans(int port, int param, int len) {
    if (_mcxChkRsrv(port) == 0) {
        return 0;
    }
    _mcxFuncNo = 6;
    _mcxFuncGetTx = _mcxTxSetTrans;
    _mcxFuncApplyRx = _mcxRxRestLen;
    _mcxParam = param;
    _mcxDataLen = len;
    _mcxFlag = 0;
    _mcxStat = 2;
    return 1;
}
