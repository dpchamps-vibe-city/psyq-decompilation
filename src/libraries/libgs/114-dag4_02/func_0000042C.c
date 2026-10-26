#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <inline_c.h>
#include <libgpu.h>
#include <libgs.h>

static void func_0000088C(VERTC *v0, VERTC *v1, VERTC *v2, GsADIV_G4 *s);
static s32 func_0000099C(POLY_G4 *si, GsADIV_G4 *s);
static void func_00000B58(VERTC *dst, VERTC *a, VERTC *b);

static void func_0000042C(GsADIV_P_G4 *p, GsADIV_G4 *s, int level) {
    GsADIV_P_G4 *input;
    GsADIV_P_G4 *q;
    POLY_G4 *si;

    input = p;
    q = ++p;

    gte_ldv3(&input->vt[0], &input->vt[1], &input->vt[2]);
    gte_rtpt();
    si = &s->si;
    gte_stflg((u_long *)&s->flg);
    gte_stsxy3_g4(si);
    gte_ldv0(&input->vt[3]);
    gte_rtps();
    gte_stflg((u_long *)&s->flg0);
    gte_stsxy(&si->x3);
    gte_avsz4();
    s->flg |= s->flg0;
    gte_stszotz(&s->otz);

    if (func_0000099C(si, s) != 0) {
        return;
    }

    if (s->limit == level) {
        if (s->flg & 0x7F85E000) {
            return;
        }
    } else if (s->flg < 0
               || (s->maxx - s->minx) >= s->adivw
               || (s->maxy - s->miny) >= s->adivh) {
        goto subdiv;
    }

    s->pk[0] = *(u_long *)&si->tag;
    s->pk[1] = *(u_long *)&input->vt[0].col;
    s->pk[2] = *(u_long *)&si->x0;
    s->pk[3] = *(u_long *)&input->vt[1].col;
    s->pk[4] = *(u_long *)&si->x1;
    s->pk[5] = *(u_long *)&input->vt[2].col;
    s->pk[6] = *(u_long *)&si->x2;
    s->pk[7] = *(u_long *)&input->vt[3].col;
    s->pk[8] = *(u_long *)&si->x3;
    s->tag = &s->org[(s32)s->otz >> s->shift];
    *s->pk = (*s->tag & 0x00FFFFFF) | 0x08000000;
    *s->tag = (u_long)s->pk & 0x00FFFFFF;
    s->pk += 9;
    return;

subdiv:
    level++;
    q->vt[0] = input->vt[0];
    func_00000B58(&q->vt[1], &input->vt[0], &input->vt[1]);
    func_00000B58(&q->vt[2], &input->vt[0], &input->vt[2]);
    func_00000B58(&q->vt[3], &input->vt[0], &input->vt[3]);
    func_0000088C((VERTC *)input, &input->vt[1], &q->vt[1], s);
    func_0000042C(p, s, level);

    q->vt[0] = input->vt[1];
    func_00000B58(&q->vt[2], &input->vt[1], &input->vt[3]);
    func_0000088C(&input->vt[1], &input->vt[3], &q->vt[2], s);
    func_0000042C(p, s, level);

    q->vt[0] = input->vt[3];
    func_00000B58(&q->vt[1], &input->vt[3], &input->vt[2]);
    func_0000088C(&input->vt[3], &input->vt[2], &q->vt[1], s);
    func_0000042C(p, s, level);

    q->vt[0] = input->vt[2];
    func_00000B58(&q->vt[2], &input->vt[0], &input->vt[2]);
    func_0000088C(&input->vt[2], (VERTC *)input, &q->vt[2], s);
    func_0000042C(p, s, level);
}
