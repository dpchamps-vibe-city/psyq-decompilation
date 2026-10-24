#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>

static void func_00000520(MATRIX *mp);
static void func_00000584(MATRIX *mp);

int GsSetFlatLight(int id, GsF_LIGHT *lt) {
    MATRIX lm;
    MATRIX m;
    int r;
    int g;
    int b;
    int len;

    r = lt->r;
    g = lt->g;
    b = lt->b;
    lm = GsLIGHTWSMATRIX;
    func_00000584(&m);
    len = SquareRoot0(lt->vx * lt->vx + lt->vy * lt->vy + lt->vz * lt->vz);
    if (len == 0)
        return -1;
    switch (id) {
    case 0:
        lm.m[0][0] = (-lt->vx << 12) / len;
        lm.m[0][1] = (-lt->vy << 12) / len;
        lm.m[0][2] = (-lt->vz << 12) / len;
        m.m[0][0] = (r << 12) / 255;
        m.m[1][0] = (g << 12) / 255;
        m.m[2][0] = (b << 12) / 255;
        break;
    case 1:
        lm.m[1][0] = (-lt->vx << 12) / len;
        lm.m[1][1] = (-lt->vy << 12) / len;
        lm.m[1][2] = (-lt->vz << 12) / len;
        m.m[0][1] = (r << 12) / 255;
        m.m[1][1] = (g << 12) / 255;
        m.m[2][1] = (b << 12) / 255;
        break;
    case 2:
        lm.m[2][0] = (-lt->vx << 12) / len;
        lm.m[2][1] = (-lt->vy << 12) / len;
        lm.m[2][2] = (-lt->vz << 12) / len;
        m.m[0][2] = (r << 12) / 255;
        m.m[1][2] = (g << 12) / 255;
        m.m[2][2] = (b << 12) / 255;
        break;
    }
    GsLIGHTWSMATRIX = lm;
    func_00000520(&m);
    return 0;
}
