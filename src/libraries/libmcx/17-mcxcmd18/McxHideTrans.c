#include "common.h"
#include <libmcx.h>
#include "libmcx_internal.h"

extern int _mcxFlag;
extern int _mcxTxSetTrans(void);
extern s32 _mcxRxRestLen(s32 size);

int McxHideTrans(int port) {
    if (_mcxChkRsrv(port) == 0) {
        return 0;
    }
    _mcxFlag = 1;
    _mcxFuncNo = 7;
    _mcxFuncGetTx = _mcxTxSetTrans;
    _mcxFuncApplyRx = _mcxRxRestLen;
    _mcxStat = 2;
    return 1;
}
