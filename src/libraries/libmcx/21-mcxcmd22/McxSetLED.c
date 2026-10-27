#include "common.h"
#include <libmcx.h>
#include "libmcx_internal.h"
#include "libmcx_transfer.h"

int _mcxTxSetMem(void);
int _mcxRxSetMem(int value);

int McxSetLED(int port, int onoff) {
    if (_mcxChkRsrv(port) == 0) {
        return 0;
    }
    _mcxParam = onoff != 0 ? 0x0D800008 : 0x0D800004;
    _mcxPtrBuff = (u8 *)&_mcxFlag;
    ((u8 *)&_mcxFlag)[0] = 2;
    _mcxDataLen = 1;
    _mcxFuncNo = 9;
    _mcxFuncGetTx = _mcxTxSetMem;
    _mcxFuncApplyRx = _mcxRxSetMem;
    _mcxStat = 2;
    return 1;
}
