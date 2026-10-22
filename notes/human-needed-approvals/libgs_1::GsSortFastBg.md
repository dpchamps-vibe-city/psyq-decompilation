# libgs_1::GsSortFastBg — human decision needed

- **Parked:** 2026-10-22T03:58:46.522Z
- **Reason:** escalation-exhausted
- **Escalation reached:** deepseek-v4-1-flash-1017
- **Source:** `src/libraries/libgs/1-2d_bg1/GsSortFastBg.c` (image stub restored; library TU retained)
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
Oracle: libgs_1::GsSortFastBg verdict MISMATCH — 116/496 words (23.39%).
Residual (steer by this, not the word count): control-flow 0, population 0, schedule 20, allocation 30.
Next block: 75 (0x63C) — population 0, schedule 1, allocation 2. smallest open residual

This block's residual shape `addu <reg>,<reg>,<reg>@-1` is not new.
It was closed in lib_51928ac182d7ab42_0::func_000000F8, which carried it at [2, 77, 1, 5] (50/87 words). The edit that closed it:

  ...
  extern u32 *_max_heap;
  
- u8 *func_000000F8(u8 *arg0, s32 arg1) {
+ u8 *func_000000F8(u8 *ptr, s32 bytes) {
      u32 *p;
      u32 *q;
  ...
      u8 *ret;
  
-     size = arg1;
+     size = bytes;
      size += 3;
      size &= ~3;
-     p = (u32 *) (arg0 - 4);
+     p = (u32 *) (ptr - 4);
      n = *p & ~1;
      if (n != size) {
  ...
              if (n < size) {
                  q = &p[*p >> 2] + 1;
-                 if (*q == (u32) -2) {
-                     extra = size - n;
-                     if ((((s32) ((s32) _max_heap - (s32) q) >> 2) * 4) - 8 >= extra) {
+                 if (*q != (u32) -2) {
+                     goto scan;
+                 }
+                 extra = size - n;
+                 if ((((s32) ((s32) _max_heap - (s32) q) >> 2) * 4) - 8 >= extra) {
  expand:
-                         *p += extra;
-                         newp = &q[extra >> 2];
-                         _Candidate = newp;
-                         _AllocRestBlockTop = newp;
-                         *newp = (u32) -2;
-                         _AllocRestBlockTop += 1;
+                     *p += extra;
+                     newp = &q[extra >> 2];
+                     _Candidate = newp;
+                     _AllocRestBlockTop = newp;
+                     *newp = (u32) -2;
+                     _AllocRestBlockTop += 1;
+                 }
+                 goto shrink;
+ 
+                 do {
+ scan:
+                     step = *q;
+                     if (!(step & 1)) {
+                         goto shrink;
                      }
-                 } else {
-                     while (*q & 1) {
-                         step = (*q & ~1) + 4;
-                         total += step;
-                         *p += step;
-                         if (total < size) {
-                             q = &q[*q >> 2] + 1;
-                             if (*q == (u32) -2) {
-                                 extra = size - total;
-                                 if ((((s32) ((s32) _max_heap - (s32) q) >> 2) * 4) - 8 >= extra) {
-                                     goto expand;
-                                 }
-                             } else {
-                                 continue;
-                             }
-                         }
-                         break;
+                     step = (step & ~1) + 4;
+                     total += step;
+                     *p += step;
+                     if (total >= size) {
+                         goto shrink;
                      }
+                     q = &q[*q >> 2] + 1;
+                 } while (*q != (u32) -2);
+                 extra = size - total;
+                 if ((((s32) ((s32) _max_heap - (s32) q) >> 2) * 4) - 8 >= extra) {
+                     goto expand;
                  }
              }
-         shrink:
+ shrink:
              n = *p & ~1;
              if (size < n) {
-                 q = &p[size >> 2];
-                 q[1] = (n - size - 4) | 1;
+                 p[(size >> 2) + 1] = (n - size - 4) | 1;
                  *p = size;
                  goto done;
              }
-             ret = arg0;
              if (n < size) {
-                 arg0 = 0;
-                 goto done;
+                 ptr = 0;
              }
+             goto done;
          }
      } else {
  done:
-         ret = arg0;
+         ret = ptr;
      }
      return ret;

That is a proven answer for this shape in this codebase. Try it before modelling the compiler.
Also closed in libgpu_0::FntOpen.
`psx_reverse_pipeline` gives the decisions, their source levers and the mechanism sheet to load; `psx_residual_objective` with a source ranks candidate edits and records them.

STALLED: 9 distinct measurements since the residual last improved on [0, 0, 17, 31]. The axis is exhausted, not the function — stop re-spelling it and bring heavier evidence. Audit the premises first, because everything else is conditioned on them and cannot see them: psx_callee_truth confronts every callee declaration in scope with the vendored SDK headers and the callees' own code, psx_sdk_idioms does the same for operation boundaries. A wrong declaration adds call setup no rewrite of this body can remove, and every measurement taken under it scored a different program. Then read the pass that decides the residual before writing another spelling: its psx_reference sheet, or the deciding function itself through psx_compiler_source. After that, enumerate the source space (psx_search_source_shapes) or solve for the compiler state instead of modelling it (psx_solve_local_allocation, psx_search_scheduler_state, psx_allocator_counterfactual). A solver result is a specification for a source shape, and an UNSAT is a real finding that closes a direction. Record what each one closed with psx_record_closed, and read that record before you run one — a direction another session already closed costs minutes to close again. When a search reports no exact candidate, that is not the end of its output: read the per-class residual axes and the runs each class moved, and take the next experiment from the axis that moved rather than from the match count. Before trusting any search verdict, check its caveats for constructs the grammar refused, its axis-effect block for axes that are counted but inert, and its coverage — a --derive-only run sampled, and a sample supports no statement about the domain. 9 distinct programs is past the point where more variation is informative. Exhausting a spelling family is a positive result: the answer is not a spelling. Switch to the author's frame, which the compiler-side tools cannot reach. The vendored SDK headers give the real signature and the real operation for anything the SDK provides — read the header rather than your reconstruction of what the disassembly implies it must say. The already-matched functions in this target's file group are the only record of how this author wrote code: which locals they kept live, how they walked an array, what they hoisted, whether they took a base pointer once or re-indexed each time. A byte-exact neighbour is a proven idiom. notes/file-groupings.md names the group; read three of its members before reading another pass. A residual that survives every rewrite of your own idiom is usually somebody else's idiom.
```

## Preserved attempt

```c
#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>
#include <stdio.h>

extern s16 GsORGOFSX;
extern s16 GsORGOFSY;

typedef struct {
    u_long tag;
    u_long tpage;
    u_long color;
    short x0, y0;
    u_char u0, v0;
    u_short cba;
    u_long wh;
} PKT18;

typedef struct {
    u_long tag;
    u_long color;
    short x0, y0;
    u_char u0, v0; u_short cba;
    short x1, y1;
    u_char u1, v1; u_short tpage;
    short x2, y2;
    u_char u2, v2; u_short pad1;
    short x3, y3;
    u_char u3, v3; u_short pad2;
} PKT28;

void GsSortFastBg(GsBG *bg, GsOT *ot, unsigned short pri)
{
    u_long attribute;
    GsMAP *map;
    u16 tpage;
    u32 c18, c28, dmaword;
    s32 w, h, xpr, yp;
    u16 cellw, cellh;
    s32 xp;
    s32 cellh16;
    u16 cellw16;
    u16 ncellw, ncellh;
    s32 mapw, maph;
    s32 wend, yend;
    s32 sx, sy, yoff, xoff, x, xclip, hclip;
    u32 xy, wh;
    s32 odd;
    s32 index;
    u16 cellidx;
    GsCELL *cell;
    u8 *p;
    PKT28 *ft4;
    PKT18 *pk;
    GsOT_TAG *tag;
    s32 z;
    s32 syfix;
    attribute = bg->attribute;
    if ((s32) attribute < 0) {
        return;
    }
    map = bg->map;
    cellw = map->cellw;
    if (cellw == 0) {
        cellw = 0x100;
    }
    cellh = map->cellh;
    if (cellh == 0) {
        cellh = 0x100;
    }
    cellw16 = cellw;
    (void) cellw16;
    ncellw = map->ncellw;
    mapw = cellw16 * ncellw;
    tpage = ((attribute >> 17) & 0x180) | ((attribute >> 23) & 0x60);
    sx = (s16) bg->scrollx % mapw;
    c18 = 0x64000000 | ((attribute >> 5) & 0x02000000)
        | ((attribute << 18) & 0x01000000) | bg->r | (bg->g << 8) | (bg->b << 16);
    c28 = 0x2C000000 | ((attribute >> 5) & 0x02000000)
        | ((attribute << 18) & 0x01000000) | bg->r | (bg->g << 8) | (bg->b << 16);
    xpr = (bg->x - bg->mx) + GsORGOFSX;
    ncellh = map->ncellh;
    cellh16 = cellh & 0xFFFF;
    maph = cellh16 * ncellh;
    p = GsOUT_PACKET_P;
    w = bg->w;
    yp = (bg->y - bg->my) + GsORGOFSY;
    h = bg->h;
    if (sx < 0) {
        sx += mapw;
    }
    syfix = (s16) bg->scrolly % maph;
    if (syfix < 0) {
        syfix += maph;
    }
    sy = syfix;
    yoff = sy % cellh16;
    xy &= 0xFFFF;
    xy |= yp << 16;
    wh &= 0xFFFF;
    wh |= (cellh16 - yoff) << 16;
    if (h < (s32) (wh >> 16)) {
        wh &= 0xFFFF;
        wh |= h << 16;
    }
    xp = xpr & 0xFFFF;
    dmaword = tpage | 0xE1000200;
    wend = sx + w;
    yend = sy + h;
    do {
        x = sx;
        xoff = x % cellw16;
        xy = (xy & 0xFFFF0000) | xp;
        xclip = (cellw - xoff) & 0xFFFF;
        wh &= 0xFFFF0000;
        wh |= xclip;
        if (w < xclip) {
            wh &= 0xFFFF0000;
            wh |= (u16) w;
        }
        index = ((sy % maph) / cellh) * ncellw + (x % mapw) / cellw16;
        cellidx = bg->map->index[index];
        if (cellidx != 0xFFFF) {
            cell = &bg->map->base[cellidx];
            odd = x & 1;
            if (odd) {
                ft4 = (PKT28 *) p;
                ft4->tag = (u_long) (p + 0x28);
                ((u8 *) ft4)[3] = 9;
                *(u_long *) &ft4->x0 = xy;
                ft4->color = c28;
                ft4->u0 = cell->u + xoff;
                ft4->v0 = cell->v + yoff;
                ft4->cba = cell->cba;
                ft4->x1 = (short) (xy + 1);
                ft4->y1 = (short) (xy >> 16);
                ft4->u1 = cell->u + xoff;
                ft4->v1 = cell->v + yoff;
                ft4->x2 = (short) xy;
                ft4->y2 = (short) ((xy >> 16) + (wh >> 16));
                ft4->tpage = tpage | (cell->tpage & 0x81F);
                ft4->u2 = cell->u + xoff;
                ft4->v2 = (wh >> 16) + (cell->v + yoff);
                ft4->x3 = (short) (xy + 1);
                ft4->y3 = (short) ((xy >> 16) + (wh >> 16));
                ft4->u3 = cell->u + xoff;
                ft4->v3 = (wh >> 16) + (cell->v + yoff);
                p += 0x28;
            }
            if (wh & 0xFFFE) {
                pk = (PKT18 *) p;
                pk->tag = (u_long) (p + 0x18);
                ((u8 *) pk)[3] = 5;
                pk->tpage = dmaword | (cell->tpage & 0x81F);
                pk->color = c18;
                pk->x0 = (short) (xy + odd);
                pk->y0 = (short) (xy >> 16);
                pk->u0 = (cell->u + xoff + 1) & ~1;
                pk->v0 = cell->v + yoff;
                pk->wh = wh & ~1;
                pk->cba = cell->cba;
                p += 0x18;
            }
        }
        index++;
        if ((index % ncellw) == 0) {
            index -= ncellw;
        }
        x += wh & 0xFFFF;
        xy = (xy & 0xFFFF0000) | ((xy + wh) & 0xFFFF);
        wh = (wh & 0xFFFF0000) | ((wend - x) & 0xFFFF);
        if ((u32) cellw16 < (u32) (wh & 0xFFFF)) {
            wh &= 0xFFFF0000;
            wh |= cellw16;
        }
        cellidx = bg->map->index[index];
        while (x < wend) {
            if (cellidx != 0xFFFF) {
                cell = &bg->map->base[cellidx];
                pk = (PKT18 *) p;
                pk->tag = (u_long) (p + 0x18);
                ((u8 *) pk)[3] = 5;
                pk->u0 = cell->u;
                pk->color = c18;
                *(u_long *) &pk->x0 = xy;
                pk->tpage = dmaword | (cell->tpage & 0x81F);
                pk->v0 = cell->v + yoff;
                pk->wh = wh;
                pk->cba = cell->cba;
                p += 0x18;
            }
            index++;
            if ((index % ncellw) == 0) {
                index -= ncellw;
            }
            x += wh & 0xFFFF;
            xy = (xy & 0xFFFF0000) | ((xy + wh) & 0xFFFF);
            wh = (wh & 0xFFFF0000) | ((wend - x) & 0xFFFF);
            if ((u32) cellw16 < (u32) (wh & 0xFFFF)) {
                wh &= 0xFFFF0000;
                wh |= cellw16;
            }
            cellidx = bg->map->index[index];
        }
        sy += wh >> 16;
        xy = (xy & 0xFFFF) | (((xy >> 16) + (wh >> 16)) << 16);
        wh &= 0xFFFF;
        wh |= (yend - sy) << 16;
        if ((u32) cellh < (u32) (wh >> 16)) {
            wh &= 0xFFFF;
            wh |= (u32) cellh << 16;
        }
        yoff = 0;
    } while (sy < yend);

    z = pri + ot->offset;
    if (z < 0) {
        printf("ps_sort_sprite,bg: z resolution overflow\n");
    }
    if (p != GsOUT_PACKET_P) {
        tag = &ot->org[z];
        p -= 0x18;
        *(u_long *) p = *(u_long *) tag;
        p[3] = 5;
        p += 0x18;
        *(u_long *) tag = (u_long) GsOUT_PACKET_P;
        ((u8 *) tag)[3] = 0;
    }
    GsOUT_PACKET_P = p;
}
```
