#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>
#include <libhmd.h>

long GsLinkAnim(GsSEQ **tsk, u_long *top) {
    GsSEQ **tskp;
    u_long *tp;
    long num;
    long i;

    tskp = tsk;
    tp = top + 2;
    num = *(u_short *) ((u_char *) top + 6);
    for (i = 0; i < num; i++) {
        *tskp++ = (GsSEQ *) tp;
        tp += *(u_short *) ((u_char *) tp + 4);
    }
    return num;
}
