#include "common.h"
#include <libmcx.h>
#include "libmcx_internal.h"
#include "libmcx_transfer.h"

static int func_00000110(void);
extern s32 _mcxRxRestLen(s32 size);

int McxCurrCtrl(int port, int param, int dataLen, int flag) {
    if (_mcxChkRsrv(port) == 0) {
        return 0;
    }
    _mcxParam = param != 0;
    _mcxDataLen = dataLen != 0;
    _mcxFlag = flag != 0;
    _mcxFuncNo = McxFuncCurrCtrl;
    _mcxFuncGetTx = func_00000110;
    _mcxFuncApplyRx = _mcxRxRestLen;
    _mcxStat = 2;
    return 1;
}
