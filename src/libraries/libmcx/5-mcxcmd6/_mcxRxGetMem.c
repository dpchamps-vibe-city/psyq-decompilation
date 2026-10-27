#include "common.h"
#include "libmcx_transfer.h"

int _mcxRxGetMem(unsigned char value) {
    int rest;
    int rx;

    if (_mcxRxLen == 9) {
        _mcxRestSize = _mcxDataLen + 1;
    } else if (_mcxRxLen == 10) {
        if (_mcxRestSize >= 3) {
            _mcxStartFastDsr(0, _mcxPtrBuff, _mcxRestSize - 2, &_mcxSum);
            rx = _mcxRxLen - 2;
            rest = _mcxRestSize;
            _mcxRestSize = 2;
            _mcxRxLen = rx + rest;
            _mcxTxLen -= 2;
            _mcxTxLen += rest;
        }
    } else if (_mcxRxLen >= 11) {
        _mcxPtrBuff[_mcxRxLen - 11] = value;
    }
    return 0;
}
