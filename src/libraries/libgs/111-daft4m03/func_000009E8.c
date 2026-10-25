#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <inline_c.h>
#include <libgpu.h>
#include <libgs.h>

static void func_000009E8(VERT *a, VERT *b, VERT *c, GsADIV_FT4 *s) {
    u_long *pk;

    gte_ldv3(a, b, c);
    gte_rtpt();
    pk = s->pk;
    *(u_long *)(pk + 1) = (*(u_long *)&s->si.r0 & 0x02FFFFFF) | 0x24000000;
    gte_stflg(&s->flg);
    if (s->flg >= 0) {
        gte_avsz3();
        gte_stsxy3_ft4(pk);
        gte_stotz(&s->otz);
        *(u_long *)(pk + 3) = *(u_short *)&a->tu;
        *(u_long *)(pk + 5) = *(u_short *)&b->tu;
        *(u_long *)(pk + 7) = *(u_short *)&c->tu;
        *(u_short *)((u_char *)pk + 0xE) = s->si.clut;
        *(u_short *)((u_char *)pk + 0x16) = s->si.tpage;
        s->tag = &s->org[s->otz >> s->shift];
        *(u_long *)pk = (*(u_long *)s->tag & 0xFFFFFF) | 0x07000000;
        *(u_long *)s->tag = (u_long)pk & 0xFFFFFF;
        s->pk += 8;
    }
}
