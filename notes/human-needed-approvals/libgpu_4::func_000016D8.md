# libgpu_4::func_000016D8 — human decision needed

- **Parked:** 2026-10-21T16:39:16.743Z
- **Reason:** escalation-exhausted
- **Escalation reached:** deepseek-v4-1-flash-1017
- **Source:** `src/libraries/libgpu/4-sys/func_000016D8.c` (image stub restored; library TU retained)
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
Oracle: libgpu_4::func_000016D8 verdict MISMATCH — 2978/3008 words (99%).
Residual (steer by this, not the word count): control-flow 0, population 7, schedule 3, allocation 5.
The two programs do not contain the same instructions, so no allocation or scheduling reading applies yet — fix the semantics first.
Next block: 4 (0x169C) — population 1, schedule 0, allocation 1. the instruction populations differ here; nothing below can be read until they agree
`psx_reverse_pipeline` gives the decisions, their source levers and the mechanism sheet to load; `psx_residual_objective` with a source ranks candidate edits and records them.

STALLED: 15 distinct measurements since the residual last improved on [0, 7, 3, 5]. The axis is exhausted, not the function — stop re-spelling it and bring heavier evidence. Audit the premises first, because everything else is conditioned on them and cannot see them: psx_callee_truth confronts every callee declaration in scope with the vendored SDK headers and the callees' own code, psx_sdk_idioms does the same for operation boundaries. A wrong declaration adds call setup no rewrite of this body can remove, and every measurement taken under it scored a different program. Then read the pass that decides the residual before writing another spelling: its psx_reference sheet, or the deciding function itself through psx_compiler_source. After that, enumerate the source space (psx_search_source_shapes) or solve for the compiler state instead of modelling it (psx_solve_local_allocation, psx_search_scheduler_state, psx_allocator_counterfactual). A solver result is a specification for a source shape, and an UNSAT is a real finding that closes a direction. Record what each one closed with psx_record_closed, and read that record before you run one — a direction another session already closed costs minutes to close again. When a search reports no exact candidate, that is not the end of its output: read the per-class residual axes and the runs each class moved, and take the next experiment from the axis that moved rather than from the match count. Before trusting any search verdict, check its caveats for constructs the grammar refused, its axis-effect block for axes that are counted but inert, and its coverage — a --derive-only run sampled, and a sample supports no statement about the domain. 15 distinct programs is past the point where more variation is informative. Exhausting a spelling family is a positive result: the answer is not a spelling. Switch to the author's frame, which the compiler-side tools cannot reach. The vendored SDK headers give the real signature and the real operation for anything the SDK provides — read the header rather than your reconstruction of what the disassembly implies it must say. The already-matched functions in this target's file group are the only record of how this author wrote code: which locals they kept live, how they walked an array, what they hoisted, whether they took a base pointer once or re-indexed each time. A byte-exact neighbour is a proven idiom. notes/file-groupings.md names the group; read three of its members before reading another pass. A residual that survives every rewrite of your own idiom is usually somebody else's idiom.
```

## Preserved attempt

```c
#include "common.h"
#include <sys/types.h>
#include <libetc.h>
#include <libgte.h>
#include <libgpu.h>
#include <memory.h>
#include <stdio.h>

extern u8 GEnv;

typedef struct {
    u16 unk0;
    u16 unk2;
} D_000031FC_t;

extern D_000031FC_t D_000031FC;

u32 func_000016D8(arg0, arg1)
    s32 arg0;
    s32 arg1;
{
    s32 var_v0;
    s32 var_a1;
    s32 var_v1;

    var_v0 = 0;
    if ((s16) arg0 >= 0) {
        var_v0 = D_000031FC.unk0 - 1;
        if ((*(s16 *) ((u8 *) &GEnv + 4) - 1) >= (s16) arg0) {
            var_v0 = arg0;
        }
    }
    if ((s16) arg1 >= 0) {
        if ((*(s16 *) ((u8 *) &GEnv + 6) - 1) < (s16) arg1) {
            var_a1 = D_000031FC.unk2 - 1;
        } else {
            var_v1 = arg1 & 0x3FF;
            goto block_8;
        }
    } else {
        var_a1 = 0;
    }
    var_v1 = var_a1 & 0x3FF;
block_8:
    return ((var_v0 & 0x3FF) | 0xE3000000) | (var_v1 << 0xA);
}
```
