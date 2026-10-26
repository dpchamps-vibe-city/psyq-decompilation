#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <inline_c.h>
#include <libgpu.h>
#include <libgs.h>

PACKET *GsTMDfastG3M(TMD_P_G3 *op, VERT *vp, VERT *np, PACKET *pk, int n,
                     int shift, GsOT *ot, u_long *scratch)
{
    GsADIV_G3 *s;
    u_long *flg;
    long *otz;
    u_long flgmask;
    u_long tagmask;
    u_long packetlen;
    int i, j;
    int mate;

    mate = GsMATE_C;
    s = (GsADIV_G3 *)scratch;
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
            packetlen = 0x06000000;
            do {
                gte_ldv3(&vp[op->v0], &vp[op->v1], &vp[op->v2]);
                gte_rtpt();
                gte_stflg(flg);
                if (!(s->flg & flgmask)) {
                    gte_nclip();
                    gte_stopz(otz);
                    if (s->otz > 0) {
                        gte_stsxy3_g3(pk);
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
                        gte_ldv0(&np[op->n1]);
                        gte_ll();
                        for (j = 0; j < mate; j++) {
                            gte_sqr12();
                        }
                        gte_cc();
                        gte_strgb(pk + 0xC);
                        gte_ldv0(&np[op->n2]);
                        gte_ll();
                        for (j = 0; j < mate; j++) {
                            gte_sqr12();
                        }
                        gte_cc();
                        gte_strgb(pk + 0x14);
                        s->tag = &s->org[s->otz >> s->shift];
                        *(u_long *)pk = (*s->tag & tagmask) | packetlen;
                        *s->tag = (u_long)pk & tagmask;
                        pk += 0x1C;
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
            packetlen = 0x06000000;
            do {
                gte_ldv3(&vp[op->v0], &vp[op->v1], &vp[op->v2]);
                gte_rtpt();
                gte_stflg(flg);
                if (!(s->flg & flgmask)) {
                    gte_nclip();
                    gte_stopz(otz);
                    if (s->otz > 0) {
                        gte_stsxy3_g3(pk);
                        gte_avsz3();
                        gte_stotz(otz);
                        gte_ldrgb(&op->r0);
                        gte_ldv3(&np[op->n0], &np[op->n1], &np[op->n2]);
                        gte_ncct();
                        s->tag = &s->org[s->otz >> s->shift];
                        *(u_long *)pk = (*s->tag & tagmask) | packetlen;
                        *s->tag = (u_long)pk & tagmask;
                        gte_strgb3_g3(pk);
                        pk += 0x1C;
                    }
                }
                i++;
                op++;
            } while (i < n);
        }
    }
    return pk;
}
