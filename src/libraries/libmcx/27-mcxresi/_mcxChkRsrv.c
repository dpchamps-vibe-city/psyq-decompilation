INCLUDE_ASM("build/libraries/nonmatchings/libmcx_27", _mcxChkRsrv);


/* PARKED by /auto_decompilation_loop on 2026-10-28T19:10:48.316Z.
 * Reason: escalation-exhausted.
 * Escalation reached: gpt-6.1-sol.
 * The best non-matching attempt is preserved verbatim below, disabled.
 * Findings and the decision needed: notes/human-needed-approvals/libmcx_27::_mcxChkRsrv.md
 */

#if 0
/* Best non-matching attempt, preserved for the next session. */
#include "common.h"
#include "libmcx_resi.h"

int _mcxChkRsrv(int port) {
    if ((_mcxStat & 1) == 0) {
        return 0;
    }
    _mcxTxLen = 0;
    _mcxRxLen = 0;
    _mcxRestSize = 0;
    _mcxCmdSeq = 0;
    _mcxPort = port;
    return 1;
}
#endif
