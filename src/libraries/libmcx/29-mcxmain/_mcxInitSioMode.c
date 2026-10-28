#include "common.h"
#include "libmcx_main.h"

/* MCXMAIN private timer helper reads only a0. */
static void _mcxSetRC2wait(int delay);

int _mcxInitSioMode(int mode) {
    volatile unsigned short *sio;
    unsigned short control;

    D_000006F0[5] = 0;
    _mcxSetRC2wait(0x91);
    sio = D_000006F0;
    control = 0x1003;
    if (mode != 0) {
        control = 0x3003;
    }
    sio[5] = control;
    if (sio[2] & 0x200) {
        sio[5] |= 0x10;
        if (sio[2] & 0x200) {
            *(volatile unsigned char *)sio = 1;
            sio = D_000006F0;
            while (!(sio[2] & 2)) {
            }
            (void)*(volatile unsigned char *)D_000006F0;
            return 0;
        }
        D_000006F4[0] = ~0x80;
    }
    return 1;
}
