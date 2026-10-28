#include "common.h"
#include "libpad-sio.h"

int _padClrIntSio0(void)
{
    PadSioRegisters *sio;
    volatile u32 *intr;

    intr = D_00001F6C;
    sio = D_00001F70;
    *intr = -0x81;
    if (sio->status & 0x80) {
        do {
            if (_padChkRC2wait()) {
                return 0;
            }
        } while (D_00001F70->status & 0x80);
    }
    D_00001F70->control |= 0x10;
    return 1;
}
