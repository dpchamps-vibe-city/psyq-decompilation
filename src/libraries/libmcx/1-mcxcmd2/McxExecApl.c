#include "common.h"
#include <libmcx.h>
#include "libmcx_internal.h"

static int func_00000114(void);
extern int _mcxFlag;
extern u8 *_mcxPtrBuff;
extern s32 _mcxRxRestLen(s32 size);

int McxExecApl(int port, int param, long flag) {
    if (param >= 0) {
        if (param < 16) {
            _mcxParam = param;
        } else {
            return 0;
        }
    } else {
        _mcxParam = -2;
    }
    if (_mcxChkRsrv(port) == 0) {
        return 0;
    }
    _mcxPtrBuff = (u8 *)&_mcxFlag;
    _mcxFuncGetTx = func_00000114;
    _mcxFlag = flag;
    _mcxFuncNo = McxFuncExecApl;
    _mcxFuncApplyRx = _mcxRxRestLen;
    _mcxStat = 2;
    return 1;
}
