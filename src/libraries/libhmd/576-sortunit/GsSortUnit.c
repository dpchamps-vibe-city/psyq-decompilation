#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>
#include <libhmd.h>

void GsSortUnit(GsUNIT *unit, GsOT *ot, u_long *work)
{
    GsARGUNIT *arg = (GsARGUNIT *)work;
    u_long *next;
    u_long *head;
    u_long *p;
    u_long *out;
    u_long *term = (u_long *)GsUNIT_TERM;
    u_long count;
    u_long i;
    u_long *(*sort)(GsARGUNIT *);

    arg->primp = unit->primtop;
    next = unit->primtop;
    arg->tagp = ot;
    arg->shift = 14 - ot->length;
    arg->offset = ot->offset;
    arg->out_packetp = GsOUT_PACKET_P;
    do {
        arg->primp = next;
        p = next;
        next = (u_long *)*next;
        arg->primp = p + 1;
        head = (u_long *)p[1];
        i = 0;
        if (*head != 0) {
            out = (u_long *)(arg + 1);
            do {
                *out++ = head[i + 1];
                i++;
            } while (i < *head);
        }
        count = *++arg->primp;
        arg->primp++;
        for (i = 0; i < count; i++) {
            sort = (u_long *(*)(GsARGUNIT *))*arg->primp++;
            arg->primp = sort(arg);
            arg->out_packetp = GsOUT_PACKET_P;
        }
    } while (next != term);
}
