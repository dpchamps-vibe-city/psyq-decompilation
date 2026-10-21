#include "common.h"
#include <libapi.h>
#include <sys/types.h>
#include <libetc.h>
#include <setjmp.h>
#include <stdio.h>

extern u16 *D_00001898;

u16 GetIntrMask(void) {
    return *D_00001898;
}


/* PARKED by /auto_decompilation_loop on 2026-10-21T09:35:54.283Z.
 * Reason: escalation-exhausted.
 * Escalation reached: deepseek-v4-1-flash-1017.
 * The best non-matching attempt is preserved verbatim below, disabled.
 * Findings and the decision needed: notes/human-needed-approvals/libetc_3::func_000002EC.md
 */

#if 0
/* Best non-matching attempt, preserved for the next session. */
#include "common.h"
#include <libapi.h>
#include <sys/types.h>
#include <libetc.h>
#include <setjmp.h>
#include <stdio.h>

extern volatile u16 *D_00001898;

u16 GetIntrMask(void) {
    return *D_00001898;
}
#endif
