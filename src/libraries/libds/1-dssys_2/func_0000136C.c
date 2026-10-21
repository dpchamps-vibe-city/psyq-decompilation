#include "common.h"

extern DsInitCmd B_00001598;
extern DsInitCmd B_000015A8;
extern void (*GlobalCallback)(u8, u8 *);

void rescpy(u8 *dst, u8 *src);
static void func_0000028C(u8 arg0, u8 *arg1, s32 arg2, s32 arg3);

static void func_0000136C(u8 arg0, u8 *arg1) {
    DsInitCmd *cmd;
    u8 *param;

    if ((arg0 & 0xFF) == 5) {
        if (*arg1 & 0x10) {
            ((void (*)(u8, u8 *))func_0000028C)(5, arg1);
        }
    }
    switch (arg0 & 0xFF) {
    case 1:
    case 5:
        cmd = &B_00001598;
        param = cmd->param;
        break;
    case 4:
        cmd = &B_000015A8;
        param = cmd->param;
        break;
    default:
        goto done;
    }
    cmd->active = 1;
    cmd->command = arg0;
    rescpy(param, arg1);
done:
    if (((void (**)(u8, u8 *))&GlobalCallback)[1] != 0) {
        ((void (**)(u8, u8 *))&GlobalCallback)[1](arg0 & 0xFF, arg1);
    }
}
