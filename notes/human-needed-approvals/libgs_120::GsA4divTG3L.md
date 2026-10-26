# libgs_120::GsA4divTG3L — human decision needed

- **Parked:** 2026-10-26T01:24:23.282Z
- **Reason:** escalation-exhausted
- **Escalation reached:** gpt-6.1-sol
- **Source:** `src/libraries/libgs/120-datg3_00/GsA4divTG3L.c` (image stub restored; library TU retained)
- **Preserved attempt:** library measurements have no staged ranking; kept the current complete TU, including neighboring functions/data
- **Parking notes:** src/libraries/libgs/120-datg3_00/func_00000958.c: pre-attempt source restored; attempt archived at /home/dave/Documents/code/psyq-decomp/run_output/autoloop/attempts/libgs_120::GsA4divTG3L.func_00000958.c.2026-10-26T01-24-23-282Z.parked.c; src/libraries/libgs/120-datg3_00/func_00000AA4.c: pre-attempt source restored; attempt archived at /home/dave/Documents/code/psyq-decomp/run_output/autoloop/attempts/libgs_120::GsA4divTG3L.func_00000AA4.c.2026-10-26T01-24-23-282Z.parked.c

## What the loop needs

Every tier on the escalation ladder returned without a byte-exact match. The function
needs either a new structural hypothesis or a policy decision that the ladder cannot
make on its own. The preserved attempt and the oracle report below are the starting
point.

## Policy findings

- none recorded

## Oracle report for the preserved attempt

```
Oracle: libgs_120::GsA4divTG3L verdict MISMATCH — 704/716 words (98.32%).
Residual (steer by this, not the word count): control-flow 0, population 0, schedule 3, allocation 3.
Next block: 0 (0x0) — population 0, schedule 3, allocation 1. smallest open residual
`psx_reverse_pipeline` gives the decisions, their source levers and the mechanism sheet to load; `psx_residual_objective` with a source ranks candidate edits and records them.

STALLED: 6 distinct measurements since the residual last improved on [0, 0, 3, 1]. The axis is exhausted, not the function — stop re-spelling it and bring heavier evidence. Audit the premises first, because everything else is conditioned on them and cannot see them: psx_callee_truth confronts every callee declaration in scope with the vendored SDK headers and the callees' own code, psx_sdk_idioms does the same for operation boundaries. A wrong declaration adds call setup no rewrite of this body can remove, and every measurement taken under it scored a different program. Then read the pass that decides the residual before writing another spelling: its psx_reference sheet, or the deciding function itself through psx_compiler_source. After that, enumerate the source space (psx_search_source_shapes) or solve for the compiler state instead of modelling it (psx_solve_local_allocation, psx_search_scheduler_state, psx_allocator_counterfactual). A solver result is a specification for a source shape, and an UNSAT is a real finding that closes a direction. Record what each one closed with psx_record_closed, and read that record before you run one — a direction another session already closed costs minutes to close again. When a search reports no exact candidate, that is not the end of its output: read the per-class residual axes and the runs each class moved, and take the next experiment from the axis that moved rather than from the match count. Before trusting any search verdict, check its caveats for constructs the grammar refused, its axis-effect block for axes that are counted but inert, and its coverage — a --derive-only run sampled, and a sample supports no statement about the domain.
```

## Preserved attempt

```c
#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <inline_c.h>
#include <libgpu.h>
#include <libgs.h>

static void func_00000458(GsADIV_P_GT3 *p, GsADIV_GT3 *s, int level);

PACKET *GsA4divTG3L(TMD_P_TG3 *op, VERT *vp, VERT *np, PACKET *pk, int n, int shift, GsOT *ot, u_long *scratch) {
    GsADIV_GT3 *ifo;
    GsADIV_P_GT3 *p;
    GsADIV_P_GT3 *q;
    TMD_P_TG3 *tp;
    POLY_GT3 *si;
    int i;
    short adivw;
    short adivh;

    adivw = GsADIVW;
    adivh = GsADIVH;
    ifo = (GsADIV_GT3 *)scratch;
    scratch += sizeof(GsADIV_GT3) / 4;
    p = (GsADIV_P_GT3 *)scratch;
    q = p;

    ifo->hwd0 = HWD0 / 2;
    ifo->vwd0 = VWD0 / 2;
    ifo->org = (u_long *)ot->org;
    ifo->shift = shift;
    ifo->adivw = adivw;
    ifo->adivh = adivh;
    ifo->pk = (u_long *)pk;
    ifo->adivz = GsADIVZ;

    ifo->si.code = op->cd;
    ifo->si.r0 = 0x80;
    ifo->si.g0 = 0x80;
    ifo->si.b0 = 0x80;
    ifo->si.r1 = 0x80;
    ifo->si.g1 = 0x80;
    ifo->si.b1 = 0x80;
    ifo->si.r2 = 0x80;
    ifo->si.g2 = 0x80;
    ifo->si.b2 = 0x80;
    gte_ldrgb((u_long *)&ifo->si.r0);

    si = (POLY_GT3 *)ifo->pk;
    tp = op;

    for (i = 0; i < n; i++, tp++) {
        gte_ldv3(&vp[tp->v0], &vp[tp->v1], &vp[tp->v2]);
        gte_rtpt();
        *(u_long *)&si->u0 = *(u_long *)&tp->tu0;
        *(u_long *)&si->u2 = *(u_long *)&tp->tu2;
        gte_stflg((u_long *)&ifo->flg);
        gte_nclip();
        gte_stopz(&ifo->otz);
        if (ifo->otz <= 0)
            continue;
        if (ifo->flg & 0x00040000)
            continue;
        gte_stsxy3_gt3((u_long *)si);
        gte_avsz3();
        gte_stotz(&ifo->otz);
        gte_ldv3(&np[tp->n0], &np[tp->n1], &np[tp->n2]);
        gte_ncct();
        *(u_long *)&si->u1 = *(u_long *)&tp->tu1;
        ifo->tag = (u_long *)(ifo->org + (ifo->otz >> ifo->shift));
        gte_strgb3(&si->r0, &si->r1, &si->r2);
        if (ifo->otz < ifo->adivz)
            goto divide;
        if (ifo->flg & 0x80000000)
            goto divide;
        *(u_long *)si = (*ifo->tag & 0x00ffffff) | 0x09000000;
        *ifo->tag = (u_long)si & 0x00ffffff;
        si++;
        continue;

divide:
        *(VERT *)&q->vt[0] = vp[tp->v0];
        *(u_long *)&q->vt[0].col = *(u_long *)&si->r0;
        *(VERT *)&q->vt[1] = vp[tp->v1];
        *(u_long *)&q->vt[1].col = *(u_long *)&si->r1;
        *(VERT *)&q->vt[2] = vp[tp->v2];
        *(u_long *)&q->vt[2].col = *(u_long *)&si->r2;
        *(u_short *)&q->vt[0].tu = *(u_short *)&tp->tu0;
        *(u_short *)&q->vt[1].tu = *(u_short *)&tp->tu1;
        *(u_short *)&q->vt[2].tu = *(u_short *)&tp->tu2;
        ifo->si.clut = tp->clut;
        ifo->si.tpage = tp->tpage;
        ifo->pk = (u_long *)si;
        func_00000458(p, ifo, 0);
        si = (POLY_GT3 *)ifo->pk;
    }
    ifo->pk = (u_long *)si;
    return (PACKET *)si;
}
```
