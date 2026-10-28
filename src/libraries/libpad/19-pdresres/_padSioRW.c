#include "common.h"
#include "libpad-sio.h"

int _padSioRW(PadInfo2 *info, int data) {
    int recv;
    int len;
    int type;
    int value;

    if (data < 0) {
        recv = D_00001F70->data & 0xFF;
        info->pad44[0] = 0xFF;
        info->pad44[1] = 1;
        info->data40[0] = ~data;
        if (!(D_00001F70->status & 1)) {
            do {
            } while (!(D_00001F70->status & 1));
        }
        while (_padChkRC2wait() == 0) {
        }
        D_00001F70->data = ~data;
    } else {
    len = 0x88;
    type = info->data3C[0];
    if ((type >> 4) == 8) {
        if (info->pad44[0] >= 9) {
            len = 0x22;
        }
    }

    B_00001FA8 = 0x1AE;
    B_00001FA4 = *(volatile u16 *)0x1F801120;
    B_00001FAC = *(volatile u16 *)0x1F801124;
    while (!(D_00001F70->status & 2)) {
    }

    recv = D_00001F70->data & 0xFF;
    D_00001F70->baud = len;
    while (!(D_00001F6C[0] & 0x80)) {
        if (_padChkRC2wait() != 0) {
            return -0x14;
        }
    }
    D_00001F70->data = data;
    if (len == 0x22) {
        volatile u32 *intr = D_00001F6C;
        PadSioRegisters *sio = D_00001F70;

        intr[0] = -0x81;
        sio->control |= 0x10;
    }
    info->pad44[1]++;
    info->data3C[info->pad44[0]] = recv;
    info->pad44[0]++;
    }
    return recv;
}
