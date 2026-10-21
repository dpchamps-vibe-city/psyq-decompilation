# libetc_3::SetIntrMask — human decision needed

- **Parked:** 2026-10-21T09:03:19.853Z
- **Reason:** escalation-exhausted
- **Escalation reached:** deepseek-v4-1-flash-1017
- **Source:** `src/libraries/libetc/3-intr/SetIntrMask.c` (image stub restored; library TU retained)
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
Oracle: libetc_3::SetIntrMask verdict MISMATCH — 94/432 words (21.76%).
Instruction count delta versus target: -52.
Residual (steer by this, not the word count): control-flow 40, population 253, schedule 2, allocation 12.
The two programs do not contain the same instructions, so no allocation or scheduling reading applies yet — fix the semantics first.
Next block: 5 (0x25C) — population 6, schedule 0, allocation 0. the instruction populations differ here; nothing below can be read until they agree
`psx_reverse_pipeline` gives the decisions, their source levers and the mechanism sheet to load; `psx_residual_objective` with a source ranks candidate edits and records them.
```

## Preserved attempt

```c
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
```
