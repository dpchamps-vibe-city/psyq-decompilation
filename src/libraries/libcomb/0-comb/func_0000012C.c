#include "common.h"
#include <libapi.h>
#include <libcomb.h>
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

typedef struct {
    u8 unk0;
    u8 pad1[3];
    volatile u16 unk4;
    u16 unk6;
    volatile u16 unk8;
    volatile u16 unkA;
    u16 unkC;
    volatile u16 unkE;
} CombDevView;

typedef struct {
    u16 unk0;
    u16 unk2;
    volatile u16 unk4;
    u16 unk6;
} CombConfig;

extern volatile CombConfig B_00001268;
extern s32 (*B_00001270)(s32, s32);
extern u8 *B_0000128C;
extern volatile s32 B_00001290;
extern s16 D_00001208[];

#define DEV ((CombDevView *) D_000011D8)

static s32 func_0000012C(s32 arg0, s32 arg1);

static s32 func_0000012C(s32 arg0, s32 arg1) {
    s32 temp_s4;
    s32 temp_a1;
    s32 var_s0;
    s32 var_s1;
    u16 old;

    var_s1 = 0;
    if (B_00001288.unk0 != 0) {
        return -1;
    }
    temp_s4 = D_00001208[(B_00001268.unk2 & 0x300) >> 8];
    B_00001288.unk8 = arg1;
    B_00001288.unk4 = arg0;
    B_00001288.unk0 = 0;
    DEV->unkA = (u16) (DEV->unkA | 0x20);
    var_s0 = 0;
    while (B_00001288.unk8 != 0) {
        if (DEV->unk4 & 0x38) {
            old = DEV->unkA;
            DEV->unkA = 0x50;
            DEV->unk8 = B_00001268.unk0;
            DEV->unkE = B_00001268.unk6;
            DEV->unkA = (u16) (DEV->unkA | 0x10);
            DEV->unkA = old;
            DEV->unkA = (u16) (DEV->unkA & 0xFFDF);
            DeliverEvent(0xF000000BU, 0x8000U);
            return arg1 - *(volatile s32 *) &B_00001290;
        }
        while (!(DEV->unk4 & 2)) {
            temp_a1 = var_s1;
            if (B_00001270 != NULL) {
                var_s1 += 1;
                if (B_00001270(1, temp_a1) != 0) {
                    continue;
                }
                DEV->unkA = (u16) (DEV->unkA & 0xFFDF);
                DeliverEvent(0xF000000BU, 0x100U);
                return arg1 - *(volatile s32 *) &B_00001290;
            }
        }
        *B_0000128C = DEV->unk0;
        B_00001288.unk4 = B_00001288.unk4 + 1;
        var_s0 += 1;
        B_00001288.unk8 = B_00001288.unk8 - 1;
        if (var_s0 == temp_s4) {
            var_s0 = 0;
            DEV->unkA = (u16) (DEV->unkA ^ 2);
        }
    }
    DEV->unkA = (u16) (DEV->unkA & 0xFFDF);
    return arg1 - *(volatile s32 *) &B_00001290;
}
