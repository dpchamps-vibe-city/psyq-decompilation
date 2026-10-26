#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <inline_c.h>
#include <libgpu.h>
#include <libgs.h>

PACKET *GsTMDfastF3M(TMD_P_F3 *op, VERT *vp, VERT *np, PACKET *pk, int n,
                     int shift, GsOT *ot, u_long *scratch)
{
    GsADIV_F3 *s;
    u_long *flg;
    long *otz;
    u_long flgmask;
    u_long tagmask;
    u_long packetlen;
    int i, j;
    int mate;

    mate = GsMATE_C;
    s = (GsADIV_F3 *)scratch;
    s->org = (u_long *)ot->org;
    s->shift = shift;
    if ((GsLIGNR == 0 && GsLIGHT_MODE == 2) ||
        (GsLIGNR == 1 && GsLMODE == 2)) {
        i = 0;
        if (i < n) {
            flg = (u_long *)&s->flg;
            flgmask = 0x80000000;
            otz = &s->otz;
            tagmask = 0x00FFFFFF;
            packetlen = 0x04000000;
            do {
                gte_ldv3(&vp[op->v0], &vp[op->v1], &vp[op->v2]);
                gte_rtpt();
                gte_stflg(flg);
                if (!(s->flg & flgmask)) {
                    gte_nclip();
                    gte_stopz(otz);
                    if (s->otz > 0) {
                        gte_stsxy3_f3(pk);
                        gte_avsz3();
                        gte_stotz(otz);
                        gte_ldrgb(&op->r0);
                        gte_ldv0(&np[op->n0]);
                        gte_ll();
                        for (j = 0; j < mate; j++) {
                            gte_sqr12();
                        }
                        gte_cc();
                        gte_strgb(pk + 4);
                        s->tag = &s->org[s->otz >> s->shift];
                        *(u_long *)pk = (*s->tag & tagmask) | packetlen;
                        *s->tag = (u_long)pk & tagmask;
                        pk += 0x14;
                    }
                }
                i++;
                op++;
            } while (i < n);
        }
    } else {
        u_long *flg;
        long *otz;
        u_long flgmask;
        u_long tagmask;
        u_long packetlen;

        i = 0;
        if (i < n) {
            flg = (u_long *)&s->flg;
            flgmask = 0x80000000;
            otz = &s->otz;
            tagmask = 0x00FFFFFF;
            packetlen = 0x04000000;
            do {
                gte_ldv3(&vp[op->v0], &vp[op->v1], &vp[op->v2]);
                gte_rtpt();
                gte_stflg(flg);
                if (!(s->flg & flgmask)) {
                    gte_nclip();
                    gte_stopz(otz);
                    if (s->otz > 0) {
                        gte_stsxy3_f3(pk);
                        gte_avsz3();
                        gte_stotz(otz);
                        gte_ldrgb(&op->r0);
                        gte_ldv0(&np[op->n0]);
                        gte_nccs();
                        s->tag = &s->org[s->otz >> s->shift];
                        *(u_long *)pk = (*s->tag & tagmask) | packetlen;
                        *s->tag = (u_long)pk & tagmask;
                        gte_strgb(pk + 4);
                        pk += 0x14;
                    }
                }
                i++;
                op++;
            } while (i < n);
        }
    }
    return pk;
}
