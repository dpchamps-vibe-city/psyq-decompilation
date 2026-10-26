INCLUDE_ASM("build/libraries/nonmatchings/libgs_120", func_00000AA4);


/* PARKED by /auto_decompilation_loop on 2026-10-26T01:24:23.282Z.
 * Reason: escalation-exhausted.
 * Escalation reached: gpt-6.1-sol.
 * The best non-matching attempt is preserved verbatim below, disabled.
 * Findings and the decision needed: notes/human-needed-approvals/libgs_120::GsA4divTG3L.md
 */

#if 0
/* Best non-matching attempt, preserved for the next session. */
#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <inline_c.h>
#include <libgpu.h>
#include <libgs.h>

static void func_00000AA4(VERTC *d, VERTC *a, VERTC *b)
{
    d->vx = (a->vx + b->vx) / 2;
    d->vy = (a->vy + b->vy) / 2;
    d->vz = (a->vz + b->vz) / 2;
    d->col.r = (a->col.r + b->col.r) / 2;
    d->col.g = (a->col.g + b->col.g) / 2;
    d->col.b = (a->col.b + b->col.b) / 2;
    d->col.cd = a->col.cd;
    d->tu = (a->tu + b->tu) / 2;
    d->tv = (a->tv + b->tv) / 2;
}
#endif
