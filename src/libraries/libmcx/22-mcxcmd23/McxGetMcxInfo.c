INCLUDE_ASM("build/libraries/nonmatchings/libmcx_22", McxGetMcxInfo);


/* PARKED by /auto_decompilation_loop on 2026-10-28T00:47:46.352Z.
 * Reason: escalation-exhausted.
 * Escalation reached: gpt-6.1-sol.
 * The best non-matching attempt is preserved verbatim below, disabled.
 * Findings and the decision needed: notes/human-needed-approvals/libmcx_22::McxGetMcxInfo.md
 */

#if 0
/* Best non-matching attempt, preserved for the next session. */
#include "common.h"
#include "libmcx_internal.h"

extern long *_mcxPtrCmdBuf1;

static int func_00000124(void);
static int func_00000148(int value);

int McxGetMcxInfo(int port, long *cmdBuf0, long *cmdBuf1) {
    if (_mcxChkRsrv(port) == 0) {
        return 0;
    }
    _mcxFuncNo = 0x13;
    _mcxFuncGetTx = func_00000124;
    _mcxFuncApplyRx = func_00000148;
    _mcxPtrCmdBuf0 = cmdBuf0;
    _mcxPtrCmdBuf1 = cmdBuf1;
    _mcxStat = 2;
    return 1;
}
#endif
