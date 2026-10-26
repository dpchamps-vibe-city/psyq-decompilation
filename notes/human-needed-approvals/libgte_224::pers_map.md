# libgte_224::pers_map — human decision needed

- **Parked:** 2026-10-26T11:37:10.414Z
- **Reason:** escalation-exhausted
- **Escalation reached:** gpt-6.1-sol
- **Source:** `src/libraries/libgte/224-ppmft/pers_map.c` (image stub restored; library TU retained)
- **Preserved attempt:** library measurements have no staged ranking; kept the current complete TU, including neighboring functions/data
- **Parking notes:** src/libraries/libgte/224-ppmft/func_00000C84.c: pre-attempt source restored; attempt archived at /home/dave/Documents/code/psyq-decomp/run_output/autoloop/attempts/libgte_224::pers_map.func_00000C84.c.2026-10-26T11-37-10-414Z.parked.c

## What the loop needs

Every tier on the escalation ladder returned without a byte-exact match. The function
needs either a new structural hypothesis or a policy decision that the ladder cannot
make on its own. The preserved attempt and the oracle report below are the starting
point.

## Policy findings

- none recorded

## Oracle report for the preserved attempt

```
Oracle: libgte_224::pers_map verdict UNKNOWN — 0/0 words (0%).
Residual (steer by this, not the word count): control-flow 0, population 38, schedule 18, allocation 30.
The two programs do not contain the same instructions, so no allocation or scheduling reading applies yet — fix the semantics first.
Next block: 54 (0xA78) — population 1, schedule 0, allocation 0. the instruction populations differ here; nothing below can be read until they agree
`psx_reverse_pipeline` gives the decisions, their source levers and the mechanism sheet to load; `psx_residual_objective` with a source ranks candidate edits and records them.

STALLED: 5 distinct measurements since the residual last improved on [0, 38, 18, 30]. The axis is exhausted, not the function — stop re-spelling it and bring heavier evidence. Audit the premises first, because everything else is conditioned on them and cannot see them: psx_callee_truth confronts every callee declaration in scope with the vendored SDK headers and the callees' own code, psx_sdk_idioms does the same for operation boundaries. A wrong declaration adds call setup no rewrite of this body can remove, and every measurement taken under it scored a different program. Then read the pass that decides the residual before writing another spelling: its psx_reference sheet, or the deciding function itself through psx_compiler_source. After that, enumerate the source space (psx_search_source_shapes) or solve for the compiler state instead of modelling it (psx_solve_local_allocation, psx_search_scheduler_state, psx_allocator_counterfactual). A solver result is a specification for a source shape, and an UNSAT is a real finding that closes a direction. Record what each one closed with psx_record_closed, and read that record before you run one — a direction another session already closed costs minutes to close again. When a search reports no exact candidate, that is not the end of its output: read the per-class residual axes and the runs each class moved, and take the next experiment from the axis that moved rather than from the match count. Before trusting any search verdict, check its caveats for constructs the grammar refused, its axis-effect block for axes that are counted but inert, and its coverage — a --derive-only run sampled, and a sample supports no statement about the domain.
```

## Preserved attempt

```c
#include "common.h"
#include <sys/types.h>
#include <libgte.h>

static int func_00000C84();
static void func_000013FC(int abuf, short *sxy, int (*tex)[2], MATRIX *m, u_short *dtext);

/*
 * Perspective-map a quad: rotate four vertices, clip them, project each
 * resulting vertex and draw the textured polygon.
 */
void pers_map(int abuf, SVECTOR **vertex, int tex[4][2], u_short *dtext)
{
    struct {
        VECTOR  clipped[2][4];
        int     clipTex[8][2];
        DVECTOR projected[2][4];
    } buf;
    VECTOR transformed[4];
    MATRIX m;
    long flag[2];
    long ofx, ofy;
    long n;
    long i;
    DVECTOR *dst;
    long screen;
    long x, y;

    RotTrans(vertex[0], &transformed[0], &flag);
    RotTrans(vertex[1], &transformed[1], &flag);
    RotTrans(vertex[2], &transformed[2], &flag);
    RotTrans(vertex[3], &transformed[3], &flag);

    m.m[0][0] = transformed[1].vx - transformed[0].vx;
    m.m[0][1] = transformed[3].vx - transformed[0].vx;
    m.m[0][2] = transformed[0].vx;
    m.m[1][0] = transformed[1].vy - transformed[0].vy;
    m.m[1][1] = transformed[3].vy - transformed[0].vy;
    m.m[1][2] = transformed[0].vy;
    m.m[2][0] = transformed[1].vz - transformed[0].vz;
    m.m[2][1] = transformed[3].vz - transformed[0].vz;
    m.m[2][2] = transformed[0].vz;

    n = func_00000C84(transformed, tex, 8, buf.clipped[0], buf.clipTex);

    for (i = 0; i < n; i++) {
        dst = (DVECTOR *)((char *)buf.projected + (i << 4));
        screen = ReadGeomScreen();
        ReadGeomOffset(&ofx, &ofy);
        x = ofx + buf.clipped[i][0].vx * screen / buf.clipped[i][0].vz;
        y = ofy + buf.clipped[i][0].vy * screen / buf.clipped[i][0].vz;
        if (x < -0x8000) x = -0x8000;
        if (x > 0x7FFF) x = 0x7FFF;
        if (y < -0x8000) y = -0x8000;
        if (y > 0x7FFF) y = 0x7FFF;
        dst[0].vx = x;
        dst[0].vy = y;

        screen = ReadGeomScreen();
        ReadGeomOffset(&ofx, &ofy);
        {
            VECTOR *cv = &buf.clipped[i][1];
            x = ofx + cv->vx * screen / cv->vz;
            y = ofy + cv->vy * screen / cv->vz;
        }
        if (x < -0x8000) x = -0x8000;
        if (x > 0x7FFF) x = 0x7FFF;
        if (y < -0x8000) y = -0x8000;
        if (y > 0x7FFF) y = 0x7FFF;
        dst[1].vx = x;
        dst[1].vy = y;

        screen = ReadGeomScreen();
        ReadGeomOffset(&ofx, &ofy);
        {
            VECTOR *cv = &buf.clipped[i][2];
            x = ofx + cv->vx * screen / cv->vz;
            y = ofy + cv->vy * screen / cv->vz;
        }
        if (x < -0x8000) x = -0x8000;
        if (x > 0x7FFF) x = 0x7FFF;
        if (y < -0x8000) y = -0x8000;
        if (y > 0x7FFF) y = 0x7FFF;
        dst[2].vx = x;
        dst[2].vy = y;

        screen = ReadGeomScreen();
        ReadGeomOffset(&ofx, &ofy);
        {
            VECTOR *cv = &buf.clipped[i][3];
            x = ofx + cv->vx * screen / cv->vz;
            y = ofy + cv->vy * screen / cv->vz;
        }
        if (x < -0x8000) x = -0x8000;
        if (x > 0x7FFF) x = 0x7FFF;
        if (y < -0x8000) y = -0x8000;
        if (y > 0x7FFF) y = 0x7FFF;
        dst[3].vx = x;
        dst[3].vy = y;

        if (NormalClip(*(long *)&buf.projected[i][0], *(long *)&buf.projected[i][1], *(long *)&buf.projected[i][2]) <= 0)
            break;

        func_000013FC(abuf, (short *)dst, tex, &m, dtext);
    }
}
```
