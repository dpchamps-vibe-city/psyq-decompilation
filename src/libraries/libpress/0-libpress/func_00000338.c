#include "common.h"
#include <sys/types.h>
#include <stdio.h>

static void func_00000428(u32 *data, u32 words);
extern u32 D_00000758;
extern u32 D_000007DC;
extern s32 *D_00000870;
extern volatile u_long *D_0000087C;
extern volatile u32 *D_0000089C;
extern char RO_STR_00000708[];

static void func_00000338(int mode) {
    switch (mode) {
    case 0:
        *D_0000089C = 0x80000000;
        *D_00000870 = 0;
        *D_0000087C = 0;
        *D_0000089C = 0x60000000;
        func_00000428(&D_00000758, 32);
        func_00000428(&D_000007DC, 32);
        break;
    case 1:
        *D_0000089C = 0x80000000;
        *D_00000870 = 0;
        *D_0000087C = 0;
        (void)*D_0000087C;
        *D_0000089C = 0x60000000;
        break;
    default:
        printf(RO_STR_00000708, mode);
        break;
    }
}
