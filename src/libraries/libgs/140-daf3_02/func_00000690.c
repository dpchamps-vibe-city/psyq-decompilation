#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <inline_c.h>
#include <libgpu.h>
#include <libgs.h>

static void func_00000690(VERT *a, VERT *b, VERT *c, GsADIV_F3 *s)
{
    POLY_F3 *pk;

    gte_ldv3(a, b, c);
    gte_rtpt();
    pk = (POLY_F3 *)s->pk;
    *(u_long *)&pk->r0 = *(u_long *)&s->si.r0;
    setPolyF3(pk);
    if (s->si.code & 2) {
        setSemiTrans(pk, 1);
    }
    gte_stflg(&s->flg);
    if (s->flg >= 0) {
        gte_avsz3();
        gte_stsxy3_f3(pk);
        gte_stotz(&s->otz);
        s->tag = &s->org[s->otz >> s->shift];
        *(u_long *)pk = (*(u_long *)s->tag & 0xFFFFFF) | 0x04000000;
        *(u_long *)s->tag = (u_long)pk & 0xFFFFFF;
        s->pk += 5;
    }
}
