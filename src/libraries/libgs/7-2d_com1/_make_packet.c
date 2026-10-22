#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>
#include <stdio.h>

extern char RO_STR_00000110[];

u_char *_make_packet(u_char *p, GsOT *ot, u_short z, u_char flag) {
    GsOT_TAG *t;
    s32 i;

    i = z - ot->offset;
    if (i < 0) {
        printf(RO_STR_00000110);
    }
    t = &ot->org[i];
    *(u_long *)p = *(u_long *)t;
    p[3] = flag;
    *(u_long *)t = (u_long)p;
    t->num = 0;
    return p + (flag * 4 + 4);
}
