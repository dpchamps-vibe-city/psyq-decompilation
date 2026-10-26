INCLUDE_ASM("build/libraries/nonmatchings/libgs_120", func_00000958);


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

static s32 func_00000958(POLY_GT3 *si, GsADIV_GT3 *s)
{
    minmax3(si->x0, si->x1, si->x2, s->minx, s->maxx);
    if ((s->maxx < -s->hwd0) || (s->minx > s->hwd0))
        return 1;
    minmax3(si->y0, si->y1, si->y2, s->miny, s->maxy);
    if ((s->maxy < -s->vwd0) || (s->miny > s->vwd0))
        return 1;
    return 0;
}
#endif
