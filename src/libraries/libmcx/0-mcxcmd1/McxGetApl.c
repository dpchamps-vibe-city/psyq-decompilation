#include "common.h"
#include <libmcx.h>
#include "libmcx_internal.h"

static int func_000000E8(void);
static int func_0000012C(int);

int McxGetApl(int port, long *applications) {
    if (_mcxChkRsrv(port) == 0) {
        return 0;
    }
    _mcxParam = -1;
    _mcxFuncNo = McxFuncGetApl;
    _mcxFuncGetTx = func_000000E8;
    _mcxFuncApplyRx = func_0000012C;
    _mcxPtrCmdBuf0 = applications;
    _mcxStat = 2;
    return 1;
}
