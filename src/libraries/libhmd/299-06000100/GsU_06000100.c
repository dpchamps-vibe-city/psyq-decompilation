/* Recovered from the supplied Sony SRC/LIB/HMD/06000100.C. */
#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <inline_c.h>
#include <gtemac.h>
#include <asm.h>
#include <libgs.h>
#include <libhmd.h>

u_long *GsU_06000100(GsARGUNIT *ap)
{
    GsARGUNIT_SHARED *bp = (GsARGUNIT_SHARED *)ap;
    SVECTOR *sv;
    DVECTOR *dv;
    SVECTOR *cv;
    GsWORKUNIT *wu;
    u_long work;
    int num, flg, i, soffset, doffset;

    bp->primp++;
    num = *bp->primp;
    bp->primp++;
    soffset = *bp->primp;
    bp->primp++;
    doffset = *bp->primp;
    sv = bp->vertop + soffset;
    wu = bp->vertop2 + doffset;
    for (i = 0; i < num; i++, sv++, wu++) {
        gte_ldv0(sv);
        gte_rtps();
        gte_stflg(&flg);
        if (flg & 0x80000000) {
            *(u_long *)&wu->otz = 0xffffffff;
            continue;
        }
        gte_stsxy(&wu->vec);
        gte_stsz(&wu->otz);
        gte_stdp(&work);
        wu->p = (work & 0xffff);
    }

    bp->primp++;
    num = *bp->primp;
    bp->primp++;
    soffset = *bp->primp;
    bp->primp++;
    doffset = *bp->primp;
    sv = bp->nortop + soffset;
    cv = bp->nortop2 + doffset;
    for (i = 0; i < num; i++, sv++, cv++) {
        *cv = *sv;
    }
    bp->primp++;
    return bp->primp;
}
