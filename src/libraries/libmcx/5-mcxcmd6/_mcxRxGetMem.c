#include "common.h"
#include "/home/dave/Documents/code/psyq-decomp/build/subagents/1ee81f42-552a-432b-877a-0498ed6fdc7f/162be034-3cb6-4afe-9532-c969c3cb7aa7/libmcx_transfer.h"

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
