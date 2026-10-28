# libpad_9::func_000001B8 — human decision needed

- **Parked:** 2026-10-28T20:16:59.839Z
- **Reason:** escalation-exhausted
- **Escalation reached:** gpt-6.1-sol
- **Source:** `src/libraries/libpad/9-pdgn1ini/func_000001B8.c` (image stub restored; library TU retained)
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
Oracle: libpad_9::func_000001B8 verdict MISMATCH — 90/92 words (97.83%).
Residual (steer by this, not the word count): control-flow 0, population 2, schedule 0, allocation 1.
The two programs do not contain the same instructions, so no allocation or scheduling reading applies yet — fix the semantics first.
Next block: 1 (0x15C) — population 1, schedule 0, allocation 0. the instruction populations differ here; nothing below can be read until they agree
`psx_reverse_pipeline` gives the decisions, their source levers and the mechanism sheet to load; `psx_residual_objective` with a source ranks candidate edits and records them.
```

## Preserved attempt

```c
#include "common.h"

int func_000001B8(void) {
    volatile unsigned int *base = (volatile unsigned int *)0xBFC00000;

    base = (volatile unsigned int *)base[0x41];
    if ((unsigned int)base != 0x2000) {
        return 1;
    }
    return 2;
}
```
