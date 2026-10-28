#include "libpad-enable-com.h"

unsigned PadEnableCom(unsigned enabled) {
    unsigned previous;

    previous = (_padChanStop * 2) | (_padChanStart == 0);
    if (previous == enabled) {
        return previous;
    }
    _padIntExec = 0;
    if (enabled & 1) {
        _padChanStart = 0;
        if (_padRestPeriod[0] >= 150) {
            _padFuncClrInfo(_padInfoDir);
        }
        _padRestPeriod[0] = 0;
    } else {
        _padChanStart = 1;
    }
    if (enabled & 2) {
        _padChanStop = 1;
        if (_padRestPeriod[1] >= 150) {
            _padFuncClrInfo(_padInfoDir + 1);
        }
        _padRestPeriod[1] = 0;
    } else {
        _padChanStop = 0;
    }
    _padIntExec = 1;
    return previous;
}
