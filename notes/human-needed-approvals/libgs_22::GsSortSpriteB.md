# libgs_22::GsSortSpriteB — human decision needed

- **Parked:** 2026-10-23T16:34:20.929Z
- **Reason:** escalation-exhausted
- **Escalation reached:** deepseek-v4-1-flash-1017
- **Source:** `src/libraries/libgs/22-2d_sp0b/GsSortSpriteB.c` (image stub restored; library TU retained)
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
Oracle: libgs_22::GsSortSpriteB verdict MISMATCH — 262/324 words (80.86%).
Residual (steer by this, not the word count): control-flow 0, population 0, schedule 15, allocation 28.
Next block: 20 (0x3D8) — population 0, schedule 15, allocation 25. smallest open residual
`psx_reverse_pipeline` gives the decisions, their source levers and the mechanism sheet to load; `psx_residual_objective` with a source ranks candidate edits and records them.

STALLED: 39 distinct measurements since the residual last improved on [0, 0, 15, 28]. The axis is exhausted, not the function — stop re-spelling it and bring heavier evidence. Audit the premises first, because everything else is conditioned on them and cannot see them: psx_callee_truth confronts every callee declaration in scope with the vendored SDK headers and the callees' own code, psx_sdk_idioms does the same for operation boundaries. A wrong declaration adds call setup no rewrite of this body can remove, and every measurement taken under it scored a different program. Then read the pass that decides the residual before writing another spelling: its psx_reference sheet, or the deciding function itself through psx_compiler_source. After that, enumerate the source space (psx_search_source_shapes) or solve for the compiler state instead of modelling it (psx_solve_local_allocation, psx_search_scheduler_state, psx_allocator_counterfactual). A solver result is a specification for a source shape, and an UNSAT is a real finding that closes a direction. Record what each one closed with psx_record_closed, and read that record before you run one — a direction another session already closed costs minutes to close again. When a search reports no exact candidate, that is not the end of its output: read the per-class residual axes and the runs each class moved, and take the next experiment from the axis that moved rather than from the match count. Before trusting any search verdict, check its caveats for constructs the grammar refused, its axis-effect block for axes that are counted but inert, and its coverage — a --derive-only run sampled, and a sample supports no statement about the domain. 39 distinct programs is past the point where more variation is informative. Exhausting a spelling family is a positive result: the answer is not a spelling. Switch to the author's frame, which the compiler-side tools cannot reach. The vendored SDK headers give the real signature and the real operation for anything the SDK provides — read the header rather than your reconstruction of what the disassembly implies it must say. The already-matched functions in this target's file group are the only record of how this author wrote code: which locals they kept live, how they walked an array, what they hoisted, whether they took a base pointer once or re-indexed each time. A byte-exact neighbour is a proven idiom. notes/file-groupings.md names the group; read three of its members before reading another pass. A residual that survives every rewrite of your own idiom is usually somebody else's idiom.
```

## Preserved attempt

```c
#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>

extern s16 GsORGOFSX;
extern s16 GsORGOFSY;
extern u_char *_make_packet(u_char *p, GsOT *ot, u_short z, u_char flag);

void GsSortSpriteB(GsSPRITE *sp, GsOT *ot, unsigned short pri, unsigned short flip) {
    MATRIX m;
    SVECTOR rot;
    VECTOR vec;
    SVECTOR v0;
    SVECTOR v1;
    SVECTOR v2;
    SVECTOR v3;
    long sxy[4];
    long pz;
    long flg;
    u_long attribute;
    u_long *p;
    u_long u0;
    u_long u1;
    u_long vv0;
    u_long vv1;
    u_long word;
    u_long hibits;
    s32 flag;
    s32 ofsx;
    s32 ofsy;
    s32 sx;
    s32 sy;
    s32 rotoff;

    attribute = sp->attribute;
    if ((s32) attribute < 0) {
        return;
    }
    if (sp->w == 0) {
        return;
    }
    if (sp->h == 0) {
        return;
    }
    p = (u_long *) GsOUT_PACKET_P;
    rotoff = (attribute >> 27) & 1;
    flag = 0;
    if (*(s32 *) &sp->scalex == 0x10001000 && sp->rotate == 0) {
        flag = (attribute & 0xC00000) == 0;
    }
    if (rotoff | flag) {
        sx = sp->x + GsORGOFSX;
        sy = sp->y + GsORGOFSY;
        p[1] = (sp->tpage & 0x81F) | 0xE1000200
             | ((attribute >> 17) & 0x180)
             | ((attribute >> 23) & 0x60)
             | ((flip & 3) << 12);
        p[2] = ((attribute >> 5) & 0x02000000) | 0x64000000
             | ((attribute << 18) & 0x01000000)
             | (sp->b << 16) | (sp->g << 8) | sp->r;
        p[3] = ((sx - sp->mx) & 0xFFFF) | ((sy - sp->my) << 16);
        p[4] = sp->u | (sp->v << 8) | (sp->cy << 22)
             | ((sp->cx << 12) & 0x3F0000);
        word = sp->w;
        p[5] = word | (sp->h << 16);
        p = (u_long *) _make_packet((u_char *) p, ot, pri, 5);
    } else {
        if (sp->rotate == 0) {
            m = GsIDMATRIX;
        } else {
            rot.vx = 0;
            rot.vy = 0;
            rot.vz = sp->rotate / 360;
            RotMatrix(&rot, &m);
        }
        if (*(s32 *) &sp->scalex != 0x10001000) {
            vec.vx = sp->scalex;
            vec.vy = sp->scaley;
            vec.vz = 0;
            ScaleMatrix(&m, &vec);
        }
        vec.vx = sp->x;
        vec.vy = sp->y;
        vec.vz = ReadGeomScreen();
        TransMatrix(&m, &vec);
        SetRotMatrix(&m);
        SetTransMatrix(&m);
        ofsx = -sp->mx;
        ofsy = -sp->my;
        v0.vx = ofsx;
        v0.vy = ofsy;
        v0.vz = 0;
        v1.vx = sp->w + ofsx;
        v1.vy = ofsy;
        v1.vz = 0;
        v2.vx = ofsx;
        v2.vy = sp->h + ofsy;
        v2.vz = 0;
        v3.vx = sp->w + ofsx;
        v3.vy = sp->h + ofsy;
        v3.vz = 0;
        RotTransPers4(&v0, &v1, &v2, &v3, &sxy[0], &sxy[1], &sxy[2], &sxy[3],
                      &pz, &flg);
        if (attribute & 0x800000) {
            u0 = (sp->u + (u_char) sp->w) - 1;
            u1 = sp->u;
        } else {
            u0 = sp->u;
            u1 = (sp->u + (u_char) sp->w) - 1;
        }
        if (attribute & 0x400000) {
            vv0 = (sp->v + (u_char) sp->h) - 1;
            vv1 = sp->v;
        } else {
            vv0 = sp->v;
            vv1 = (sp->v + (u_char) sp->h) - 1;
        }
        p[1] = ((attribute >> 5) & 0x02000000) | 0x2C000000
             | ((attribute << 18) & 0x01000000)
             | (sp->b << 16) | (sp->g << 8) | sp->r;
        p[2] = sxy[0];
        p[4] = sxy[1];
        p[3] = (u0 & 0xFF) | ((vv0 & 0xFF) << 8) | (sp->cy << 22)
             | ((sp->cx << 12) & 0x3F0000);
        hibits = attribute >> 1;
        p[6] = sxy[2];
        p[7] = (u0 & 0xFF) | ((vv1 & 0xFF) << 8);
        p[8] = sxy[3];
        p[9] = (u1 & 0xFF) | ((vv1 & 0xFF) << 8);
        word = (u1 & 0xFF) | ((vv0 & 0xFF) << 8) | ((sp->tpage & 0x81F) << 16)
             | (hibits & 0x01800000);
        p[5] = word | ((attribute >> 7) & 0x600000);
        p = (u_long *) _make_packet((u_char *) p, ot, pri, 9);
    }
    GsOUT_PACKET_P = (PACKET *) p;
}
```
