INCLUDE_ASM("build/libraries/nonmatchings/libgpu_2", func_00000090);


/* PARKED by /auto_decompilation_loop on 2026-10-21T13:18:47.816Z.
 * Reason: escalation-exhausted.
 * Escalation reached: deepseek-v4-1-flash-1017.
 * The best non-matching attempt is preserved verbatim below, disabled.
 * Findings and the decision needed: notes/human-needed-approvals/libgpu_2::func_00000090.md
 */

#if 0
/* Best non-matching attempt, preserved for the next session. */
#include "common.h"
#include <libapi.h>
#include <memory.h>
#include <stdio.h>

s32 hankanjitrans();
s32 kanjitrans(s32);
extern u8 B_0000B8B0;
extern s32 D_00001068;
extern u8 txyuv;
extern char RO_STR_00000F90[];

s32 func_00000090(s8 *arg0) {
    s32 temp_a0;
    s32 temp_a1;
    s32 temp_s1;
    s32 var_s0;
    s32 var_v0_2;
    u32 var_a0;

    if ((u32) (((u8) arg0[0] + 0x7F) & 0xFF) >= 0x18U) {
        var_s0 = hankanjitrans(*(volatile u8 *) arg0);
        if (!(var_s0 & 0xFFFF)) {
            return -1;
        }
        goto block_4;
    }
    var_s0 = ((u8) arg0[1]) | (*(volatile u8 *) arg0 << 8);
block_4:
    var_a0 = 0x8140;
    if ((u32) ((var_s0 + 0x7EC0) & 0xFFFF) >= 0x37FU) {
        var_a0 = 0x889F;
        if ((u32) ((var_s0 + 0x7761) & 0xFFFF) >= 0xFD4U) {
            printf(RO_STR_00000F90, var_s0 & 0xFFFF);
            return -1;
        }
    }
    temp_s1 = Krom2RawAdd(var_a0);
    bcopy((u8 *) (temp_s1 + (kanjitrans(var_s0 & 0xFFFF) * 0x1E)), (&B_0000B8B0 + (D_00001068 << 5)), 0x1E);
    var_v0_2 = D_00001068;
    temp_a1 = D_00001068 * 0x10;
    if (D_00001068 < 0) {
        var_v0_2 = D_00001068 + 0xF;
    }
    temp_a0 = (var_v0_2 >> 4) * 0x10;
    *((s32 *) ((u8 *) ((void *) ((u8 *) &txyuv + 8)) + temp_a1)) = (D_00001068 - temp_a0) * 0x10;
    *((s32 *) ((u8 *) ((void *) ((u8 *) &txyuv + 0xC)) + temp_a1)) = temp_a0;
    return 0;
}
#endif
