#include "common.h"
#include "libmcx.h"
#include "libmcx_command_setup.h"

static int func_00000100(void);
static int func_00000124(int value);

int McxGetInfo(int port, long *cmdBuf0, long *cmdBuf1) {
    if (_mcxChkRsrv(port) == 0) {
        return 0;
    }
    _mcxFuncNo = 0x64;
    _mcxFuncGetTx = func_00000100;
    _mcxFuncApplyRx = func_00000124;
    _mcxPtrCmdBuf0 = cmdBuf0;
    _mcxPtrCmdBuf1 = cmdBuf1;
    _mcxStat = 2;
    return 1;
}
