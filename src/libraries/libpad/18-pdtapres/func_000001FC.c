#include "common.h"
#include "libpad-mtap.h"
#include "libpad-enable-com.h"

void func_000001FC(int result) {
    PadInfo2 *info;
    u32 base;
    int *last;
    int chan;
    int next;
    int status;
    int nofail;
    int *fix;

    base = (u32)B_000011C0;
    last = _mtapLastResult;
    nofail = -9;
    fix = _padFixResult;
    do {
        chan = _padSioChan;
        *(volatile u16 *)(D_000011B8 + 0xA) = 0;
        last[chan] = result;
        info = (PadInfo2 *)(chan * sizeof(PadInfo2) + base);
        if (result != nofail) {
            if (result == 0) {
                fix[chan] = (((*info->data3C) >> 4) == 8) << 2;
            } else {
                _mtapFailAuto(info, result);
            }
        }
        _padSioState = 0;
        next = _padSioChan + 1;
        _padSioChan = next;
        if (_padChanStop >= next) {
            status = _padInitSioMode((PadInfo2 *)(next * sizeof(PadInfo2) + base));
            result = 0xFFFF;
        } else {
            status = 1;
            result = 0xFFFF;
        }
    } while (status == 0);
}
