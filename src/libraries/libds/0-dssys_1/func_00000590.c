#include "common.h"

/* D_00001240.timeout under its own label: this function's original code never
   addresses the word from the state block's base, as a shared symbol makes GCC do. */
extern s32 D_00001284;

static s32 func_000003B8(u8, u8 *);
static s32 func_00000860();

static void func_00000590(u8 arg0, u8 *arg1, s32 *arg2, s32 *arg3) {
    u8 sp10;
    s32 *p;
    u8 *q;

    p = &D_00001284;
    if (*p > 0) {
        *p = *p - 1;
        if (*p == 0) {
            func_00000860();
            return;
        }
    }
    if (D_00001240.unk40 > 0) {
        D_00001240.unk40 = D_00001240.unk40 - 1;
    }
    if (D_00001240.unk4C > 0) {
        D_00001240.unk4C = D_00001240.unk4C - 1;
    }
    if (D_00001240.system[0] == 1) {
    } else if (D_00001240.system[0] == 2) {
        if (D_00001240.system[1] != 0xB) {
            if (D_00001240.system[1] == 0xC) {
                if (D_00001394 != 0) {
                    q = &sp10;
                    sp10 = 0;
                    if (D_00001284 <= 0) {
                        D_00001240.unk1C = 0x20;
                        func_000003B8(0xEU, q);
                    }
                    D_00001394 = 0;
                } else {
                    if (D_00001284 <= 0) {
                        D_00001240.unk1C = 0x20;
                        func_000003B8(1U, 0);
                    }
                    D_00001394 = 1;
                }
            } else if (D_00001240.system[1] == 0xD) {
                D_00001394 = 0;
                if (D_00001284 <= 0) {
                    D_00001240.unk1C = 0x20;
                    func_000003B8(1U, 0);
                }
            } else if (D_00001240.system[1] == 0xE) {
                if (D_00001240.system[2] == 0x15) {
                    if (D_00001284 <= 0) {
                        D_00001240.unk1C = 0x20;
                        func_000003B8(1U, 0);
                    }
                } else if (D_00001240.system[2] == 0x16) {
                    D_00001240.unk38 = D_00001240.unk38 + 1;
                    if (D_00001284 <= 0) {
                        D_00001240.unk1C = 0x20;
                        func_000003B8(1U, 0);
                    }
                } else if (D_00001240.system[2] == 0x17) {
                    if (D_00001284 <= 0) {
                        D_00001240.unk1C = 0x20;
                        func_000003B8(0x13U, 0);
                    }
                } else if (D_00001240.system[2] == 0x18) {
                    if (D_00001284 <= 0) {
                        D_00001240.unk1C = 0x20;
                        func_000003B8(1U, 0);
                    }
                }
            } else if (D_00001240.system[1] == 0xF) {
                if (D_00001240.unk40 == 0) {
                    D_00001240.system[0] = 1;
                    D_00001240.system[1] = 0xB;
                }
            } else if (D_00001240.system[1] == 0x10) {
                if (D_00001240.flags[0] != 0) {
                    D_00001240.system[0] = 1;
                    D_00001240.system[1] = 0xB;
                } else {
                    if (D_00001284 <= 0) {
                        D_00001240.unk1C = 0x20;
                        func_000003B8(1U, 0);
                    }
                }
            } else if (D_00001240.system[1] == 0x11) {
                if (D_00001240.flags[2] != 0) {
                    D_00001240.system[0] = 1;
                    D_00001240.system[1] = 0xB;
                } else {
                    if (D_00001284 <= 0) {
                        D_00001240.unk1C = 0x20;
                        func_000003B8(1U, 0);
                    }
                }
            }
        }
    }
    if ((B_00001398 != 0) && (D_00001240.active != 0)) {
        ((void (*)()) B_00001398)();
    }
    if ((((D_00001240.system[0] == 1) && (D_00001240.flags[3] == 0)) || (D_00001240.system[0] == 3)) && (D_00001284 <= 0)) {
        D_00001240.unk1C = 0x21;
        func_000003B8(1U, 0);
    }
}
