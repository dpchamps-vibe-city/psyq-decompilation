#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <inline_c.h>
#include <libgpu.h>
#include <libgs.h>

PACKET *GsTMDfastTF3MFG(TMD_P_TF3 *op, VERT *vp, VERT *np, PACKET *pk, int n,
                       int shift, GsOT *ot, u_long *scratch)
{
    GsADIV_FT3 *s;
    POLY_FT3 *p;
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
    p = (POLY_FT3 *)pk;
    setPolyFT3(p);
    setRGB0(p, 0x80, 0x80, 0x80);
    gte_ldrgb(&p->r0);
    if ((GsLIGNR == 0 && GsLIGHT_MODE == 3) ||
        (GsLIGNR == 1 && GsLMODE == 3)) {
        i = 0;
        if (i < n) {
            flg = (u_long *)&s->flg;
            flgmask = 0x80000000;
            otz = &s->otz;
            tagmask = 0x00FFFFFF;
            packetlen = 0x07000000;
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
                        gte_stsxy3_ft3(p);
                        gte_avsz3();
                        gte_stotz(otz);
                        gte_ldv0(&np[op->n0]);
                        gte_ll();
                        for (j = 0; j < mate; j++) {
                            gte_sqr12();
                        }
                        gte_cdp();
                        gte_strgb(&p->r0);
                        s->tag = &s->org[s->otz >> s->shift];
                        *(u_long *)p = (*s->tag & tagmask) | packetlen;
                        *s->tag = (u_long)p & tagmask;
                        p++;
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
            packetlen = 0x07000000;
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
                        gte_stsxy3_ft3(p);
                        gte_avsz3();
                        gte_stotz(otz);
                        gte_ldv0(&np[op->n0]);
                        gte_ncds();
                        s->tag = &s->org[s->otz >> s->shift];
                        *(u_long *)p = (*s->tag & tagmask) | packetlen;
                        *s->tag = (u_long)p & tagmask;
                        gte_strgb(&p->r0);
                        p++;
                    }
                }
                i++;
                op++;
            } while (i < n);
        }
    }
    return (PACKET *)p;
}
