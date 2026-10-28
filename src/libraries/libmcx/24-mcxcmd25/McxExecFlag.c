#include "common.h"
#include <libmcx.h>
#include "libmcx_internal.h"
#include "libmcx_transfer.h"

static int func_00000104(void);
static int func_000002AC(int);

int McxExecFlag(int port, int application, int enabled) {
    _mcxParam = application;
    if (application < 1 || application > 15) {
        return 0;
    }
    if (_mcxChkRsrv(port) == 0) {
        return 0;
    }
    _mcxFlag = enabled != 0;
    _mcxFuncNo = McxFuncExecFlag;
    _mcxFuncGetTx = func_00000104;
    _mcxFuncApplyRx = func_000002AC;
    _mcxPass = 1;
    _mcxStat = 2;
    return 1;
}
