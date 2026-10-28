INCLUDE_ASM("build/libraries/nonmatchings/libmcx_23", McxAllInfo);


/* PARKED by /auto_decompilation_loop on 2026-10-28T02:27:32.511Z.
 * Reason: escalation-exhausted.
 * Escalation reached: gpt-6.1-sol.
 * The best non-matching attempt is preserved verbatim below, disabled.
 * Findings and the decision needed: notes/human-needed-approvals/libmcx_23::McxAllInfo.md
 */

#if 0
/* Best non-matching attempt, preserved for the next session. */
#include "common.h"
#include <libmcx.h>
#include "libmcx_internal.h"
#include "libmcx_transfer.h"

static int func_000000EC(void);
static int func_00000110(int);

int McxAllInfo(int port, unsigned char *buff) {
    if (_mcxChkRsrv(port) == 0) {
        return 0;
    }
    _mcxFuncNo = McxFuncAllInfo;
    _mcxFuncGetTx = func_000000EC;
    _mcxFuncApplyRx = func_00000110;
    _mcxPtrBuff = buff;
    _mcxStat = 2;
    return 1;
}
#endif
