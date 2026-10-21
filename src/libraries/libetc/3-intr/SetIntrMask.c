INCLUDE_ASM("build/libraries/nonmatchings/libetc_3", SetIntrMask);


/* PARKED by /auto_decompilation_loop on 2026-10-21T09:03:19.853Z.
 * Reason: escalation-exhausted.
 * Escalation reached: deepseek-v4-1-flash-1017.
 * The best non-matching attempt is preserved verbatim below, disabled.
 * Findings and the decision needed: notes/human-needed-approvals/libetc_3::SetIntrMask.md
 */

#if 0
/* Best non-matching attempt, preserved for the next session. */
#include "common.h"
#include <libapi.h>
#include <sys/types.h>
#include <libetc.h>
#include <setjmp.h>
#include <stdio.h>

extern u16 *D_00001898;

u16 SetIntrMask(u16 arg0) {
    u16 temp_v0;

    temp_v0 = *D_00001898;
    *D_00001898 = arg0;
    return temp_v0;
}
#endif
