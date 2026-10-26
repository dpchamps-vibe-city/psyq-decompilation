#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>
#include <libhmd.h>

/* Camera primitive layout from the retained 07020100.C. */
typedef struct {
    long proj;
    long rot;
    long vpx, vpy, vpz;
    long vrx, vry, vrz;
} HMD_P_CAMERA;

void gte_rotate_z_matrix(MATRIX *, long);
void Gssub_make_matrix(MATRIX *, short, short, int);
static void func_00000438(HMD_P_CAMERA *, GsRVIEWUNIT *);

u_long *GsU_07020100(GsARGUNIT *sp)
{
    GsARGUNIT_CAMERA *ap = (GsARGUNIT_CAMERA *)sp;
    HMD_P_CAMERA *cp = (HMD_P_CAMERA *)ap->cparam;
    GsRVIEWUNIT view2;
    long x0, y0, z0;
    short rx, ry;
    MATRIX mat, mat2, mat3;
    short sx, sy, cx, cy;
    VECTOR tmp;
    int f1, f2;
    int i, j;

    GsWSMATRIX = GsIDMATRIX2;
    gte_rotate_z_matrix(&GsWSMATRIX, -cp->vrz);
    func_00000438(cp, &view2);
    f1 = SquareRoot0((view2.vrx - view2.vpx) * (view2.vrx - view2.vpx) +
                     (view2.vry - view2.vpy) * (view2.vry - view2.vpy) +
                     (view2.vrz - view2.vpz) * (view2.vrz - view2.vpz));
    if (f1 == 0)
        goto END;
    f2 = view2.vpy - view2.vry;
    sx = -(f2 * ONE / f1);
    f2 = SquareRoot0((view2.vrx - view2.vpx) * (view2.vrx - view2.vpx) +
                     (view2.vrz - view2.vpz) * (view2.vrz - view2.vpz));
    cx = f2 * ONE / f1;
    Gssub_make_matrix(&mat, sx, cx, 'x');
    MulMatrix(&GsWSMATRIX, &mat);
    if (f2 != 0) {
        f1 = f2;
        f2 = view2.vrx - view2.vpx;
        sy = -(f2 * 4096 / f1);
        f2 = view2.vrz - view2.vpz;
        cy = f2 * ONE / f1;
        Gssub_make_matrix(&mat, sy, cy, 'y');
        MulMatrix(&GsWSMATRIX, &mat);
    }
    tmp.vx = -(long)cp->vpx;
    tmp.vy = -(long)cp->vpy;
    tmp.vz = -(long)cp->vpz;
    ApplyMatrixLV(&GsWSMATRIX, &tmp, (VECTOR *)&GsWSMATRIX.t[0]);
    GsGetLwUnit(ap->coord, &mat);
    TransposeMatrix(&mat, &mat2);
    ApplyMatrixLV(&mat2, (VECTOR *)&mat.t[0], &tmp);
    mat2.t[0] = -tmp.vx;
    mat2.t[1] = -tmp.vy;
    mat2.t[2] = -tmp.vz;
    GsMulCoord2(&GsWSMATRIX, &mat2);
    GsWSMATRIX = mat2;
    GsWSMATRIX_ORG = GsWSMATRIX;
END:
    return ap->primp + 1;
}
