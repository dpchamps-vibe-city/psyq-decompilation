#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <inline_c.h>
#include <libgpu.h>
#include <libgs.h>

PACKET *GsTMDfastF4GNL(TMD_P_F4G *op, VERT *vp, VERT *np, PACKET *input, int n,
                       int shift, GsOT *ot, u_long *scratch)
{
    GsADIV_F4 *s;
    PACKET *pk;
    u_long *flg;
    u_long flgmask;
    u_long packetlen;
    u_long tagmask;
    int i;

    pk = input;
    s = (GsADIV_F4 *)scratch;

    i = 0;
    s->org = (u_long *)ot->org;
    s->shift = shift;
    if (i < n) {
        for (; i < n; i++, op++) {
            gte_ldv3(&vp[op->v0], &vp[op->v1], &vp[op->v2]);
            gte_rtpt();
            *(u_long *)(pk + 4) = *(u_long *)&op->r0 & 0x00FFFFFF;
            *(u_char *)(pk + 7) = op->cd | 0x10;
            flg = (u_long *)&s->flg;
            flgmask = 0x80000000;
            gte_stflg(flg);
            if (!(s->flg & flgmask)) {
                gte_nclip();
                *(u_long *)(pk + 0xC) = *(u_long *)&op->r1;
                gte_stopz(&s->otz);
                if (s->otz > 0) {
                    gte_stsxy3_g4(pk);
                    gte_ldv0(&vp[op->v3]);
                    gte_rtps();
                    *(u_long *)(pk + 0x14) = *(u_long *)&op->r2;
                    gte_stflg(flg);
                    if (!(s->flg & flgmask)) {
                        gte_stsxy(pk + 0x20);
                        gte_avsz4();
                        *(u_long *)(pk + 0x1C) = *(u_long *)&op->r3;
                        gte_stotz(&s->otz);
                        tagmask = 0x00FFFFFF;
                        s->tag = &s->org[s->otz >> s->shift];
                        packetlen = 0x08000000;
                        *(u_long *)pk = (*s->tag & tagmask) | packetlen;
                        *s->tag = (u_long)pk & tagmask;
                        pk += 0x24;
                    }
                }
            }
        }
    }
    return pk;
}
