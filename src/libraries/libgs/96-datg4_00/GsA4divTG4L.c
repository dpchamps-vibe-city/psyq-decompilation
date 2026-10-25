INCLUDE_ASM("build/libraries/nonmatchings/libgs_96", GsA4divTG4L);


/* PARKED by /auto_decompilation_loop on 2026-10-25T15:49:42.990Z.
 * Reason: asm-needs-human-approval.
 * Escalation reached: deepseek-v4-1-flash-1017.
 * The best non-matching attempt is preserved verbatim below, disabled.
 * Findings and the decision needed: notes/human-needed-approvals/libgs_96::GsA4divTG4L.md
 */

#if 0
/* Best non-matching attempt, preserved for the next session. */
#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <inline_c.h>
#include <libgpu.h>
#include <libgs.h>
/* Original libgs GTE words use the cop2op encoding (include/gte_macros.inc,
   matches original object bytes). */
#undef gte_rtpt
#undef gte_nclip
#undef gte_rtps
#undef gte_avsz4
#undef gte_ncct
#undef gte_nccs
#define gte_rtpt()    __asm__ volatile ("nop;nop;.word 0x4A280030")
#define gte_nclip()    __asm__ volatile ("nop;nop;.word 0x4B400006")
#define gte_rtps()    __asm__ volatile ("nop;nop;.word 0x4A180001")
#define gte_avsz4()    __asm__ volatile ("nop;nop;.word 0x4B68002E")
#define gte_ncct()    __asm__ volatile ("nop;nop;.word 0x4B18043F")
#define gte_nccs()    __asm__ volatile ("nop;nop;.word 0x4B08041B")


void func_00000560(u32 *arg0, u32 *arg1, s32 arg2, u8 *arg3);

PACKET *GsA4divTG4L(TMD_P_TG4 *op, VERT *vp, VERT *np, PACKET *pk, int n, int shift, GsOT *ot, u_long *scratch)
{
    GsADIV_GT4 *s = (GsADIV_GT4 *)scratch;
    GsADIV_P_GT4 *p;
    TMD_P_TG4 *tp;
    PACKET *a;
    long t0, t1;
    int i;

    scratch += sizeof(GsADIV_GT4) / 4;
    p = (GsADIV_P_GT4 *)scratch;
    s->hwd0 = HWD0 / 2;
    s->adivh = GsADIVH;
    s->vwd0 = VWD0 / 2;
    s->adivw = GsADIVW;
    s->adivz = GsADIVZ;
    s->pk = (u_long *)pk;
    s->org = (u_long *)ot->org;
    s->shift = shift;
    s->si.r0 = 0x80;
    s->si.g0 = 0x80;
    s->si.b0 = 0x80;
    s->si.r1 = 0x80;
    s->si.g1 = 0x80;
    s->si.b1 = 0x80;
    s->si.r2 = 0x80;
    s->si.g2 = 0x80;
    s->si.b2 = 0x80;
    s->si.r3 = 0x80;
    s->si.g3 = 0x80;
    s->si.b3 = 0x80;
    s->si.code = op->cd;
    gte_SetRGBcd(&s->si.r0);
    a = (PACKET *)s->pk;
    tp = op;

    t1 = 0x40000;
    t0 = 0x80000000;
    for (i = 0; i < n; i++, tp++) {
            gte_ldv3(&vp[tp->v0], &vp[tp->v1], &vp[tp->v2]);
            gte_rtpt();
            (*(u32 *)(a + 0xC)) = (u32)(*(u32 *)&tp->tu0);
            (*(u32 *)(a + 0x24)) = (u32)(*(u32 *)&tp->tu2);
            gte_stflg(&s->flg0);
            gte_nclip();
            (*(u32 *)(a + 0x30)) = (u32)(*(u32 *)&tp->tu3);
            gte_stopz(&s->otz);
            if (s->otz > 0) {
                gte_stsxy3_gt4(a);
                gte_ldv0(&vp[tp->v3]);
                gte_rtps();
                gte_stflg(&s->flg);
                if ((s->flg & t1) == 0 || (s->flg0 & t1) == 0) {
                gte_stsxy(a + 0x2C);
                gte_avsz4();
                gte_stotz(&s->otz);
                gte_ldv3(&np[tp->n0], &np[tp->n1], &np[tp->n2]);
                gte_ncct();
                (*(u32 *)(a + 0x18)) = (u32)(*(u32 *)&tp->tu1);
                s->tag = &s->org[s->otz >> s->shift];
                gte_strgb3(a + 4, a + 0x10, a + 0x1C);
                gte_ldv0(&np[tp->n3]);
                gte_nccs();
                gte_strgb(a + 0x28);
                if (s->otz >= s->adivz && !(s->flg0 & t0) && !(s->flg & t0)) {
                    (*(u32 *)a) = (*s->tag & 0x00FFFFFF) | 0x0C000000;
                    *s->tag = (u32)a & 0x00FFFFFF;
                    a += 0x34;
                } else {
                    (*(VERT *)&p->vt[0].vx) = (*(VERT *)&vp[tp->v0].vx);
                    (*(u32 *)&p->vt[0].col) = (u32)(*(u32 *)(a + 4));
                    (*(VERT *)&p->vt[1].vx) = (*(VERT *)&vp[tp->v1].vx);
                    (*(u32 *)&p->vt[1].col) = (u32)(*(u32 *)(a + 0x10));
                    (*(VERT *)&p->vt[2].vx) = (*(VERT *)&vp[tp->v2].vx);
                    (*(u32 *)&p->vt[2].col) = (u32)(*(u32 *)(a + 0x1C));
                    (*(VERT *)&p->vt[3].vx) = (*(VERT *)&vp[tp->v3].vx);
                    (*(u32 *)&p->vt[3].col) = (u32)(*(u32 *)(a + 0x28));
                    *(u16 *)&p->vt[0].tu = *(u16 *)&tp->tu0;
                    *(u16 *)&p->vt[1].tu = *(u16 *)&tp->tu1;
                    *(u16 *)&p->vt[2].tu = *(u16 *)&tp->tu2;
                    *(u16 *)&p->vt[3].tu = *(u16 *)&tp->tu3;
                    s->si.clut = tp->clut;
                    s->si.tpage = tp->tpage;
                    s->pk = (u_long *)a;
                    func_00000560((u32 *)scratch, (u32 *)s, 0, (u8 *)a);
                    a = (PACKET *)s->pk;
                }
                }
            }
    }
    s->pk = (u_long *)a;
    return a;
}
#endif
