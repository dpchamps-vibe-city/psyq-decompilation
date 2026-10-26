#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <inline_c.h>
#include <libgpu.h>
#include <libgs.h>

PACKET *GsTMDfastG3GL(TMD_P_G3G *op, VERT *vp, VERT *np, PACKET *pk, int n,
                      int shift, GsOT *ot, u_long *scratch) {
    GsADIV_G3 *s;
    u_long *flg;
    u_long flgmask;
    u_long packetlen;
    u_long tagmask;
    int i;

    s = (GsADIV_G3 *)scratch;

    i = 0;
    s->org = (u_long *)ot->org;
    s->shift = shift;
    if (i < n) {
        flg = (u_long *)&s->flg;
        flgmask = 0x80000000;
        do {
            gte_ldv3(&vp[op->v0], &vp[op->v1], &vp[op->v2]);
            gte_rtpt();
            gte_stflg(flg);
            if (!(s->flg & flgmask)) {
                gte_nclip();
                gte_stopz(&s->otz);
                if (s->otz > 0) {
                    gte_stsxy3_g3(pk);
                    gte_avsz3();
                    gte_stotz(&s->otz);
                    gte_ldrgb(&op->r0);
                    gte_ldv0(&np[op->n0]);
                    gte_nccs();
                    tagmask = 0x00FFFFFF;
                    s->tag = &s->org[s->otz >> s->shift];
                    gte_strgb(pk + 4);
                    gte_ldrgb(&op->r1);
                    gte_ldv0(&np[op->n1]);
                    gte_nccs();
                    packetlen = 0x06000000;
                    *(u_long *)pk = (*s->tag & tagmask) | packetlen;
                    gte_strgb(pk + 0xC);
                    gte_ldrgb(&op->r2);
                    gte_ldv0(&np[op->n2]);
                    gte_nccs();
                    *s->tag = (u_long)pk & tagmask;
                    gte_strgb(pk + 0x14);
                    pk += 0x1C;
                }
            }
            i++;
            op++;
        } while (i < n);
    }
    return pk;
}
