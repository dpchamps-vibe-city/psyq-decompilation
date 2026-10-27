# libmcx_3::func_000000FC — human decision needed

- **Parked:** 2026-10-27T22:04:22.557Z
- **Reason:** escalation-exhausted
- **Escalation reached:** gpt-6.1-sol
- **Source:** `src/libraries/libmcx/3-mcxcmd4/func_000000FC.c` (image stub restored; library TU retained)
- **Preserved attempt:** library measurements have no staged ranking; kept the current complete TU, including neighboring functions/data

## What the loop needs

Every tier on the escalation ladder returned without a byte-exact match. The function
needs either a new structural hypothesis or a policy decision that the ladder cannot
make on its own. The preserved attempt and the oracle report below are the starting
point.

## Policy findings

- none recorded

## Oracle report for the preserved attempt

```
Oracle: libmcx_3::func_000000FC verdict MISMATCH — 76/76 words (100%).
Residual (steer by this, not the word count): control-flow 0, population 0, schedule 0, allocation 0.
`psx_reverse_pipeline` gives the decisions, their source levers and the mechanism sheet to load; `psx_residual_objective` with a source ranks candidate edits and records them.
```

## Preserved attempt

```c
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
```
