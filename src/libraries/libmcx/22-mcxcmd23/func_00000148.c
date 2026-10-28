INCLUDE_ASM("build/libraries/nonmatchings/libmcx_22", func_00000148);


/* PARKED by /auto_decompilation_loop on 2026-10-28T01:57:51.991Z.
 * Reason: escalation-exhausted.
 * Escalation reached: gpt-6.1-sol.
 * The best non-matching attempt is preserved verbatim below, disabled.
 * Findings and the decision needed: notes/human-needed-approvals/libmcx_22::func_00000148.md
 */

#if 0
/* Best non-matching attempt, preserved for the next session. */
/* Original member: LIBMCX.LIB[22] MCXCMD23.OBJ */
#include "common.h"
#include "libmcx_internal.h"

extern s32 _mcxRestSize;
extern s32 _mcxRxLen;

static s32 func_00000148(s32 arg0) {
    switch (_mcxRxLen) {
    case 3:
        _mcxRestSize = arg0 & 0xFF;
        break;
    case 4:
        *_mcxPtrCmdBuf0 = arg0 & 0xFF;
        break;
    case 5:
        *_mcxPtrCmdBuf1 = arg0 & 0xFF;
        break;
    }
    return 0;
}
#endif
