#include "common.h"
#include "libmcx_main.h"

int _mcxSioRW(int data) {
    volatile unsigned short *sio;
    int succeeded;

    sio = D_000006F0;
    B_00000700 = *(volatile unsigned char *)sio;
    if (data < 0) {
        while (!(D_000006F0[2] & 1)) {
        }
        while (!_mcxChkRC2wait()) {
        }
        *(volatile unsigned char *)D_000006F0 = ~data;
    } else {
        int (*check_timeout)(void);
        unsigned short count;
        volatile unsigned int *irq;
        volatile unsigned short *poll_sio;
        volatile unsigned short *control_sio;

        *(volatile unsigned char *)sio = data;
        count = *(volatile unsigned short *)0x1F801120;
        (void)*(volatile unsigned short *)0x1F801124;
        B_0000070C = 0;
        irq = D_000006F4;
        poll_sio = D_000006F0;
        *irq = ~0x80;
        B_00000708 = 0x3C;
        B_00000704 = count;
        if (poll_sio[2] & 0x80) {
            do {
                if ((check_timeout = _mcxChkRC2wait)()) {
                    succeeded = 0;
                    goto complete;
                }
            } while (D_000006F0[2] & 0x80);
        }
        control_sio = D_000006F0;
        control_sio[5] |= 0x10;
        succeeded = 1;
complete:
        if (!succeeded) {
            return -0x300 - B_00000700;
        }
    }
    return B_00000700;
}
