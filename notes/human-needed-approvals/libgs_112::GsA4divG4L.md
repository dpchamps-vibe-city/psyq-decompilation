# libgs_112::GsA4divG4L — human decision needed

- **Parked:** 2026-10-26T00:12:53.458Z
- **Reason:** escalation-exhausted
- **Escalation reached:** gpt-6.1-sol
- **Source:** `src/libraries/libgs/112-dag4_00/GsA4divG4L.c` (image stub restored; library TU retained)
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
Oracle: libgs_112::GsA4divG4L verdict MISMATCH — 776/784 words (98.98%).
Residual (steer by this, not the word count): control-flow 0, population 0, schedule 0, allocation 2.
Next block: 0 (0x0) — population 0, schedule 0, allocation 2. smallest open residual
`psx_reverse_pipeline` gives the decisions, their source levers and the mechanism sheet to load; `psx_residual_objective` with a source ranks candidate edits and records them.

VALLEY: the best key [0, 0, 0, 2] is 2 term(s) from exact and 8 distinct programs since have not beaten it, across 8 distinct keys clustered around it. That is a floor, not a gradient. A best this close that a whole sweep cannot improve on means the remaining distance is several coordinates wide: every single-coordinate respelling moves one of the other coordinates the wrong way, scores worse, and reads as a refutation of the direction it tried. Sweeping one axis at a time cannot cross it however long it runs. Take the next experiment from the REQUIREMENT side instead of from another spelling:   psx_target_loop_emission  — what the original's loop pass must have emitted, and by which route   psx_triage                — its cluster-donor finding names a sibling that already reaches a                               mechanism this program does not, with the trace that measured it   psx_analyze_target_schedule / psx_allocator_counterfactual — the same for the later passes Write the program the requirement describes, in one edit, and measure that. STALLED: 14 distinct measurements since the residual last improved on [0, 0, 0, 2]. The axis is exhausted, not the function — stop re-spelling it and bring heavier evidence. Audit the premises first, because everything else is conditioned on them and cannot see them: psx_callee_truth confronts every callee declaration in scope with the vendored SDK headers and the callees' own code, psx_sdk_idioms does the same for operation boundaries. A wrong declaration adds call setup no rewrite of this body can remove, and every measurement taken under it scored a different program. Then read the pass that decides the residual before writing another spelling: its psx_reference sheet, or the deciding function itself through psx_compiler_source. After that, enumerate the source space (psx_search_source_shapes) or solve for the compiler state instead of modelling it (psx_solve_local_allocation, psx_search_scheduler_state, psx_allocator_counterfactual). A solver result is a specification for a source shape, and an UNSAT is a real finding that closes a direction. Record what each one closed with psx_record_closed, and read that record before you run one — a direction another session already closed costs minutes to close again. When a search reports no exact candidate, that is not the end of its output: read the per-class residual axes and the runs each class moved, and take the next experiment from the axis that moved rather than from the match count. Before trusting any search verdict, check its caveats for constructs the grammar refused, its axis-effect block for axes that are counted but inert, and its coverage — a --derive-only run sampled, and a sample supports no statement about the domain. 14 distinct programs is past the point where more variation is informative. Exhausting a spelling family is a positive result: the answer is not a spelling. Switch to the author's frame, which the compiler-side tools cannot reach. The vendored SDK headers give the real signature and the real operation for anything the SDK provides — read the header rather than your reconstruction of what the disassembly implies it must say. The already-matched functions in this target's file group are the only record of how this author wrote code: which locals they kept live, how they walked an array, what they hoisted, whether they took a base pointer once or re-indexed each time. A byte-exact neighbour is a proven idiom. notes/file-groupings.md names the group; read three of its members before reading another pass. A residual that survives every rewrite of your own idiom is usually somebody else's idiom.
```

## Preserved attempt

```c
#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <inline_c.h>
#include <libgpu.h>
#include <libgs.h>

static void func_000004C8(GsADIV_P_G4 *p, GsADIV_G4 *s, int level);

PACKET *GsA4divG4L(TMD_P_G4 *op, VERT *vp, VERT *np, PACKET *pk, int n, int shift, GsOT *ot, u_long *scratch) {
    GsADIV_G4 *s;
    GsADIV_P_G4 *p;
    GsADIV_P_G4 *q;
    TMD_P_G4 *tp;
    PACKET *a;
    u_long t0;
    u_long t1;
    long *otz;
    int i;

    s = (GsADIV_G4 *)scratch;

    s->hwd0 = HWD0 / 2;
    s->vwd0 = VWD0 / 2;
    s->org = (u_long *)ot->org;
    s->shift = shift;
    s->adivz = GsADIVZ;
    s->adivw = GsADIVW;
    s->adivh = GsADIVH;
    s->pk = (u_long *)pk;
    s->si.code = op->cd;

    a = (PACKET *)s->pk;
    p = (GsADIV_P_G4 *)(scratch + sizeof(GsADIV_G4) / 4);
    q = p;
    tp = op;
    i = 0;

    if (n > 0) {
    otz = &s->otz;
    t1 = 0x40000;
    t0 = 0x80000000;
    do {
        gte_ldrgb(&tp->r0);
        gte_ldv3(&vp[tp->v0], &vp[tp->v1], &vp[tp->v2]);
        gte_rtpt();
        gte_stflg((u_long *)&s->flg0);
        gte_nclip();
        gte_stopz(otz);
        if (s->otz > 0) {
            gte_stsxy3_g4(a);
            gte_ldv0(&vp[tp->v3]);
            gte_rtps();
            gte_stflg((u_long *)&s->flg);
            if ((s->flg & t1) == 0 || (s->flg0 & t1) == 0) {
                gte_stsxy(a + 0x20);
                gte_avsz4();
                gte_stotz(otz);
                gte_ldv3(&np[tp->n0], &np[tp->n1], &np[tp->n2]);
                gte_ncct();
                s->tag = &s->org[s->otz >> s->shift];
                gte_strgb3(a + 4, a + 0xC, a + 0x14);
                gte_ldv0(&np[tp->n3]);
                gte_nccs();
                gte_strgb(a + 0x1C);
                if (s->otz >= s->adivz && !(s->flg0 & t0) && !(s->flg & t0)) {
                    *(u_long *)a = (*s->tag & 0x00FFFFFF) | 0x08000000;
                    *s->tag = (u_long)a & 0x00FFFFFF;
                    a += 0x24;
                } else {
                    (*(VERT *)&q->vt[0].vx) = (*(VERT *)&vp[tp->v0].vx);
                    (*(u_long *)&q->vt[0].col) = *(u_long *)(a + 4);
                    (*(VERT *)&q->vt[1].vx) = (*(VERT *)&vp[tp->v1].vx);
                    (*(u_long *)&q->vt[1].col) = *(u_long *)(a + 0xC);
                    (*(VERT *)&q->vt[2].vx) = (*(VERT *)&vp[tp->v2].vx);
                    (*(u_long *)&q->vt[2].col) = *(u_long *)(a + 0x14);
                    (*(VERT *)&q->vt[3].vx) = (*(VERT *)&vp[tp->v3].vx);
                    (*(u_long *)&q->vt[3].col) = *(u_long *)(a + 0x1C);
                    s->pk = (u_long *)a;
                    func_000004C8(p, s, 0);
                    a = (PACKET *)s->pk;
                }
            }
        }
        i++;
        tp++;
    } while (i < n);
    }
    s->pk = (u_long *)a;
    return a;
}
```
