#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <inline_c.h>
#include <libgpu.h>
#include <libgs.h>

static void func_00000878(VERT *v0, VERT *v1, VERT *v2, GsADIV_F4 *s);
static s32 func_00000958(POLY_F4 *si, GsADIV_F4 *s);
static void func_00000B14(VERT *dst, VERT *a, VERT *b);

static void func_00000488(u_long *scratch, GsADIV_F4 *s, int level) {
    GsADIV_P_F4 *in;
    GsADIV_P_F4 *out;
    POLY_F4 *si;

    in = (GsADIV_P_F4 *)scratch;
    scratch += sizeof(GsADIV_P_F4) / 4;
    out = (GsADIV_P_F4 *)scratch;

    gte_ldv3(&in->vt[0], &in->vt[1], &in->vt[2]);
    gte_rtpt();
    si = &s->si;
    gte_stflg((u_long *)&s->flg);
    gte_stsxy3_f4(si);
    gte_ldv0(&in->vt[3]);
    gte_rtps();
    gte_stflg((u_long *)&s->flg0);
    gte_stsxy(&si->x3);
    gte_avsz4();
    s->flg |= s->flg0;
    gte_stszotz(&s->otz);

    if (func_00000958(si, s) != 0) {
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
    s->pk[1] = *(u_long *)&si->r0;
    s->pk[2] = *(u_long *)&si->x0;
    s->pk[3] = *(u_long *)&si->x1;
    s->pk[4] = *(u_long *)&si->x2;
    s->pk[5] = *(u_long *)&si->x3;
    s->tag = &s->org[(s32)s->otz >> s->shift];
    *s->pk = (*s->tag & 0x00FFFFFF) | 0x05000000;
    *s->tag = (u_long)s->pk & 0x00FFFFFF;
    s->pk += 6;
    return;

subdiv:
    level++;
    out->vt[0] = in->vt[0];
    func_00000B14(&out->vt[1], &in->vt[0], &in->vt[1]);
    func_00000B14(&out->vt[2], &in->vt[0], &in->vt[2]);
    func_00000B14(&out->vt[3], &in->vt[0], &in->vt[3]);
    func_00000878(&in->vt[0], &in->vt[1], &out->vt[1], s);
    func_00000488(scratch, s, level);

    out->vt[0] = in->vt[1];
    func_00000B14(&out->vt[2], &in->vt[1], &in->vt[3]);
    func_00000878(&in->vt[1], &in->vt[3], &out->vt[2], s);
    func_00000488(scratch, s, level);

    out->vt[0] = in->vt[3];
    func_00000B14(&out->vt[1], &in->vt[3], &in->vt[2]);
    func_00000878(&in->vt[3], &in->vt[2], &out->vt[1], s);
    func_00000488(scratch, s, level);

    out->vt[0] = in->vt[2];
    func_00000B14(&out->vt[2], &in->vt[0], &in->vt[2]);
    func_00000878(&in->vt[2], &in->vt[0], &out->vt[2], s);
    func_00000488(scratch, s, level);
}
