# libds_1::func_000000B8 — human decision needed

- **Parked:** 2026-10-20T20:06:08.061Z
- **Reason:** escalation-exhausted
- **Escalation reached:** deepseek-v4-1-flash-1017
- **Source:** `src/libraries/libds/1-dssys_2/func_000000B8.c` (image stub restored; library TU retained)
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
Oracle: libds_1::func_000000B8 verdict MISMATCH — 39/1276 words (3.06%).
Residual (steer by this, not the word count): control-flow 0, population 0, schedule 1, allocation 2.
Next block: 4 (0xA8) — population 0, schedule 1, allocation 0. smallest open residual
`psx_reverse_pipeline` gives the decisions, their source levers and the mechanism sheet to load; `psx_residual_objective` with a source ranks candidate edits and records them.

VALLEY: the best key [0, 0, 1, 2] is 3 term(s) from exact and 27 distinct programs since have not beaten it, across 26 distinct keys clustered around it. That is a floor, not a gradient. A best this close that a whole sweep cannot improve on means the remaining distance is several coordinates wide: every single-coordinate respelling moves one of the other coordinates the wrong way, scores worse, and reads as a refutation of the direction it tried. Sweeping one axis at a time cannot cross it however long it runs. Take the next experiment from the REQUIREMENT side instead of from another spelling:   psx_target_loop_emission  — what the original's loop pass must have emitted, and by which route   psx_triage                — its cluster-donor finding names a sibling that already reaches a                               mechanism this program does not, with the trace that measured it   psx_analyze_target_schedule / psx_allocator_counterfactual — the same for the later passes Write the program the requirement describes, in one edit, and measure that. STALLED: 36 distinct measurements since the residual last improved on [0, 0, 1, 2]. The axis is exhausted, not the function — stop re-spelling it and bring heavier evidence. Audit the premises first, because everything else is conditioned on them and cannot see them: psx_callee_truth confronts every callee declaration in scope with the vendored SDK headers and the callees' own code, psx_sdk_idioms does the same for operation boundaries. A wrong declaration adds call setup no rewrite of this body can remove, and every measurement taken under it scored a different program. Then read the pass that decides the residual before writing another spelling: its psx_reference sheet, or the deciding function itself through psx_compiler_source. After that, enumerate the source space (psx_search_source_shapes) or solve for the compiler state instead of modelling it (psx_solve_local_allocation, psx_search_scheduler_state, psx_allocator_counterfactual). A solver result is a specification for a source shape, and an UNSAT is a real finding that closes a direction. Record what each one closed with psx_record_closed, and read that record before you run one — a direction another session already closed costs minutes to close again. When a search reports no exact candidate, that is not the end of its output: read the per-class residual axes and the runs each class moved, and take the next experiment from the axis that moved rather than from the match count. Before trusting any search verdict, check its caveats for constructs the grammar refused, its axis-effect block for axes that are counted but inert, and its coverage — a --derive-only run sampled, and a sample supports no statement about the domain. 36 distinct programs is past the point where more variation is informative. Exhausting a spelling family is a positive result: the answer is not a spelling. Switch to the author's frame, which the compiler-side tools cannot reach. The vendored SDK headers give the real signature and the real operation for anything the SDK provides — read the header rather than your reconstruction of what the disassembly implies it must say. The already-matched functions in this target's file group are the only record of how this author wrote code: which locals they kept live, how they walked an array, what they hoisted, whether they took a base pointer once or re-indexed each time. A byte-exact neighbour is a proven idiom. notes/file-groupings.md names the group; read three of its members before reading another pass. A residual that survives every rewrite of your own idiom is usually somebody else's idiom.
```

## Preserved attempt

```c
#include "common.h"

typedef struct {
    DsCommand command[8];
    s32 index;
    s32 field4;
    s32 count;
} DsQueue;

extern DsQueue $LB_000015B8 __asm__("$LB_000015B8");
extern DsCommand commands[] __asm__("$LB_000015B8");
extern s32 $LB_00001678 __asm__("$LB_00001678");

static void func_000000B8(void) __asm__("$Lfunc_000000B8");

static void func_000000B8(void) {
    s32 *ip;
    s32 *jp;
    s32 *cnt;
    DsCommand *cmdq;
    s32 id;
    DsCommand *cmd;
    void (*self)(void);

    self = func_000000B8;
    (void) self;
    ip = &$LB_000015B8.index;
    cnt = &$LB_000015B8.count;
    cmdq = (DsCommand *) ((u8 *) ip - 0xC0);
    id = commands[*ip].active;
    jp = ip;
loop:
    if (*cnt <= 0) {
        goto done;
    }
    cmd = &cmdq[$LB_00001678];
    func_00000088(cmd);

    (*jp)++;
    if (*jp >= 8) {
        *jp = 0;
    }
    jp[2]--;
    if (commands[*jp].active == id) {
        goto loop;
    }
done:
    {
        s32 *fp = &$LB_000015B8.field4;
        *fp = fp[-1];
    }
}
```
