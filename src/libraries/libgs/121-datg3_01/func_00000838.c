#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <inline_c.h>
#include <libgpu.h>
#include <libgs.h>

void func_00000838(VERTC *a, VERTC *b, VERTC *c, GsADIV_GT3 *s)
{
    u_long *pk;
    POLY_GT3 *si;

    gte_ldv3(a, b, c);
    gte_rtpt();

    pk = s->pk;
    pk[1] = *(u_long *)&a->col;
    gte_stflg(&s->flg);
    if (s->flg < 0) {
        return;
    }
    gte_avsz3();
    gte_stsxy3_gt3(pk);
    gte_stotz(&s->otz);

    pk[3] = *(u_short *)&a->tu;
    pk[6] = *(u_short *)&b->tu;
    pk[9] = *(u_short *)&c->tu;
    pk[4] = *(u_long *)&b->col;
    pk[7] = *(u_long *)&c->col;

    si = (POLY_GT3 *)pk;
    si->clut = s->si.clut;
    si->tpage = s->si.tpage;

    s->tag = &s->org[s->otz >> s->shift];
    pk[0] = (*(u_long *)s->tag & 0xFFFFFF) | 0x09000000;
    *(u_long *)s->tag = (u_long)pk & 0xFFFFFF;
    s->pk += 0xA;
}
