#include "common.h"
#include <libmcx.h>
#include "/home/dave/Documents/code/psyq-decomp/build/subagents/1ee81f42-552a-432b-877a-0498ed6fdc7f/3efb7971-b300-435e-9e37-bf2e95636e5a/libmcx_internal.h"

static int func_000000E8(void);
static int func_0000012C(int);

int McxGetApl(int port, long *applications) {
    if (_mcxChkRsrv() == 0) {
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
