#include "common.h"
#include <libapi.h>
#include <libcomb.h>
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

extern volatile CombConfig $LB_00001268;
extern s32 (*$LB_00001270)(s32, s32);
extern volatile CombCmd $LB_00001278;
extern u8 *$LB_0000127C;
extern volatile s32 $LB_00001280;
extern volatile s32 $LB_00001284;
extern s16 $LD_00001208[];

#define DEV ((CombDevView *) $LD_000011D8)

static s32 func_000003D8(s32 arg0, s32 arg1) __asm__("$Lfunc_000003D8");

static s32 func_000003D8(s32 arg0, s32 arg1) {
    s32 temp_s5;
    s32 var_s0;
    s32 var_s1;

    var_s0 = 0;
    if ($LB_00001278.unk0 != 0) {
        return -1;
    }
    temp_s5 = $LD_00001208[($LB_00001268.unk2 & 0x300) >> 8];
    $LB_00001278.unk8 = arg1;
    $LB_00001278.unk4 = arg0;
    var_s1 = 0;
    if ($LB_00001278.unk8 != 0) {
        do {
            while ((DEV->unk4 & 5) != 5) {
                s32 temp_a1;

                temp_a1 = var_s0;
                if ($LB_00001270 != NULL) {
                    var_s0 += 1;
                    if ($LB_00001270(2, temp_a1) == 0) {
                        DeliverEvent(0xF000000BU, 0x100U);
                        return arg1 - *(volatile s32 *) &$LB_00001280;
                    }
                }
            }
            if (var_s1 == 0) {
                $LB_00001278.unkC = DEV->unk4 & 0x80;
            }
            DEV->unk0 = *$LB_0000127C;
            $LB_00001278.unk4 = $LB_00001278.unk4 + 1;
            var_s1 += 1;
            $LB_00001278.unk8 = $LB_00001278.unk8 - 1;
            if (var_s1 == temp_s5) {
                var_s1 = 0;
                if ((DEV->unk4 & 0x80) == $LB_00001278.unkC) {
                    volatile s32 *limit = &$LB_00001284;
                    do {
                        s32 temp_a1;

                        temp_a1 = var_s0;
                        if ($LB_00001270 != NULL) {
                            var_s0 += 1;
                            if ($LB_00001270(2, temp_a1) == 0) {
                                DeliverEvent(0xF000000BU, 0x100U);
                                return arg1 - *(volatile s32 *) &$LB_00001280 - 1;
                            }
                        }
                    } while ((DEV->unk4 & 0x80) == *limit);
                }
                var_s1 = 0;
            }
        } while (*(volatile s32 *) &$LB_00001280 != 0);
    }
    return arg1 - *(volatile s32 *) &$LB_00001280;
}
