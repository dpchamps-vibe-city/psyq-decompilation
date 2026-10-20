#include "common.h"

typedef struct {
    s32 active;
    u8 command;
    u8 param[4];
    u8 pad[3];
    s32 unkC;
} DsCmd16;

typedef struct {
    u8 pad0[0x110];
    DsCmd16 command[8];
    s32 index;
    s32 field4;
    s32 count;
} DsSys;

extern DsSys $LB_00001578 __asm__("$LB_00001578");

void rescpy(u8 *dst, u8 *src);

static void func_00000710(s32 arg0, u8 arg1, u8 *arg2, s32 arg3) __asm__("$Lfunc_00000710");

static void func_00000710(s32 arg0, u8 arg1, u8 *arg2, s32 arg3) {
    s32 next;

    $LB_00001578.command[$LB_00001578.index].active = arg0;
    $LB_00001578.command[$LB_00001578.index].command = arg1;
    rescpy($LB_00001578.command[$LB_00001578.index].param, arg2);
    next = $LB_00001578.index + 1;
    $LB_00001578.index = next;
    if (next >= 8) {
        $LB_00001578.index = 0;
    }
}
