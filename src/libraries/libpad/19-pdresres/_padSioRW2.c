#include "common.h"
#include "libpad-sio.h"

int _padSioRW2(PadInfo2 *pad, s32 data) {
    u16 baud;
    s32 rev;
    s32 type;
    s32 now;

    type = *pad->data3C;
    baud = 0x88;
    if (((type >> 4) == 8) && (pad->pad44[0] >= 9U)) {
        baud = 0x22;
    } else {
        baud = 0x88;
    }
    while (!(D_00001F70->status & 2))
        ;
    _padSetRC2wait(0x190);
    rev = D_00001F70->data & 0xFF;
    if ((pad->pad44[0] != 0) || ((rev >> 4) != 8)) {
        D_00001F70->baud = baud;
    } else {
        D_00001F70->baud = 0x22;
    }
    if (!(D_00001F6C[0] & 0x80)) {
        for (;;) {
            (void)*(volatile u16 *)0x1F801124;
            now = *(volatile u16 *)0x1F801120 & 0xFFFF;
            if (now < B_00001FA4) {
                if (*(volatile u16 *)0x1F801128 != 0) {
                    now += *(volatile u16 *)0x1F801128;
                } else {
                    now += 0x10000;
                }
            }
            if (*(volatile u16 *)0x1F801124 & 0x200) {
                if ((now - B_00001FA4) >= B_00001FA8) {
                    return -2;
                }
            } else {
                if (((now - B_00001FA4) >> 3) >= B_00001FA8) {
                    return -2;
                }
            }
            if (D_00001F6C[0] & 0x80) {
                break;
            }
        }
    }
    if ((pad->mtapType != 8) && (_padSioState == 2)) {
        _padSetRC2wait(0x3C);
        while (_padChkRC2wait() == 0)
            ;
    }
    D_00001F70->data = data;
    if ((_padSioState == 3) && (rev == 0x80)) {
        PadSioRegisters *sio;
        volatile u32 *intr;

        intr = D_00001F6C;
        sio = D_00001F70;
        intr[0] = -0x81;
        sio->control |= 0x10;
    }
    pad->pad44[1]++;
    if (pad->pad44[0] != 0xFF) {
        pad->data3C[pad->pad44[0]] = rev;
    }
    pad->pad44[0]++;
    return rev;
}
