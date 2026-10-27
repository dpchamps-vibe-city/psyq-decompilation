# libmcrd_1::MemCardOpen — human decision needed

- **Parked:** 2026-10-27T17:36:54.249Z
- **Reason:** escalation-exhausted
- **Escalation reached:** gpt-6.1-sol
- **Source:** `src/libraries/libmcrd/1-libmcrd/MemCardOpen.c` (image stub restored; library TU retained)
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
Oracle: libmcrd_1::MemCardOpen verdict MISMATCH — 1586/1588 words (99.87%).
Residual (steer by this, not the word count): control-flow 0, population 0, schedule 1, allocation 0.
Next block: 2 (0x7F8) — population 0, schedule 1, allocation 0. smallest open residual
`psx_reverse_pipeline` gives the decisions, their source levers and the mechanism sheet to load; `psx_residual_objective` with a source ranks candidate edits and records them.

STALLED: 29 distinct measurements since the residual last improved on [0, 0, 0, 2]. The axis is exhausted, not the function — stop re-spelling it and bring heavier evidence. Audit the premises first, because everything else is conditioned on them and cannot see them: psx_callee_truth confronts every callee declaration in scope with the vendored SDK headers and the callees' own code, psx_sdk_idioms does the same for operation boundaries. A wrong declaration adds call setup no rewrite of this body can remove, and every measurement taken under it scored a different program. Then read the pass that decides the residual before writing another spelling: its psx_reference sheet, or the deciding function itself through psx_compiler_source. After that, enumerate the source space (psx_search_source_shapes) or solve for the compiler state instead of modelling it (psx_solve_local_allocation, psx_search_scheduler_state, psx_allocator_counterfactual). A solver result is a specification for a source shape, and an UNSAT is a real finding that closes a direction. Record what each one closed with psx_record_closed, and read that record before you run one — a direction another session already closed costs minutes to close again. When a search reports no exact candidate, that is not the end of its output: read the per-class residual axes and the runs each class moved, and take the next experiment from the axis that moved rather than from the match count. Before trusting any search verdict, check its caveats for constructs the grammar refused, its axis-effect block for axes that are counted but inert, and its coverage — a --derive-only run sampled, and a sample supports no statement about the domain. 29 distinct programs is past the point where more variation is informative. Exhausting a spelling family is a positive result: the answer is not a spelling. Switch to the author's frame, which the compiler-side tools cannot reach. The vendored SDK headers give the real signature and the real operation for anything the SDK provides — read the header rather than your reconstruction of what the disassembly implies it must say. The already-matched functions in this target's file group are the only record of how this author wrote code: which locals they kept live, how they walked an array, what they hoisted, whether they took a base pointer once or re-indexed each time. A byte-exact neighbour is a proven idiom. notes/file-groupings.md names the group; read three of its members before reading another pass. A residual that survives every rewrite of your own idiom is usually somebody else's idiom.
```

## Preserved attempt

```c
#include "common.h"
#include <libapi.h>
#include <libmcrd.h>
#include <stdio.h>
#include <strings.h>
#include "libmcrd_internal.h"

extern long B_00001B8C;
extern MemCB B_00001BD0;
extern char RO_STR_00001A54[];
extern void _clr_card_event(void);
static void func_000018FC(long, char *);
static s32 T_00000580(s32 *);

long MemCardOpen(long chan, char *file, long flag)
{
    long result;
    long *fd = &((McrdState *)&B_00001B78)->unk14;
    char *path;
    McrdState *state;
    long descriptor;
    long retries = 0;

    if (fd[0] >= 0) {
        printf(RO_STR_00001A54);
        return -1;
    }
    path = (char *)(fd + 4);
    func_000018FC(chan, path);
    strcat(path, file);
    state = (McrdState *)&B_00001B78;
    fd[-1] = chan;
    do {
        do {
            descriptor = open(path, 1);
            if (descriptor >= 0)
                goto opened;
            B_00001BD0 = MemCardCallback(0);
            if (*(long *)(path - 0x24) > 0) {
                printf(RO_STR_00001958);
            } else {
                *(long *)(path - 0x24) = 2;
                state->unk04 = 0;
                state->unk08 = 0;
                *(long *)((char *)B_00001B48 + 0x40) = chan;
                UserFuncOpen(T_00000580);
            }
            MemCardSync(0, 0, &result);
            MemCardCallback(B_00001BD0);
        } while (result == 3);
        if (result != 2)
            break;
        ++retries;
    } while (retries < 5);
    if (result == 0)
        result = 5;
    return result;

opened:
    close(descriptor);
    _clr_card_event();
    *(long *)(path - 0x10) = open(path, flag | 0x8000);
    return 0;
}
```
