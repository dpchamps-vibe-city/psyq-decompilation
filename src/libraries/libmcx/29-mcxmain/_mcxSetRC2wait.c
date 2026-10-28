#include "common.h"
#include "libmcx_main.h"

static void _mcxSetRC2wait(int delay) {
    unsigned short count;

    count = *(volatile unsigned short *)0x1F801120;
    (void)*(volatile unsigned short *)0x1F801124;
    B_0000070C = 0;
    B_00000708 = delay;
    B_00000704 = count;
}
