#include "common.h"
#include "libpad-sio.h"

int _padInitSioMode(PadInfo2 *arg0) {
    PadSioRegisters *sio;

    sio = D_00001F70;
    sio->control = 0x40;
    sio->control = 0;
    sio->mode = 0xD;
    sio->baud = 0x88;

    if (arg0->mtapType == 8) {
        _padSetRC2wait(0x50);
    } else {
        _padSetRC2wait(0x91);
    }

    D_00001F70->control = (_padSioChan != 0) ? 0x3003 : 0x1003;

    if (_padFixResult[_padSioChan] >= 0) {
        while (_padFixResult[_padSioChan] > 0) {
            _padFuncRecvAuto(&arg0->child[--_padFixResult[_padSioChan]]);
        }
        if (_padFixResult[_padSioChan] == 0) {
            _padFixResult[_padSioChan] = -1;
            _padFuncRecvAuto(arg0);
            _padFuncClrCmdNo(arg0);
        }
    }

    if (D_00001F70->status & 0x200) {
        D_00001F70->control |= 0x10;
        if (D_00001F70->status & 0x200) {
            while (_padChkRC2wait() == 0)
                ;
            D_00001F70->data = 1;
            _padSetRC2wait(0x7D0);
            if (_padClrIntSio0() == 0) {
                return 0;
            }
            _padWaitRXready();
            (void)D_00001F70->data;
            _padSetRC2wait(0x1AE);

            while ((D_00001F6C[0] & 0x80) == 0) {
                if (_padChkRC2wait() != 0) {
                    return 0;
                }
            }
            D_00001F70->data = 0x42;
            _padSetRC2wait(0x3C);
            if (_padClrIntSio0() == 0) {
                return 0;
            }
            _padWaitRXready();
            (void)D_00001F70->data;
            _padSetRC2wait(0x1AE);

            while ((D_00001F6C[0] & 0x80) == 0) {
                if (_padChkRC2wait() != 0) {
                    return 0;
                }
            }
            D_00001F70->data = 1;
            _padSetRC2wait(0x3C);
            if (_padClrIntSio0() == 0) {
                return 0;
            }
            _padWaitRXready();
            (void)D_00001F70->data;
            return 0;
        }
        D_00001F6C[0] = -0x81;
    }

    if (arg0->pad50 != 0 && arg0->requestCommand != 0) {
        return 0;
    }
    return 1;
}
