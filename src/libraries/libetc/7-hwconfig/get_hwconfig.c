#include "common.h"

extern u32 D_000001C8;
extern u32 D_000001D8;
extern s16 D_000001DC[];

s32 get_hwconfig(s32 mode) {
    u32 addr;
    u32 end;
    u32 sum;
    s32 (*hook)(void);
    s32 ret;

    hook = *(s32(**)(void))0x4D0;
    if (hook != 0) {
        return hook();
    }

    sum = 0;
    addr = 0xBFC00000;
    end = 0xBFC04580;
    while (addr < end) {
        sum += *(u32 *)addr;
        addr += 4;
    }
    if (sum != 0x4A20382C) {
        return -1;
    }
    D_000001D8 = (u32)&D_000001C8;

    ret = 0;
    switch (mode) {
    case 0:
    case 1:
        ret = *(volatile u32 *)(0xBFC00100 + (mode << 2));
        break;
    case 2:
        ret = 0xBFC00129;
        break;
    case 5:
        ret = *(s32 *)0x60 << 10;
        break;
    case 3:
        ret = (*(s32(*)(void))D_000001D8)() & 0xFF;
        break;
    case 4:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
        ret = D_000001DC[mode];
        break;
    }
    return ret;
}
