# libgs_111::GsA4divTNF4M — human decision needed

- **Parked:** 2026-10-26T00:26:26.069Z
- **Reason:** escalation-exhausted
- **Escalation reached:** gpt-6.1-sol
- **Source:** `src/libraries/libgs/111-daft4m03/GsA4divTNF4M.c` (image stub restored; library TU retained)
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
Oracle: libgs_111::GsA4divTNF4M verdict MISMATCH — 805/828 words (97.22%).
Residual (steer by this, not the word count): control-flow 0, population 0, schedule 0, allocation 7.
Next block: 5 (0x1EC) — population 0, schedule 0, allocation 2. smallest open residual
`psx_reverse_pipeline` gives the decisions, their source levers and the mechanism sheet to load; `psx_residual_objective` with a source ranks candidate edits and records them.

STALLED: 13 distinct measurements since the residual last improved on [0, 0, 0, 3]. The axis is exhausted, not the function — stop re-spelling it and bring heavier evidence. Audit the premises first, because everything else is conditioned on them and cannot see them: psx_callee_truth confronts every callee declaration in scope with the vendored SDK headers and the callees' own code, psx_sdk_idioms does the same for operation boundaries. A wrong declaration adds call setup no rewrite of this body can remove, and every measurement taken under it scored a different program. Then read the pass that decides the residual before writing another spelling: its psx_reference sheet, or the deciding function itself through psx_compiler_source. After that, enumerate the source space (psx_search_source_shapes) or solve for the compiler state instead of modelling it (psx_solve_local_allocation, psx_search_scheduler_state, psx_allocator_counterfactual). A solver result is a specification for a source shape, and an UNSAT is a real finding that closes a direction. Record what each one closed with psx_record_closed, and read that record before you run one — a direction another session already closed costs minutes to close again. When a search reports no exact candidate, that is not the end of its output: read the per-class residual axes and the runs each class moved, and take the next experiment from the axis that moved rather than from the match count. Before trusting any search verdict, check its caveats for constructs the grammar refused, its axis-effect block for axes that are counted but inert, and its coverage — a --derive-only run sampled, and a sample supports no statement about the domain. 13 distinct programs is past the point where more variation is informative. Exhausting a spelling family is a positive result: the answer is not a spelling. Switch to the author's frame, which the compiler-side tools cannot reach. The vendored SDK headers give the real signature and the real operation for anything the SDK provides — read the header rather than your reconstruction of what the disassembly implies it must say. The already-matched functions in this target's file group are the only record of how this author wrote code: which locals they kept live, how they walked an array, what they hoisted, whether they took a base pointer once or re-indexed each time. A byte-exact neighbour is a proven idiom. notes/file-groupings.md names the group; read three of its members before reading another pass. A residual that survives every rewrite of your own idiom is usually somebody else's idiom.
```

## Preserved attempt

```c
#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <inline_c.h>
#include <libgpu.h>
#include <libgs.h>

static void func_00000588(GsADIV_P_FT4 *p, GsADIV_FT4 *s, int level);

PACKET *GsA4divTNF4M(TMD_P_TNF4 *op, VERT *vp, PACKET *pk, int n, int shift, GsOT *ot, u_long *scratch)
{
    GsADIV_FT4 *s;
    GsADIV_P_FT4 *p;
    GsADIV_P_FT4 *q;
    PACKET *a;
    long *otz;
    u_long t0;
    u_long t1;
    u_long tagmask;
    int i;
    int u0, v0, uw, vh, n0, nv2;

    s = (GsADIV_FT4 *)scratch;
    p = (GsADIV_P_FT4 *)(scratch + sizeof(GsADIV_FT4) / 4);
    q = p;
    s->org = (u_long *)ot->org;
    s->shift = shift;
    s->adivz = GsADIVZ;
    s->adivw = GsADIVW;
    s->adivh = GsADIVH;
    s->pk = (u_long *)pk;
    s->hwd0 = HWD0 / 2;
    s->vwd0 = VWD0 / 2;
    setPolyFT4(&s->si);
    a = (PACKET *)s->pk;
    i = 0;
    if (n > 0) {
        otz = &s->otz;
        t1 = 0x40000;
        t0 = 0x80000000;
        tagmask = 0xFFFFFF;
        do {
            gte_ldv3(&vp[op->v0], &vp[op->v1], &vp[op->v2]);
            gte_rtpt();
            *(u_long *)(a + 0x0C) = *(u_long *)&op->tu0;
            *(u_long *)(a + 0x14) = *(u_long *)&op->tu1;
            gte_stflg((u_long *)&s->flg0);
            gte_nclip();
            *(u_long *)(a + 0x1C) = *(u_long *)&op->tu2;
            gte_stopz(otz);
            if (s->otz > 0) {
                gte_stsxy3_ft4(a);
                gte_ldv0(&vp[op->v3]);
                gte_rtps();
                *(u_long *)(a + 0x24) = *(u_long *)&op->tu3;
                gte_stflg((u_long *)&s->flg);
                if ((s->flg & t1) == 0 || (s->flg0 & t1) == 0) {
                    gte_stsxy(a + 0x20);
                    u0 = a[0x0C];
                    v0 = a[0x0D];
                    uw = (a[0x24] - u0 + 1) & 0xFFFE;
                    vh = (a[0x25] - v0 + 1) & 0xFFFE;
                    n0 = u0;
                    n0 += uw;
                    if (s->otz < (uw * vh) >> 6) {
                        int h3;

                        uw >>= 3;
                        n0 += uw;
                        nv2 = v0 + (vh >> 1);
                        h3 = vh >> 3;
                        nv2 += h3;
                        uw--;
                        uw += n0;
                        h3--;
                        a[0x0D] = nv2;
                        a[0x15] = nv2;
                        nv2 += h3;
                        a[0x0C] = n0;
                        a[0x14] = uw;
                        a[0x1C] = n0;
                        a[0x1D] = nv2;
                        a[0x24] = uw;
                        a[0x25] = nv2;
                    } else if (s->otz < (uw * vh) >> 4) {
                        int w, h, ew, u, v;

                        w = uw >> 2;
                        u = n0 + w;
                        v = v0 + (vh >> 1);
                        ew = w - 1;
                        h = (vh >> 2) - 1;
                        setUVWH((POLY_FT4 *)a, u, v, ew, h);
                    } else if (s->otz < (uw * vh) >> 2) {
                        int h;

                        uw >>= 1;
                        uw--;
                        uw += n0;
                        h = vh >> 1;
                        h--;
                        nv2 = v0 + h;
                        setUV4((POLY_FT4 *)a, n0, v0, uw, v0, n0, nv2, uw, nv2);
                    }
                    gte_avsz4();
                    *(u_long *)(a + 4) = *(u_long *)&op->r0 | 0x2C000000;
                    gte_stotz(otz);
                    s->tag = &s->org[s->otz >> s->shift];
                    if (s->otz >= s->adivz && !(s->flg0 & t0) && !(s->flg & t0)) {
                        *(u_long *)a = (*(u_long *)s->tag & tagmask) | 0x09000000;
                        *(u_long *)s->tag = (u_long)a & tagmask;
                        a += 0x28;
                    } else {
                        *(u_long *)&s->si.r0 = *(u_long *)(a + 4);
                        q->vt[0] = vp[op->v0];
                        q->vt[1] = vp[op->v1];
                        q->vt[2] = vp[op->v2];
                        q->vt[3] = vp[op->v3];
                        *(u_short *)&q->vt[0].tu = *(u_short *)&op->tu0;
                        *(u_short *)&q->vt[1].tu = *(u_short *)&op->tu1;
                        *(u_short *)&q->vt[2].tu = *(u_short *)&op->tu2;
                        *(u_short *)&q->vt[3].tu = *(u_short *)&op->tu3;
                        s->si.clut = op->clut;
                        s->si.tpage = op->tpage;
                        s->pk = (u_long *)a;
                        func_00000588(p, s, 0);
                        a = (PACKET *)s->pk;
                    }
                }
            }
            i++;
            op++;
        } while (i < n);
    }
    s->pk = (u_long *)a;
    return a;
}
```
