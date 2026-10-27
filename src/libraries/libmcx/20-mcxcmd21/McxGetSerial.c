#include "common.h"
#include <libmcx.h>
#include "libmcx_internal.h"
#include "libmcx_transfer.h"

extern int _mcxTxGetMem(void);
extern int _mcxRxGetMem(int value);

int McxGetSerial(int port, unsigned long *buff) {
    if (_mcxChkRsrv(port) == 0) {
        return 0;
    }
    _mcxParam = 0x6000300;
    _mcxDataLen = 4;
    _mcxFuncNo = McxFuncGetSerial;
    _mcxFuncGetTx = _mcxTxGetMem;
    _mcxFuncApplyRx = _mcxRxGetMem;
    _mcxPtrBuff = (unsigned char *)buff;
    _mcxStat = 2;
    return 1;
}
