#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>
#include <libhmd.h>

void gte_rotate_z_matrix(MATRIX *arg0, s32 arg1);
void Gssub_make_matrix(MATRIX *out, s16 x, s16 y, s32 mode);

int GsSetRefViewLUnit(GsRVIEWUNIT *pv) {
    GsRVIEWUNIT lv;
    MATRIX lm;
    MATRIX m;
    MATRIX lvo;
    VECTOR v;
    s32 r3;
    s32 r2;
    s16 q1;
    s16 q2;
    s32 h2;
    s16 q3;
    s16 q4;
    s32 n;
    s32 s2;

    GsWSMATRIX = GsIDMATRIX2;
    gte_rotate_z_matrix(&GsWSMATRIX, -pv->rz);
    r3 = (pv->vrx - pv->vpx) * (pv->vrx - pv->vpx) +
         (pv->vry - pv->vpy) * (pv->vry - pv->vpy) +
         (pv->vrz - pv->vpz) * (pv->vrz - pv->vpz);
    if (r3 == 0)
        return 1;
    r2 = pv->vpy - pv->vry;
    h2 = r2 * r2;
    n = 0xC - Lzc(h2);
    if (n < 0) {
        q1 = (s32) -((pv->vpy - pv->vry) << 0xC) / SquareRoot0(r3);
    } else if (pv->vpy - pv->vry >= 0) {
        q1 = (s32) -csqrt((s32) ((u32) (h2 << (0xC - n)) / (u32) ((u32) r3 >> n)));
    } else {
        q1 = csqrt((s32) ((u32) (h2 << (0xC - n)) / (u32) ((u32) r3 >> n)));
    }
    h2 = (pv->vrx - pv->vpx) * (pv->vrx - pv->vpx) +
         (pv->vrz - pv->vpz) * (pv->vrz - pv->vpz);
    n = 0xC - Lzc(h2);
    if (n < 0) {
        s2 = SquareRoot0(h2);
        q2 = (s32) (s2 << 0xC) / SquareRoot0(r3);
    } else {
        q2 = csqrt((s32) ((u32) (h2 << (0xC - n)) / (u32) ((u32) r3 >> n)));
    }
    Gssub_make_matrix(&lm, q1, q2, 0x78);
    MulMatrix(&GsWSMATRIX, &lm);
    if (h2 != 0) {
        r3 = h2;
        h2 = (pv->vrx - pv->vpx) * (pv->vrx - pv->vpx);
        n = 0xC - Lzc(h2);
        if (n < 0) {
            q3 = (s32) -((pv->vrx - pv->vpx) << 0xC) / SquareRoot0(r3);
        } else if (pv->vrx - pv->vpx >= 0) {
            q3 = (s32) -csqrt((s32) ((u32) (h2 << (0xC - n)) / (u32) ((u32) r3 >> n)));
        } else {
            q3 = csqrt((s32) ((u32) (h2 << (0xC - n)) / (u32) ((u32) r3 >> n)));
        }
        h2 = (pv->vrz - pv->vpz) * (pv->vrz - pv->vpz);
        n = 0xC - Lzc(h2);
        if (n < 0) {
            q4 = (s32) ((pv->vrz - pv->vpz) << 0xC) / SquareRoot0(r3);
        } else if (pv->vrz - pv->vpz >= 0) {
            q4 = csqrt((s32) ((u32) (h2 << (0xC - n)) / (u32) ((u32) r3 >> n)));
        } else {
            q4 = (s32) -csqrt((s32) ((u32) (h2 << (0xC - n)) / (u32) ((u32) r3 >> n)));
        }
        Gssub_make_matrix(&lm, q3, q4, 0x79);
        MulMatrix(&GsWSMATRIX, &lm);
    }
    v.vx = -pv->vpx;
    v.vy = -pv->vpy;
    v.vz = -pv->vpz;
    ApplyMatrixLV(&GsWSMATRIX, &v, (VECTOR *) GsWSMATRIX.t);
    if (pv->super != NULL) {
        GsGetLwUnit(pv->super, &lm);
        TransposeMatrix(&lm, &m);
        ApplyMatrixLV(&m, (VECTOR *) lm.t, &v);
        m.t[0] = -v.vx;
        m.t[1] = -v.vy;
        m.t[2] = -v.vz;
        GsMulCoord2(&GsWSMATRIX, &m);
        GsWSMATRIX = m;
    }
    GsWSMATRIX_ORG = GsWSMATRIX;
    return 0;
}
