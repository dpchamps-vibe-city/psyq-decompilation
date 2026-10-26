#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <inline_c.h>
#include <libgpu.h>
#include <libgs.h>

PACKET *GsPrstG3GL(TMD_P_G3G *op, VERT *vp, VERT *np, PACKET *pk, int n,
                   int shift, GsOT *ot, u_long *scratch) {
    u_long val;
    u_long *tag;
    u_long flgmask;
    u_long tagmask;
    u_long packetlen;
    int i;

    i = 0;
    if (i < n) {
        flgmask = 0x80000000;
        tagmask = 0x00FFFFFF;
        packetlen = 0x06000000;
        do {
            gte_ldv3(&vp[op->v0], &vp[op->v1], &vp[op->v2]);
            gte_rtpt();
            gte_stflg(&val);
            if (!(val & flgmask)) {
                gte_nclip();
                gte_stopz(&val);
                if (val != 0) {
                    gte_stsxy3_g3(pk);
                    gte_avsz3();
                    gte_stotz(&val);
                    gte_ldrgb(&op->r0);
                    gte_ldv0(&np[op->n0]);
                    gte_nccs();
                    tag = (u_long *)&ot->org[val >> shift];
                    gte_strgb(pk + 4);
                    gte_ldrgb(&op->r1);
                    gte_ldv0(&np[op->n1]);
                    gte_nccs();
                    *(u_long *)pk = (*tag & tagmask) | packetlen;
                    gte_strgb(pk + 0xC);
                    gte_ldrgb(&op->r2);
                    gte_ldv0(&np[op->n2]);
                    gte_nccs();
                    *tag = (u_long)pk & tagmask;
                    gte_strgb(pk + 0x14);
                }
            }
            i++;
            op++;
            pk += 0x38;
        } while (i < n);
    }
    return pk;
}
