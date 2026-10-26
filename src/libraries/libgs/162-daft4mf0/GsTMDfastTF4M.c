#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <inline_c.h>
#include <libgpu.h>
#include <libgs.h>

PACKET *GsTMDfastTF4M(TMD_P_TF4 *op, VERT *vp, VERT *np, PACKET *pk, int n,
                       int shift, GsOT *ot, u_long *scratch)
{
    GsADIV_FT3 *s;
    POLY_FT4 *p;
    u_long *flg;
    long *otz;
    u_long flgmask;
    u_long tagmask;
    u_long packetlen;
    int i, j;
    int mate;

    mate = GsMATE_C;
    s = (GsADIV_FT3 *)scratch;
    s->org = (u_long *)ot->org;
    s->shift = shift;
    setPolyFT4((POLY_FT4 *)pk);
    setRGB0((POLY_FT4 *)pk, 0x80, 0x80, 0x80);
    gte_ldrgb(&((POLY_FT4 *)pk)->r0);
    if ((GsLIGNR == 0 && GsLIGHT_MODE == 2) ||
        (GsLIGNR == 1 && GsLMODE == 2)) {
        p = (POLY_FT4 *)pk;
        i = 0;
        if (i < n) {
            flg = (u_long *)&s->flg;
            flgmask = 0x80000000;
            otz = &s->otz;
            tagmask = 0x00FFFFFF;
            packetlen = 0x09000000;
            do {
                gte_ldv3(&vp[op->v0], &vp[op->v1], &vp[op->v2]);
                gte_rtpt();
                *(u_long *)&p->u0 = *(u_long *)&op->tu0;
                *(u_long *)&p->u1 = *(u_long *)&op->tu1;
                gte_stflg(flg);
                if (!(s->flg & flgmask)) {
                    gte_nclip();
                    *(u_long *)&p->u2 = *(u_long *)&op->tu2;
                    gte_stopz(otz);
                    if (s->otz > 0) {
                        gte_stsxy3_ft4(pk);
                        gte_ldv0(&vp[op->v3]);
                        gte_rtps();
                        *(u_long *)&p->u3 = *(u_long *)&op->tu3;
                        gte_stflg(flg);
                        if (!(s->flg & flgmask)) {
                            gte_stsxy(pk + 0x20);
                            gte_avsz4();
                            gte_stotz(otz);
                            gte_ldv0(&np[op->n0]);
                            gte_ll();
                            for (j = 0; j < mate; j++) {
                                gte_sqr12();
                            }
                            gte_cc();
                            gte_strgb(&p->r0);
                            s->tag = &s->org[s->otz >> s->shift];
                            *(u_long *)pk = (*s->tag & tagmask) | packetlen;
                            *s->tag = (u_long)pk & tagmask;
                            p++;
                            pk += 0x28;
                        }
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

        p = (POLY_FT4 *)pk;
        i = 0;
        if (i < n) {
            flg = (u_long *)&s->flg;
            flgmask = 0x80000000;
            otz = &s->otz;
            tagmask = 0x00FFFFFF;
            packetlen = 0x09000000;
            do {
                gte_ldv3(&vp[op->v0], &vp[op->v1], &vp[op->v2]);
                gte_rtpt();
                *(u_long *)&p->u0 = *(u_long *)&op->tu0;
                *(u_long *)&p->u1 = *(u_long *)&op->tu1;
                gte_stflg(flg);
                if (!(s->flg & flgmask)) {
                    gte_nclip();
                    *(u_long *)&p->u2 = *(u_long *)&op->tu2;
                    gte_stopz(otz);
                    if (s->otz > 0) {
                        gte_stsxy3_ft4(pk);
                        gte_ldv0(&vp[op->v3]);
                        gte_rtps();
                        *(u_long *)&p->u3 = *(u_long *)&op->tu3;
                        gte_stflg(flg);
                        if (!(s->flg & flgmask)) {
                            gte_stsxy(pk + 0x20);
                            gte_avsz4();
                            gte_stotz(otz);
                            gte_ldv0(&np[op->n0]);
                            gte_nccs();
                            s->tag = &s->org[s->otz >> s->shift];
                            *(u_long *)pk = (*s->tag & tagmask) | packetlen;
                            *s->tag = (u_long)pk & tagmask;
                            gte_strgb(&p->r0);
                            p++;
                            pk += 0x28;
                        }
                    }
                }
                i++;
                op++;
            } while (i < n);
        }
    }
    return pk;
}
