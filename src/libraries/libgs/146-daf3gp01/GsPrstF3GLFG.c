#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <inline_c.h>
#include <libgpu.h>
#include <libgs.h>

PACKET *GsPrstF3GLFG(TMD_P_F3G *op, VERT *vp, VERT *np, PACKET *pk, int n,
                     int shift, GsOT *ot, u_long *scratch) {
    struct {
        u_long limit;
        u_long val;
    } f;
    u_long *flg;
    u_long *tag;
    u_long flgmask;
    u_long tagmask;
    u_long packetlen;
    u_long code;
    int i;

    i = 0;
    if (i < n) {
        code = 0x30;
        flg = &f.val;
        flgmask = 0x80000000;
        tagmask = 0x00FFFFFF;
        packetlen = 0x06000000;
        do {
            gte_ldv3(&vp[op->v0], &vp[op->v1], &vp[op->v2]);
            gte_rtpt();
            f.limit = *(u_long *)&op->r0;
            *((u_char *)&f.limit + 3) = code;
            gte_stflg(flg);
            if (!(f.val & flgmask)) {
                gte_nclip();
                gte_stopz(flg);
                if (f.val != 0) {
                    gte_stsxy3_g3(pk);
                    gte_avsz3();
                    gte_stotz(flg);
                    gte_ldrgb(&f.limit);
                    gte_ldv0(&np[op->n0]);
                    gte_ncds();
                    tag = (u_long *)&ot->org[f.val >> shift];
                    gte_strgb(pk + 4);
                    gte_ldrgb(&op->r1);
                    gte_ldv0(&np[op->n0]);
                    gte_ncds();
                    *(u_long *)pk = (*tag & tagmask) | packetlen;
                    gte_strgb(pk + 0xC);
                    gte_ldrgb(&op->r2);
                    gte_ldv0(&np[op->n0]);
                    gte_ncds();
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
