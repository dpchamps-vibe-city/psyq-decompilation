# libgs_24::GsSortClear — human decision needed

- **Parked:** 2026-10-23T17:58:19.090Z
- **Reason:** escalation-exhausted
- **Escalation reached:** deepseek-v4-1-flash-1017
- **Source:** `src/libraries/libgs/24-gs_001/GsSortClear.c` (image stub restored; library TU retained)
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
Oracle: libgs_24::GsSortClear verdict MISMATCH — 324/340 words (95.29%).
Residual (steer by this, not the word count): control-flow 0, population 0, schedule 2, allocation 1.
Next block: 0 (0x418) — population 0, schedule 2, allocation 1. smallest open residual
`psx_reverse_pipeline` gives the decisions, their source levers and the mechanism sheet to load; `psx_residual_objective` with a source ranks candidate edits and records them.

VALLEY: the best key [0, 0, 2, 1] is 3 term(s) from exact and 27 distinct programs since have not beaten it, across 14 distinct keys clustered around it. That is a floor, not a gradient. A best this close that a whole sweep cannot improve on means the remaining distance is several coordinates wide: every single-coordinate respelling moves one of the other coordinates the wrong way, scores worse, and reads as a refutation of the direction it tried. Sweeping one axis at a time cannot cross it however long it runs. Take the next experiment from the REQUIREMENT side instead of from another spelling:   psx_target_loop_emission  — what the original's loop pass must have emitted, and by which route   psx_triage                — its cluster-donor finding names a sibling that already reaches a                               mechanism this program does not, with the trace that measured it   psx_analyze_target_schedule / psx_allocator_counterfactual — the same for the later passes Write the program the requirement describes, in one edit, and measure that. STALLED: 28 distinct measurements since the residual last improved on [0, 0, 2, 1]. The axis is exhausted, not the function — stop re-spelling it and bring heavier evidence. Audit the premises first, because everything else is conditioned on them and cannot see them: psx_callee_truth confronts every callee declaration in scope with the vendored SDK headers and the callees' own code, psx_sdk_idioms does the same for operation boundaries. A wrong declaration adds call setup no rewrite of this body can remove, and every measurement taken under it scored a different program. Then read the pass that decides the residual before writing another spelling: its psx_reference sheet, or the deciding function itself through psx_compiler_source. After that, enumerate the source space (psx_search_source_shapes) or solve for the compiler state instead of modelling it (psx_solve_local_allocation, psx_search_scheduler_state, psx_allocator_counterfactual). A solver result is a specification for a source shape, and an UNSAT is a real finding that closes a direction. Record what each one closed with psx_record_closed, and read that record before you run one — a direction another session already closed costs minutes to close again. When a search reports no exact candidate, that is not the end of its output: read the per-class residual axes and the runs each class moved, and take the next experiment from the axis that moved rather than from the match count. Before trusting any search verdict, check its caveats for constructs the grammar refused, its axis-effect block for axes that are counted but inert, and its coverage — a --derive-only run sampled, and a sample supports no statement about the domain. 28 distinct programs is past the point where more variation is informative. Exhausting a spelling family is a positive result: the answer is not a spelling. Switch to the author's frame, which the compiler-side tools cannot reach. The vendored SDK headers give the real signature and the real operation for anything the SDK provides — read the header rather than your reconstruction of what the disassembly implies it must say. The already-matched functions in this target's file group are the only record of how this author wrote code: which locals they kept live, how they walked an array, what they hoisted, whether they took a base pointer once or re-indexed each time. A byte-exact neighbour is a proven idiom. notes/file-groupings.md names the group; read three of its members before reading another pass. A residual that survives every rewrite of your own idiom is usually somebody else's idiom.
```

## Preserved attempt

```c
#include "common.h"
#include <sys/types.h>
#include <libetc.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>

extern GsOT_TAG B_000005D0[8];
extern volatile long HWD0, VWD0;
extern s16 PSDOFSX[2];
extern s16 PSDOFSY[2];

void GsSortClear(u8 arg0, u8 arg1, u8 arg2, GsOT *arg3) {
    *(u8 *) ((u8 *) B_000005D0 + (PSDIDX << 4) + 4) = arg0;
    *(u8 *) ((u8 *) B_000005D0 + (PSDIDX << 4) + 5) = arg1;
    *(u8 *) ((u8 *) B_000005D0 + (PSDIDX << 4) + 6) = arg2;
    *(u16 *) ((u8 *) B_000005D0 + (PSDIDX << 4) + 8) = PSDOFSX[PSDIDX];
    *(u16 *) ((u8 *) B_000005D0 + (PSDIDX << 4) + 14) = *(u16 *) &VWD0;
    *(u16 *) ((u8 *) B_000005D0 + (PSDIDX << 4) + 10) = PSDOFSY[PSDIDX];
    if (GsDISPENV.isrgb24) {
        *(u16 *) ((u8 *) B_000005D0 + (PSDIDX << 4) + 12) = HWD0 * 3 / 2;
    } else {
        *(u16 *) ((u8 *) B_000005D0 + (PSDIDX << 4) + 12) = *(u16 *) &HWD0;
    }
    AddPrim(arg3->tag, (u8 *) B_000005D0 + (PSDIDX << 4));
}
```
