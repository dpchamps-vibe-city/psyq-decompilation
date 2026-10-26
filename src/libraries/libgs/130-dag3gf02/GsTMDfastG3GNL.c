#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <inline_c.h>
#include <libgpu.h>
#include <libgs.h>

PACKET *GsTMDfastG3GNL(TMD_P_G3G *op, VERT *vp, VERT *np, PACKET *input, int n,
                      int shift, GsOT *ot, u_long *scratch) {
    GsADIV_G3 *s;
    PACKET *pk;
    u_long *flg;
    u_long flgmask;
    u_long packetlen;
    u_long tagmask;
    int i;

    pk = input;
    s = (GsADIV_G3 *)scratch;

    i = 0;
    s->org = (u_long *)ot->org;
    s->shift = shift;
    if (i < n) {
        flg = (u_long *)&s->flg;
        flgmask = 0x80000000;
        for (; i < n; i++, op++) {
            gte_ldv3(&vp[op->v0], &vp[op->v1], &vp[op->v2]);
            gte_rtpt();
            *(u_long *)(pk + 4) = *(u_long *)&op->r0;
            gte_stflg(flg);
            if (!(s->flg & flgmask)) {
                gte_nclip();
                *(u_long *)(pk + 0xC) = *(u_long *)&op->r1;
                gte_stopz(&s->otz);
                if (s->otz > 0) {
                    gte_stsxy3_g3(pk);
                    gte_avsz3();
                    *(u_long *)(pk + 0x14) = *(u_long *)&op->r2;
                    gte_stotz(&s->otz);
                    tagmask = 0x00FFFFFF;
                    s->tag = &s->org[s->otz >> s->shift];
                    packetlen = 0x06000000;
                    *(u_long *)pk = (*s->tag & tagmask) | packetlen;
                    *s->tag = (u_long)pk & tagmask;
                    pk += 0x1C;
                }
            }
        }
    }
    return pk;
}
