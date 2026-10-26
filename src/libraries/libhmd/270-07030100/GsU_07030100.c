#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>
#include <libhmd.h>

#define C_LIMIT 16

/* Camera primitive layout from the retained 07030100.C. */
typedef struct {
    long proj;
    long rot;
    long vpx, vpy, vpz;
    long vrx, vry, vrz;
} HMD_P_CAMERA;

void gte_rotate_z_matrix(MATRIX *, long);
void Gssub_make_matrix(MATRIX *, short, short, int);
static void func_000004D0(VECTOR *, VECTOR *, GsRVIEWUNIT *);

u_long *GsU_07030100(GsARGUNIT *sp)
{
    GsARGUNIT_CAMERA *ap = (GsARGUNIT_CAMERA *)sp;
    HMD_P_CAMERA *cp = (HMD_P_CAMERA *)ap->cparam;
    GsRVIEWUNIT view2;
    long x0, y0, z0;
    short rx, ry;
    MATRIX mat, mat2, mat3, mat4;
    short sx, sy, cx, cy;
    VECTOR tmp, tmp2;
    int f1, f2;
    int i, j;

    GsGetLwUnit((GsCOORDUNIT *)ap->coord, &mat4);
    GsGetLwUnit((GsCOORDUNIT *)ap->rcoord, &mat2);
    TransposeMatrix(&mat4, &mat3);
    ApplyMatrixLV(&mat2, (VECTOR *)&cp->vrx, &tmp);
    tmp.vx += mat2.t[0] - mat4.t[0];
    tmp.vy += mat2.t[1] - mat4.t[1];
    tmp.vz += mat2.t[2] - mat4.t[2];
    ApplyMatrixLV(&mat3, &tmp, &tmp2);
    GsWSMATRIX = GsIDMATRIX2;
    gte_rotate_z_matrix(&GsWSMATRIX, -cp->rot);
    func_000004D0((VECTOR *)&cp->vpx, &tmp2, &view2);
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
    if (f2 > C_LIMIT) {
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
    ApplyMatrixLV(&mat3, (VECTOR *)&mat4.t[0], &tmp);
    mat3.t[0] = -tmp.vx;
    mat3.t[1] = -tmp.vy;
    mat3.t[2] = -tmp.vz;
    GsMulCoord2(&GsWSMATRIX, &mat3);
    GsWSMATRIX = mat3;
    GsWSMATRIX_ORG = GsWSMATRIX;
END:
    return ap->primp + 1;
}
