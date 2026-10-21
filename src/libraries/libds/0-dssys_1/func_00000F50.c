#include "common.h"

static void func_00000F50(u8 arg0, u8 *arg1) {
    u8 temp_s0;

    temp_s0 = arg0 & 0xFF;
    func_00000FE4(temp_s0, arg1);
    if (D_00001240.status & 0x10) {
        D_00001240.system[0] = 2;
        D_00001240.system[1] = 0xC;
    }
    if ((B_000013A0 != 0) && (D_00001240.active != 0)) {
        B_000013A0(temp_s0, arg1);
    }
}
