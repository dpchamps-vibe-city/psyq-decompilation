#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>

typedef struct {
    unsigned long type;
    unsigned long *ptr;
} GsTYPEUNIT;

extern u32 D_00000240;
extern u32 *D_00000244;
extern u32 *D_00000248;
extern u16 D_0000024C;

extern PACKET *GsOUT_PACKET_P;

int GsScanUnit(u_long *addr, GsTYPEUNIT *ut, GsOT *ot, u_long *arg) {
    u_long *p;
    u_long *r;
    u_long *q;
    u_long *a;
    u_long i;
    u_long t0;
    u_long t1;
    u_short t2;

    a = addr;
    if (a != NULL) {
        t0 = a[0];
        t1 = a[1];
        t2 = *(u_short *)((u_char *)a + 8);
        D_00000244 = (u32 *)(a + 3);
        D_00000240 = t0;
        D_00000248 = (u32 *)t1;
        D_0000024C = t2;
        return 0;
    }

    if ((short)--D_0000024C < 0) {
        p = (u_long *)D_00000240;
        if (p == (u_long *)-1)
            return 0;
        D_00000244 = (u32 *)p;
        D_00000240 = p[0];
        D_00000248 = (u32 *)p[1];
        D_0000024C = ((u_short *)p)[4] - 1;
        D_00000244 = (u32 *)(p + 3);
    }

    r = (u_long *)D_00000244;
    if ((s32)r[1] >= 0) {
        ut->type = 0;
        ut->ptr = NULL;
    } else {
        ut->type = r[0];
        ut->ptr = r;
        r[1] &= 0x7FFFFFFF;
    }

    arg[1] = (u_long)ot;
    arg[0] = (u_long)((u_long *)D_00000244 + 1);
    arg[2] = 0xE - ot->length;
    arg[3] = ot->offset;
    arg[4] = (u_long)GsOUT_PACKET_P;

    for (i = 0; i < *D_00000248; i++)
        arg[5 + i] = D_00000248[i + 1];

    q = (u_long *)D_00000244;
    D_00000244 = (u32 *)(q + 1);
    D_00000244 = (u32 *)((u_char *)D_00000244 +
        (((u_long)*(u_short *)((u_char *)q + 4)) << 2));
    return 1;
}
