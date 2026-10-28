#include "common.h"
#include "libpad-sio.h"

static void func_000005AC(PadInfo2 *info) {
    int ret;

    ret = D_00001F80[_padSioState++](info);
    if (ret >= 0) {
        if (_padSioState != 0 && (_padSioState != 3 || *info->data3C != 0x80)) {
            _padSetRC2wait(0x3C);
            if (_padClrIntSio0() == 0) {
                _padFuncNextPort(-3);
            }
        }
        if (_padSioState >= 5) {
            _padSioState--;
        }
    } else {
        _padFuncNextPort(ret);
    }
}
