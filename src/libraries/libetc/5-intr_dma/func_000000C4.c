#include "common.h"
#include <stdio.h>

extern s32 *D_00000348;
extern DMAFunc D_0000034C[8];
extern u8 *D_0000036C;
extern char RO_STR_00000318[];

void func_000000C4(void) {
    s32 var_s0;
    u32 var_s1;
    DMAFunc *var_s2;
    DMAFunc temp_v0;

    var_s1 = ((u32) *(volatile u32 *)D_00000348 >> 0x18) & 0x7F;
    if (var_s1 != 0) {
        u32 one = 1;
        u32 mask = 0xFFFFFF;
        DMAFunc *base = D_0000034C;
        do {
            var_s0 = 0;
            if (var_s1 != 0) {
                for (var_s2 = base; ; ) {
loop_4:
                if (var_s0 < 7) {
                    if (var_s1 & 1) {
                        *(volatile u32 *)D_00000348 &= (one << (var_s0 + 0x18)) | mask;
                        temp_v0 = *var_s2;
                        if (temp_v0 != 0) {
                            temp_v0();
                        }
                    }
                    var_s2 += 1;
                    var_s1 = var_s1 >> 1;
                    var_s0 += 1;
                    if (var_s1 != 0) {
                        goto loop_4;
                    }
                }
                break;
                }
            }
            var_s1 = ((u32) *(volatile u32 *)D_00000348 >> 0x18) & 0x7F;
        } while (var_s1 != 0);
    }
    if (((*(volatile u32 *)D_00000348 & 0xFF000000) == 0x80000000) || (*(volatile u32 *)D_00000348 & 0x8000)) {
        printf(RO_STR_00000318, *(volatile u32 *)D_00000348);
        var_s0 = 0;
        do {
            printf(RO_STR_00000318 + 28, var_s0, *(u32 *)((var_s0 * 0x10) + D_0000036C));
            var_s0 += 1;
        } while (var_s0 < 7);
    }
}
