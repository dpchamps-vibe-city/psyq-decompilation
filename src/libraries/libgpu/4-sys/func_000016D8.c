INCLUDE_ASM("build/libraries/nonmatchings/libgpu_4", func_000016D8);


/* PARKED by /auto_decompilation_loop on 2026-10-21T16:39:16.743Z.
 * Reason: escalation-exhausted.
 * Escalation reached: deepseek-v4-1-flash-1017.
 * The best non-matching attempt is preserved verbatim below, disabled.
 * Findings and the decision needed: notes/human-needed-approvals/libgpu_4::func_000016D8.md
 */

#if 0
/* Best non-matching attempt, preserved for the next session. */
#include "common.h"
#include <sys/types.h>
#include <libetc.h>
#include <libgte.h>
#include <libgpu.h>
#include <memory.h>
#include <stdio.h>

extern u8 GEnv;

typedef struct {
    u16 unk0;
    u16 unk2;
} D_000031FC_t;

extern D_000031FC_t D_000031FC;

u32 func_000016D8(arg0, arg1)
    s32 arg0;
    s32 arg1;
{
    s32 var_v0;
    s32 var_a1;
    s32 var_v1;

    var_v0 = 0;
    if ((s16) arg0 >= 0) {
        var_v0 = D_000031FC.unk0 - 1;
        if ((*(s16 *) ((u8 *) &GEnv + 4) - 1) >= (s16) arg0) {
            var_v0 = arg0;
        }
    }
    if ((s16) arg1 >= 0) {
        if ((*(s16 *) ((u8 *) &GEnv + 6) - 1) < (s16) arg1) {
            var_a1 = D_000031FC.unk2 - 1;
        } else {
            var_v1 = arg1 & 0x3FF;
            goto block_8;
        }
    } else {
        var_a1 = 0;
    }
    var_v1 = var_a1 & 0x3FF;
block_8:
    return ((var_v0 & 0x3FF) | 0xE3000000) | (var_v1 << 0xA);
}
#endif
