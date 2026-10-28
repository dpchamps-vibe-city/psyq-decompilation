#include "common.h"
#include "libmcx_main.h"

int _mcxChkRC2wait(void) {
    int mode;
    int count;

    mode = *(volatile unsigned short *)0x1F801124 & 0xFFFF;
    count = *(volatile unsigned short *)0x1F801120 & 0xFFFF;
    if (mode & 0x1000) {
        B_0000070C += 0x10000;
    } else if ((mode & 0x808) == 0x808) {
        B_0000070C += *(volatile unsigned short *)0x1F801128;
    }
    if (mode & 0x200) {
        return !(count + B_0000070C - B_00000704 < B_00000708);
    }
    return !(count + B_0000070C - B_00000704 < (B_00000708 << 3));
}
