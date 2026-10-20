#include "common.h"

typedef struct {
    u8 pad0[0x0C];
    u8 command;
    u8 pad1[0x0B];
    u8 result[8];
    u8 status;
    u8 pad2[0x1B];
    u8 flags[4];
} DsDataFe4;

extern DsDataFe4 DDf __asm__("$LD_00001238");
extern s32 D_00001314[] __asm__("$LD_00001238+220");

extern void rescpy(u8 *dst, u8 *src);

void func_00000FE4(u8 arg0, u8 *arg1) {
    u8 *p;
    s32 n;
    u8 status;

    if ((arg0 & 0xFF) != 5) {
        n = D_00001314[DDf.command] - 1;
        if (n < 0) {
            return;
        }
    } else {
        n = 0;
    }
    p = arg1 + n;
    status = *p;
    DDf.flags[0] = status >> 7;
    DDf.flags[1] = (status >> 6) & 1;
    DDf.flags[2] = (status >> 5) & 1;
    DDf.flags[3] = (status >> 1) & 1;
    DDf.status = status;
    rescpy(DDf.result, arg1);
}
