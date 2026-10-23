INCLUDE_ASM("build/libraries/nonmatchings/libgs_24", GsSortClear);


/* PARKED by /auto_decompilation_loop on 2026-10-23T17:58:19.090Z.
 * Reason: escalation-exhausted.
 * Escalation reached: deepseek-v4-1-flash-1017.
 * The best non-matching attempt is preserved verbatim below, disabled.
 * Findings and the decision needed: notes/human-needed-approvals/libgs_24::GsSortClear.md
 */

#if 0
/* Best non-matching attempt, preserved for the next session. */
#include "common.h"
#include <sys/types.h>
#include <libetc.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>

extern GsOT_TAG B_000005D0[8];
extern volatile long HWD0, VWD0;
extern s16 PSDOFSX[2];
extern s16 PSDOFSY[2];

void GsSortClear(u8 arg0, u8 arg1, u8 arg2, GsOT *arg3) {
    *(u8 *) ((u8 *) B_000005D0 + (PSDIDX << 4) + 4) = arg0;
    *(u8 *) ((u8 *) B_000005D0 + (PSDIDX << 4) + 5) = arg1;
    *(u8 *) ((u8 *) B_000005D0 + (PSDIDX << 4) + 6) = arg2;
    *(u16 *) ((u8 *) B_000005D0 + (PSDIDX << 4) + 8) = PSDOFSX[PSDIDX];
    *(u16 *) ((u8 *) B_000005D0 + (PSDIDX << 4) + 14) = *(u16 *) &VWD0;
    *(u16 *) ((u8 *) B_000005D0 + (PSDIDX << 4) + 10) = PSDOFSY[PSDIDX];
    if (GsDISPENV.isrgb24) {
        *(u16 *) ((u8 *) B_000005D0 + (PSDIDX << 4) + 12) = HWD0 * 3 / 2;
    } else {
        *(u16 *) ((u8 *) B_000005D0 + (PSDIDX << 4) + 12) = *(u16 *) &HWD0;
    }
    AddPrim(arg3->tag, (u8 *) B_000005D0 + (PSDIDX << 4));
}
#endif
