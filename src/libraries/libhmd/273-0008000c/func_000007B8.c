#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <inline_c.h>
#include <libgpu.h>
#include <libgs.h>

static void func_000007B8(VERTC *a, VERTC *b, VERTC *c, GsADIV_G3 *s)
{
    u_long *pk;

    gte_ldv3(a, b, c);
    gte_rtpt();
    pk = s->pk;
    *(u_long *)(pk + 1) = *(u_long *)&a->col;
    *(u_char *)((u_char *)pk + 3) = 6;
    *(u_char *)((u_char *)pk + 7) = 0x30;
    gte_stflg(&s->flg);
    if (s->flg >= 0) {
        gte_avsz3();
        gte_stsxy3_g3(pk);
        gte_stotz(&s->otz);
        *(u_long *)(pk + 3) = *(u_long *)&b->col;
        *(u_long *)(pk + 5) = *(u_long *)&c->col;
        s->tag = &s->org[s->otz >> s->shift];
        *(u_long *)pk = (*(u_long *)s->tag & 0xFFFFFF) | 0x06000000;
        *(u_long *)s->tag = (u_long)pk & 0xFFFFFF;
        s->pk += 7;
    }
}
