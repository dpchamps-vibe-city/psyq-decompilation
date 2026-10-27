INCLUDE_ASM("build/libraries/nonmatchings/libmcx_3", func_000000FC);


/* PARKED by /auto_decompilation_loop on 2026-10-27T22:04:22.557Z.
 * Reason: escalation-exhausted.
 * Escalation reached: gpt-6.1-sol.
 * The best non-matching attempt is preserved verbatim below, disabled.
 * Findings and the decision needed: notes/human-needed-approvals/libmcx_3::func_000000FC.md
 */

#if 0
/* Best non-matching attempt, preserved for the next session. */
/* Original member: LIBMCX.LIB[3] MCXCMD4.OBJ */
#include "common.h"
#include "libmcx_transfer.h"

s32 func_000000FC(u8 arg0) {
    s32 len;

    len = _mcxRxLen;
    if (len == 5) {
        _mcxRestSize = 8;
    } else if ((u32)(len - 6) < 4) {
        _mcxPtrBuff[9 - len] = arg0;
    } else if ((u32)(len - 10) < 3) {
        _mcxPtrBuff[17 - len] = arg0;
    } else if (len == 13) {
        _mcxPtrBuff[4] = arg0 - 1;
    }
    return 0;
}
#endif
