INCLUDE_ASM("build/libraries/nonmatchings/libgpu_2", func_000001D0);


/* PARKED by /auto_decompilation_loop on 2026-10-21T13:46:33.695Z.
 * Reason: escalation-exhausted.
 * Escalation reached: deepseek-v4-1-flash-1017.
 * The best non-matching attempt is preserved verbatim below, disabled.
 * Findings and the decision needed: notes/human-needed-approvals/libgpu_2::func_000001D0.md
 */

#if 0
/* Best non-matching attempt, preserved for the next session. */
#include "common.h"
#include <libapi.h>
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <memory.h>
#include <stdio.h>
#include <strings.h>

extern u16 B_0000B8A8;
extern u8 B_0000B8B0;
extern s32 D_00001068;

u16 func_000001D0(s32 arg0, s32 arg1) {
    u16 buf[0x8000];
    s32 i;
    s32 j;
    s32 k;
    s32 t5;
    s32 t4;
    s32 p;
    u16 *bp;
    u16 *src;
    u16 temp;

    if (D_00001068 < 0x10) {
        t5 = D_00001068 % 16 + 1;
    } else {
        t5 = 0x10;
    }
    bp = buf;
    t4 = 0;
    p = 0;
    for (i = 0; i < D_00001068 / 16 + 1; i++) {
        for (j = 0; j < 16; j++) {
            for (k = 0; k < t5; k++) {
                p = i * t5 + k;
                if (p < D_00001068) {
                    src = (u16 *) ((&B_0000B8B0) + (p << 5) + (j << 1));
                    buf[t4] = ((src[0] >> 7) & 1) | ((src[0] >> 2) & 0x10) | ((src[0] << 3) & 0x100) | ((src[0] << 8) & 0x1000);
                    buf[t4 + 1] = ((src[0] >> 3) & 1) | ((src[0] << 2) & 0x10) | ((src[0] << 7) & 0x100) | ((src[0] & 1) << 12);
                    buf[t4 + 2] = (src[0] >> 15) | ((src[0] >> 10) & 0x10) | ((src[0] >> 5) & 0x100) | (src[0] & 0x1000);
                    buf[t4 + 3] = ((src[0] >> 11) & 1) | ((src[0] >> 6) & 0x10) | ((src[0] >> 1) & 0x100) | ((src[0] << 4) & 0x1000);
                }
                t4 += 4;
            }
        }
        if (p >= D_00001068) {
            break;
        }
    }
    temp = LoadTPage((u_long *) bp, 0, 0, arg0, arg1, t5 * 16, (D_00001068 / 16 + 1) * 16);
    B_0000B8A8 = temp;
    return temp;
}
#endif
