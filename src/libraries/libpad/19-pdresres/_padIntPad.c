#include "common.h"
#include "libpad-sio.h"

int _padIntPad(void) {
    if (D_00001F70->control & 2) {
        D_00001F70->control = 0;
    } else {
        int first = _padChanStart;

        _padCalledIntPad = 1;
        if (first != 0 && _padRestPeriod[0] < 150) {
            _padRestPeriod[0]++;
        }
        if (_padChanStop == 0 && _padRestPeriod[1] < 150) {
            _padRestPeriod[1]++;
        }
        if (_padIntExec != 0 && _padChanStart <= _padChanStop) {
            _padSioState = 0;
            _padSioChan = _padChanStart;
            if (_padInitSioMode(&_padInfoDir[_padChanStart]) == 0) {
                _padFuncNextPort(0xFFFF);
            }
            _padTotalCurr = 0;
            while (_padChanStop >= _padSioChan) {
                func_000005AC(&_padInfoDir[_padSioChan]);
            }
            D_00001F70->baud = 0x88;
        }
    }
    return 0;
}
