#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>

void gte_rotate_z_matrix(MATRIX *arg0, s32 arg1);
void Gssub_make_matrix(MATRIX *out, s16 x, s16 y, s32 mode);
static void func_00000438(GsRVIEW2 *arg0, GsRVIEW2 *arg1);

int GsSetRefView2(GsRVIEW2 *pv) {
    GsRVIEW2 lv;
    MATRIX lm;
    MATRIX m;
    MATRIX lvo;
    VECTOR v;
    s32 r3;
    s32 r2;
    s32 q1;
    s32 q2;
    s32 h2;
    s32 q3;
    s32 q4;

    GsWSMATRIX = GsIDMATRIX2;
    gte_rotate_z_matrix(&GsWSMATRIX, -pv->rz);
    func_00000438(pv, &lv);
    r3 = SquareRoot0((lv.vrx - lv.vpx) * (lv.vrx - lv.vpx) +
                     (lv.vry - lv.vpy) * (lv.vry - lv.vpy) +
                     (lv.vrz - lv.vpz) * (lv.vrz - lv.vpz));
    if (r3 == 0)
        return 1;
    r2 = lv.vpy - lv.vry;
    q1 = (r2 << 12) / r3;
    h2 = (lv.vrx - lv.vpx) * (lv.vrx - lv.vpx) +
         (lv.vrz - lv.vpz) * (lv.vrz - lv.vpz);
    q1 = -q1;
    r2 = SquareRoot0(h2);
    q2 = (r2 << 12) / r3;
    Gssub_make_matrix(&lm, q1, q2, 0x78);
    MulMatrix(&GsWSMATRIX, &lm);
    if (r2 != 0) {
        r3 = r2;
        r2 = lv.vrx - lv.vpx;
        q3 = (r2 << 12) / r3;
        r2 = lv.vrz - lv.vpz;
        q4 = (r2 << 12) / r3;
        Gssub_make_matrix(&lm, -q3, q4, 0x79);
        MulMatrix(&GsWSMATRIX, &lm);
    }
    v.vx = -pv->vpx;
    v.vy = -pv->vpy;
    v.vz = -pv->vpz;
    ApplyMatrixLV(&GsWSMATRIX, &v, (VECTOR *) GsWSMATRIX.t);
    if (pv->super != NULL) {
        GsGetLw(pv->super, &lm);
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
