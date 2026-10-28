INCLUDE_ASM("build/libraries/nonmatchings/libmcx_10", McxWriteDev);


/* PARKED by /auto_decompilation_loop on 2026-10-28T17:25:18.822Z.
 * Reason: escalation-exhausted.
 * Escalation reached: gpt-6.1-sol.
 * The best non-matching attempt is preserved verbatim below, disabled.
 * Findings and the decision needed: notes/human-needed-approvals/libmcx_10::McxWriteDev.md
 */

#if 0
/* Best non-matching attempt, preserved for the next session. */
#include "common.h"
#include <libmcx.h>
#include "libmcx_internal.h"
#include "libmcx_transfer.h"

int McxWriteDev(int port, int param, unsigned char *buff, unsigned char *cmdBuf0) {
    if (_mcxChkRsrv(port) == 0) {
        return 0;
    }
    _mcxFuncNo = McxFuncWriteDev;
    _mcxFuncGetTx = _mcxTxWriteDev;
    _mcxFuncApplyRx = _mcxRxWriteDev;
    _mcxParam = param;
    _mcxPtrBuff = buff;
    _mcxPtrCmdBuf0 = (long *)cmdBuf0;
    _mcxDataLen = 0;
    _mcxFlag = 0;
    _mcxStat = 2;
    return 1;
}
#endif
