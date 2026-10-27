#include "common.h"
#include "libmcx_transfer.h"

int _mcxRxSetMem(int value) {
    int rest;
    int rx;

    if (_mcxRxLen == 9) {
        _mcxRestSize = _mcxDataLen + 1;
    } else if (_mcxRxLen == 10) {
        if (_mcxRestSize >= 3) {
            _mcxStartFastDsr(1, _mcxPtrBuff + 1, _mcxRestSize - 2, &_mcxSum);
            rx = _mcxRxLen - 2;
            rest = _mcxRestSize;
            _mcxRestSize = 2;
            _mcxRxLen = rx + rest;
            _mcxTxLen -= 2;
            _mcxTxLen += rest;
        }
    }
    return 0;
}
