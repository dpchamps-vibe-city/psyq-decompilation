#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <inline_c.h>
#include <libgpu.h>
#include <libgs.h>

static void func_0000088C(VERTC *a, VERTC *b, VERTC *c, GsADIV_G4 *s) {
    POLY_G3 *pk;

    gte_ldv3(a, b, c);
    gte_rtpt();
    pk = (POLY_G3 *)s->pk;
    *(u_long *)&pk->r0 = *(u_long *)&a->col;
    setPolyG3(pk);
    if (s->si.code & 2) {
        setSemiTrans(pk, 1);
    }
    gte_stflg(&s->flg);
    if (!(s->flg & 0x60000)) {
        gte_avsz3();
        gte_stsxy3_g3(pk);
        gte_stotz(&s->otz);
        *(u_long *)&pk->r1 = *(u_long *)&b->col;
        *(u_long *)&pk->r2 = *(u_long *)&c->col;
        s->tag = &s->org[s->otz >> s->shift];
        *(u_long *)pk = (*s->tag & 0xFFFFFF) | 0x06000000;
        *s->tag = (u_long)pk & 0xFFFFFF;
        s->pk += 7;
    }
}
