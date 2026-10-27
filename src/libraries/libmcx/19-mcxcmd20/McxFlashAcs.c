#include "common.h"
#include <libmcx.h>
#include "libmcx_internal.h"

static int func_000000E0(void);
extern s32 _mcxRxRestLen(s32 size);

int McxFlashAcs(int port, int onoff) {
    if (_mcxChkRsrv(port) == 0) {
        return 0;
    }
    _mcxParam = onoff != 0;
    _mcxFuncNo = McxFuncFlashAcs;
    _mcxFuncGetTx = func_000000E0;
    _mcxFuncApplyRx = _mcxRxRestLen;
    _mcxStat = 2;
    return 1;
}
