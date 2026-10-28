#include "common.h"
#include "libpad-sio.h"

void _padSetRC2wait(int count) {
    B_00001FA8 = count;
    B_00001FA4 = *(volatile u16 *)0x1F801120;
}
