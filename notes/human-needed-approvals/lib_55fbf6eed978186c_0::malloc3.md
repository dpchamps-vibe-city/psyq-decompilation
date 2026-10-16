# lib_55fbf6eed978186c_0::malloc3 — resolved, byte-exact

**Resolved 2026-10-16:** unparked and reconstructed with the unchanged GCC 2.7.2
production toolchain. `malloc3` matches 44/44 words and passed the authoritative
exact-diff, full-build, scope and clean-source gates. No human policy decision
or compiler replacement is needed. Verified documentation handoff identity:
`8b7cf1e6b1081788957b7399bc068044159b4d80ac97af714461fa705ec8d7cc`.

See [the loop-entry investigation and retrospective](../research/malloc3-loop-entry-and-false-toolchain-blocker.md)
for the native-dump evidence and the correction to the old impossibility claim.
The remainder of this file preserves the **historical, superseded park**; it
is not a current approval request or a description of the verified source.

- **Parked:** 2026-10-16T20:56:49.720Z
- **Reason:** escalation-exhausted
- **Escalation reached:** deepseek-v4-1-flash
- **Source:** `src/libraries/libapi/85-malloc3/malloc3.c` (image stub restored; library TU retained)
- **Preserved attempt:** library measurements have no staged ranking; kept the current complete TU, including neighboring functions/data
- **Parking notes:** Library park preserves the complete member TU unchanged; no disabled neighbor bodies or original-object fallback

## What the loop needs

Every tier on the escalation ladder returned without a byte-exact match. The function
needs either a new structural hypothesis or a policy decision that the ladder cannot
make on its own. The preserved attempt and the oracle report below are the starting
point.

## Policy findings

- none recorded

## Oracle report for the preserved attempt

```
Oracle: lib_55fbf6eed978186c_0::malloc3 verdict MISMATCH — 41/44 words (93.18%).
Residual (steer by this, not the word count): control-flow 0, population 1, schedule 0, allocation 0.
The two programs do not contain the same instructions, so no allocation or scheduling reading applies yet — fix the semantics first.
Next block: 0 (0x0) — population 1, schedule 0, allocation 0. the instruction populations differ here; nothing below can be read until they agree
`psx_reverse_pipeline` gives the decisions, their source levers and the mechanism sheet to load; `psx_residual_objective` with a source ranks candidate edits and records them.

VALLEY: the best key [0, 1, 0, 0] is 1 term(s) from exact, and the nearest of the other 10 distinct key(s) measured is 5 — 13 distinct programs, and nothing landed in between. That is a floor, not a gradient. A best this close that a whole sweep cannot improve on means the remaining distance is several coordinates wide: every single-coordinate respelling moves one of the other coordinates the wrong way, scores worse, and reads as a refutation of the direction it tried. Sweeping one axis at a time cannot cross it however long it runs. Take the next experiment from the REQUIREMENT side instead of from another spelling:   psx_target_loop_emission  — what the original's loop pass must have emitted, and by which route   psx_triage                — its cluster-donor finding names a sibling that already reaches a                               mechanism this program does not, with the trace that measured it   psx_analyze_target_schedule / psx_allocator_counterfactual — the same for the later passes Write the program the requirement describes, in one edit, and measure that. STALLED: 6 distinct measurements since the residual last improved on [0, 1, 0, 0]. The axis is exhausted, not the function — stop re-spelling it and bring heavier evidence. Audit the premises first, because everything else is conditioned on them and cannot see them: psx_callee_truth confronts every callee declaration in scope with the vendored SDK headers and the callees' own code, psx_sdk_idioms does the same for operation boundaries. A wrong declaration adds call setup no rewrite of this body can remove, and every measurement taken under it scored a different program. Then read the pass that decides the residual before writing another spelling: its psx_reference sheet, or the deciding function itself through psx_compiler_source. After that, enumerate the source space (psx_search_source_shapes) or solve for the compiler state instead of modelling it (psx_solve_local_allocation, psx_search_scheduler_state, psx_allocator_counterfactual). A solver result is a specification for a source shape, and an UNSAT is a real finding that closes a direction. Record what each one closed with psx_record_closed, and read that record before you run one — a direction another session already closed costs minutes to close again. When a search reports no exact candidate, that is not the end of its output: read the per-class residual axes and the runs each class moved, and take the next experiment from the axis that moved rather than from the match count. Before trusting any search verdict, check its caveats for constructs the grammar refused, its axis-effect block for axes that are counted but inert, and its coverage — a --derive-only run sampled, and a sample supports no statement about the domain.
```

## Preserved attempt

```c
#include "common.h"

extern u32 *_freep;

void *malloc3(u32 size) {
    s32 *p;
    s32 *q;
    s32 n;
    s32 rem;

    if (size == 0) {
        return 0;
    }
    while (size & 7) {
        size++;
    }
    n = ((size + 7) >> 3) + 1;
    q = (s32 *)_freep;
    p = (s32 *)*q;
    for (;;) {
        if (p[1] >= n) {
            if (p[1] == n) {
                *q = *p;
            } else {
                rem = p[1] - n;
                p[1] = rem;
                p = &p[rem * 2];
                p[1] = n;
            }
            _freep = (u32 *)q;
            return p + 2;
        }
        if (p == (s32 *)_freep) {
            return 0;
        }
        q = p;
        p = (s32 *)*p;
    }
}
```
