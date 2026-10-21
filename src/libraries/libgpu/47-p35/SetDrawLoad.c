#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

void SetDrawLoad(DR_LOAD *p, RECT *rect) {
    u_long n;
    u_long len;

    n = (rect->w * rect->h + 1) / 2;
    len = n + 4;
    if (n >= 13) {
        len = 0;
    }
    setlen(p, len);
    p->code[0] = 0xa0000000;
    p->code[1] = *(u_long *)&rect->x;
    p->code[2] = *(u_long *)&rect->w;
    p->p[len - 4] = 0x01000000;
}
