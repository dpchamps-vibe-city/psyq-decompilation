#include "common.h"

extern s32 D_00001394 __asm__("D_00001238+348");
extern s32 D_00001284 __asm__("D_00001238+76");
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
    if (LD_00001258.unk28 > 0) {
        LD_00001258.unk28 = LD_00001258.unk28 - 1;
    }
    if (LD_00001258.unk34 > 0) {
        LD_00001258.unk34 = LD_00001258.unk34 - 1;
    }
    if (LD_00001258.unk8 == 1) {
    } else if (LD_00001258.unk8 == 2) {
        if (LD_00001258.unkC != 0xB) {
            if (LD_00001258.unkC == 0xC) {
                if (D_00001394 != 0) {
                    q = &sp10;
                    sp10 = 0;
                    if (D_00001284 <= 0) {
                        LD_00001258.unk4 = 0x20;
                        func_000003B8(0xEU, q);
                    }
                    D_00001394 = 0;
                } else {
                    if (D_00001284 <= 0) {
                        LD_00001258.unk4 = 0x20;
                        func_000003B8(1U, 0);
                    }
                    D_00001394 = 1;
                }
            } else if (LD_00001258.unkC == 0xD) {
                D_00001394 = 0;
                if (D_00001284 <= 0) {
                    LD_00001258.unk4 = 0x20;
                    func_000003B8(1U, 0);
                }
            } else if (LD_00001258.unkC == 0xE) {
                if (LD_00001258.unk10 == 0x15) {
                    if (D_00001284 <= 0) {
                        LD_00001258.unk4 = 0x20;
                        func_000003B8(1U, 0);
                    }
                } else if (LD_00001258.unk10 == 0x16) {
                    LD_00001258.unk20 = LD_00001258.unk20 + 1;
                    if (D_00001284 <= 0) {
                        LD_00001258.unk4 = 0x20;
                        func_000003B8(1U, 0);
                    }
                } else if (LD_00001258.unk10 == 0x17) {
                    if (D_00001284 <= 0) {
                        LD_00001258.unk4 = 0x20;
                        func_000003B8(0x13U, 0);
                    }
                } else if (LD_00001258.unk10 == 0x18) {
                    if (D_00001284 <= 0) {
                        LD_00001258.unk4 = 0x20;
                        func_000003B8(1U, 0);
                    }
                }
            } else if (LD_00001258.unkC == 0xF) {
                if (LD_00001258.unk28 == 0) {
                    LD_00001258.unk8 = 1;
                    LD_00001258.unkC = 0xB;
                }
            } else if (LD_00001258.unkC == 0x10) {
                if (LD_00001258.unk1C != 0) {
                    LD_00001258.unk8 = 1;
                    LD_00001258.unkC = 0xB;
                } else {
                    if (D_00001284 <= 0) {
                        LD_00001258.unk4 = 0x20;
                        func_000003B8(1U, 0);
                    }
                }
            } else if (LD_00001258.unkC == 0x11) {
                if (LD_00001258.unk1E != 0) {
                    LD_00001258.unk8 = 1;
                    LD_00001258.unkC = 0xB;
                } else {
                    if (D_00001284 <= 0) {
                        LD_00001258.unk4 = 0x20;
                        func_000003B8(1U, 0);
                    }
                }
            }
        }
    }
    if ((B_00001398 != 0) && (LD_00001240 != 0)) {
        ((void (*)()) B_00001398)();
    }
    if ((((LD_00001258.unk8 == 1) && (LD_00001258.unk1F == 0)) || (LD_00001258.unk8 == 3)) && (D_00001284 <= 0)) {
        LD_00001258.unk4 = 0x21;
        func_000003B8(1U, 0);
    }
}
