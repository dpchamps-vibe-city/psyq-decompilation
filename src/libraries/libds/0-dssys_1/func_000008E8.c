#include "common.h"

typedef struct {
    s32 timeout;
    s32 unk44;
} DsCommandState;

extern DsCommandState D_00001284s __asm__("$LD_00001238+76");

typedef struct {
    u8 status;
    u8 pad0[3];
    s32 unk4;
} DsSysLite;

extern DsSysLite D_00001258_sys __asm__("$LD_00001238+32");

static s32 func_000009F8(s32, u8 *) __asm__("$Lfunc_000009F8");
static void func_00000BDC(s32 arg0, u8 *arg1) __asm__("$Lfunc_00000BDC");
static void func_00000E64(s32 arg0, u8 *arg1) __asm__("$Lfunc_00000E64");
static void func_00000FE4(u8 arg0, u8 *arg1) __asm__("$Lfunc_00000FE4");

void func_000008E8(u8 arg0, u8 *arg1) {
    DsCommandState *cmd;
    u8 temp_s0;
    u8 var_s1;

    var_s1 = arg0;
    temp_s0 = var_s1 & 0xFF;
    func_00000FE4(temp_s0, arg1);
    cmd = &D_00001284s;
    cmd->unk44 = 0;
    cmd->timeout = 0;
    if ((temp_s0 == 2) && ((*(u8 *) ((u8 *) &D_00001284s + -0x40)) != 1) && (((*(u8 *) ((u8 *) &D_00001284s + -0x40)) != 9) || !((*(s32 *) ((u8 *) &D_00001284s + -0x10)) & 0xFF00FF))) {
        (*(u8 *) ((u8 *) &D_00001284s + 0xC)) = 1;
    }
    if (D_00001258_sys.status & 0x10) {
        var_s1 = 5;
    }
    switch (D_00001258_sys.unk4) {
    case 0x1F:
        func_000009F8(var_s1 & 0xFF, arg1);
        break;
    case 0x20:
        func_00000BDC(var_s1 & 0xFF, arg1);
        break;
    default:
        func_00000E64(var_s1 & 0xFF, arg1);
        break;
    }
    if (D_00001284s.timeout == 0) {
        (*(s32 *) ((u8 *) &D_00001284s + -0x28)) = 0x21;
    }
}
