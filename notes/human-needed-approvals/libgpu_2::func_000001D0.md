# libgpu_2::func_000001D0 — human decision needed

- **Parked:** 2026-10-21T13:46:33.695Z
- **Reason:** escalation-exhausted
- **Escalation reached:** deepseek-v4-1-flash-1017
- **Source:** `src/libraries/libgpu/2-kprintf/func_000001D0.c` (image stub restored; library TU retained)
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
Oracle: libgpu_2::func_000001D0 verdict MISMATCH — 110/960 words (11.46%).
Instruction count delta versus target: +4.
Residual (steer by this, not the word count): control-flow 0, population 12, schedule 8, allocation 41.
The two programs do not contain the same instructions, so no allocation or scheduling reading applies yet — fix the semantics first.
Next block: 15 (0x310) — population 1, schedule 0, allocation 0. the instruction populations differ here; nothing below can be read until they agree
`psx_reverse_pipeline` gives the decisions, their source levers and the mechanism sheet to load; `psx_residual_objective` with a source ranks candidate edits and records them.

STALLED: 5 distinct measurements since the residual last improved on [0, 12, 8, 41]. The axis is exhausted, not the function — stop re-spelling it and bring heavier evidence. Audit the premises first, because everything else is conditioned on them and cannot see them: psx_callee_truth confronts every callee declaration in scope with the vendored SDK headers and the callees' own code, psx_sdk_idioms does the same for operation boundaries. A wrong declaration adds call setup no rewrite of this body can remove, and every measurement taken under it scored a different program. Then read the pass that decides the residual before writing another spelling: its psx_reference sheet, or the deciding function itself through psx_compiler_source. After that, enumerate the source space (psx_search_source_shapes) or solve for the compiler state instead of modelling it (psx_solve_local_allocation, psx_search_scheduler_state, psx_allocator_counterfactual). A solver result is a specification for a source shape, and an UNSAT is a real finding that closes a direction. Record what each one closed with psx_record_closed, and read that record before you run one — a direction another session already closed costs minutes to close again. When a search reports no exact candidate, that is not the end of its output: read the per-class residual axes and the runs each class moved, and take the next experiment from the axis that moved rather than from the match count. Before trusting any search verdict, check its caveats for constructs the grammar refused, its axis-effect block for axes that are counted but inert, and its coverage — a --derive-only run sampled, and a sample supports no statement about the domain.
```

## Preserved attempt

```c
#include "common.h"
#include <libapi.h>
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <memory.h>
#include <stdio.h>
#include <strings.h>

extern u16 B_0000B8A8;
extern u8 B_0000B8B0;
extern s32 D_00001068;

u16 func_000001D0(s32 arg0, s32 arg1) {
    u16 buf[0x8000];
    s32 i;
    s32 j;
    s32 k;
    s32 t5;
    s32 t4;
    s32 p;
    u16 *bp;
    u16 *src;
    u16 temp;

    if (D_00001068 < 0x10) {
        t5 = D_00001068 % 16 + 1;
    } else {
        t5 = 0x10;
    }
    bp = buf;
    t4 = 0;
    p = 0;
    for (i = 0; i < D_00001068 / 16 + 1; i++) {
        for (j = 0; j < 16; j++) {
            for (k = 0; k < t5; k++) {
                p = i * t5 + k;
                if (p < D_00001068) {
                    src = (u16 *) ((&B_0000B8B0) + (p << 5) + (j << 1));
                    buf[t4] = ((src[0] >> 7) & 1) | ((src[0] >> 2) & 0x10) | ((src[0] << 3) & 0x100) | ((src[0] << 8) & 0x1000);
                    buf[t4 + 1] = ((src[0] >> 3) & 1) | ((src[0] << 2) & 0x10) | ((src[0] << 7) & 0x100) | ((src[0] & 1) << 12);
                    buf[t4 + 2] = (src[0] >> 15) | ((src[0] >> 10) & 0x10) | ((src[0] >> 5) & 0x100) | (src[0] & 0x1000);
                    buf[t4 + 3] = ((src[0] >> 11) & 1) | ((src[0] >> 6) & 0x10) | ((src[0] >> 1) & 0x100) | ((src[0] << 4) & 0x1000);
                }
                t4 += 4;
            }
        }
        if (p >= D_00001068) {
            break;
        }
    }
    temp = LoadTPage((u_long *) bp, 0, 0, arg0, arg1, t5 * 16, (D_00001068 / 16 + 1) * 16);
    B_0000B8A8 = temp;
    return temp;
}
```
