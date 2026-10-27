# libmcrd_1::func_000001FC — human decision needed

- **Parked:** 2026-10-27T16:33:21.187Z
- **Reason:** escalation-exhausted
- **Escalation reached:** gpt-6.1-sol
- **Source:** `src/libraries/libmcrd/1-libmcrd/func_000001FC.c` (image stub restored; library TU retained)
- **Preserved attempt:** library measurements have no staged ranking; kept the current complete TU, including neighboring functions/data
- **Parking notes:** src/libraries/libmcrd/1-libmcrd/MemCardStop.c: pre-attempt source restored; attempt archived at /home/dave/Documents/code/psyq-decomp/run_output/autoloop/attempts/libmcrd_1::func_000001FC.MemCardStop.c.2026-10-27T16-33-21-187Z.parked.c

## What the loop needs

Every tier on the escalation ladder returned without a byte-exact match. The function
needs either a new structural hypothesis or a policy decision that the ladder cannot
make on its own. The preserved attempt and the oracle report below are the starting
point.

## Policy findings

- none recorded

## Oracle report for the preserved attempt

```
Oracle: libmcrd_1::func_000001FC verdict MISMATCH — 180/1588 words (11.34%).
Residual (steer by this, not the word count): control-flow 0, population 2, schedule 10, allocation 21.
The two programs do not contain the same instructions, so no allocation or scheduling reading applies yet — fix the semantics first.
Next block: 12 (0x29C) — population 1, schedule 0, allocation 0. the instruction populations differ here; nothing below can be read until they agree
`psx_reverse_pipeline` gives the decisions, their source levers and the mechanism sheet to load; `psx_residual_objective` with a source ranks candidate edits and records them.

STALLED: 4 distinct measurements since the residual last improved on [0, 2, 10, 21]. The axis is exhausted, not the function — stop re-spelling it and bring heavier evidence. Audit the premises first, because everything else is conditioned on them and cannot see them: psx_callee_truth confronts every callee declaration in scope with the vendored SDK headers and the callees' own code, psx_sdk_idioms does the same for operation boundaries. A wrong declaration adds call setup no rewrite of this body can remove, and every measurement taken under it scored a different program. Then read the pass that decides the residual before writing another spelling: its psx_reference sheet, or the deciding function itself through psx_compiler_source. After that, enumerate the source space (psx_search_source_shapes) or solve for the compiler state instead of modelling it (psx_solve_local_allocation, psx_search_scheduler_state, psx_allocator_counterfactual). A solver result is a specification for a source shape, and an UNSAT is a real finding that closes a direction. Record what each one closed with psx_record_closed, and read that record before you run one — a direction another session already closed costs minutes to close again. When a search reports no exact candidate, that is not the end of its output: read the per-class residual axes and the runs each class moved, and take the next experiment from the axis that moved rather than from the match count. Before trusting any search verdict, check its caveats for constructs the grammar refused, its axis-effect block for axes that are counted but inert, and its coverage — a --derive-only run sampled, and a sample supports no statement about the domain.
```

## Preserved attempt

```c
#include "common.h"
#include <libapi.h>
#include <stdio.h>
#include "libmcrd_internal.h"

extern s32 B_00001B48;
extern volatile s32 B_00001B4C;
extern u32 D_00001B28;
extern s32 D_00001B2C;
extern char RO_STR_00001980[];

extern void _clr_card_event(void);
extern long _chk_card_event(void);
extern long _get_card_event(void);
extern long _chk_card_event_x(void);
extern long _get_card_event_x(void);

static s32 func_000017FC(s32);

static s32 func_000001FC(s32 *arg)
{
    McrdState *mcrd;
    long *p;
    long *q;
    long *slot;
    s32 ev;
    s32 v;
    s32 w;
    s32 retryState = 10;

    switch (arg[0]) {
    case 0:
        p = &((McrdState *)&B_00001B78)->unk10;
        B_00001B4C = 0;
        B_00001B48 = 0;
        arg[0] = retryState;
        v = p[0];
        p += 16;
        slot = &p[v >> 4];
        v = *slot;
        *slot = 0;
        D_00001B28 = v;
        /* fall through */
    case 10:
        _clr_card_event();
        _card_info(((McrdState *)&B_00001B78)->unk10);
        arg[0] = arg[0] + 1;
        goto complete;

    case 11:
        if (_chk_card_event() == 0)
            return 0;
        ev = _get_card_event();
        B_00001B4C = ev;
        p = &((McrdState *)&B_00001B78)->unk10;
        q = p + 14;
        v = p[0];
        slot = &q[v >> 4];
        w = *slot;
        D_00001B2C = w;
        switch (ev) {
        case 4:
            if (w != 0)
                goto retry;
            if (D_00001B28 >= 0x80U)
                goto retry;
            _clr_card_event();
            _card_clear(p[0]);
            arg[0] = 21;
            goto complete;
        retry:
            p = &((McrdState *)&B_00001B78)->unk10;
            p[(p[0] >> 4) + 14] = 1;
            p -= 4;
            p[1] = func_000017FC(B_00001B4C);
            return 1;

        case 0:
            if ((p[-1] & (1 << v)) == 0)
                B_00001B4C = 4;
            *slot = 0;
            ((McrdState *)&B_00001B78)->unk04 = func_000017FC(B_00001B4C);
            return 1;

        case 2:
            if (++B_00001B48 >= 3) {
                *slot = 1;
                ((McrdState *)&B_00001B78)->unk04 = func_000017FC(2);
                return 1;
            }
            goto retry_info;

        case 1:
            if (++B_00001B48 < 0x11) {
        retry_info:
                arg[0] = retryState;
                return 0;
            }
            ((McrdState *)&B_00001B78)->unk04 = func_000017FC(1);
            q[p[0] >> 4] = 0;
            return 1;

        default:
            mcrd = (McrdState *)&B_00001B78;
            mcrd->unk04 = func_000017FC(B_00001B4C);
            (&mcrd->unk48)[mcrd->unk10 >> 4] = 0;
            return 1;
        }

    case 21:
        if (_chk_card_event_x() != 0) {
            _get_card_event_x();
            arg[0] = 0;
        }
        return 0;

    default:
        printf(RO_STR_00001980);
        break;
    }
complete:
    return 0;
}
```
