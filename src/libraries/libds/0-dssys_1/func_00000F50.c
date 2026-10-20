#include "common.h"

void func_00000F50(u8 arg0, u8 *arg1) {
    u8 temp_s0;

    temp_s0 = arg0 & 0xFF;
    func_00000FE4(temp_s0, arg1);
    if (DDx.status & 0x10) {
        DDx.unk8 = 2;
        DDx.unkC = 0xC;
    }
    if ((B_000013A0 != 0) && (DDx.active != 0)) {
        B_000013A0(temp_s0, arg1);
    }
}
