#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>
#include <libhmd.h>

int GsSetViewUnit(GsVIEWUNIT *pv) {
    MATRIX m;
    MATRIX lm;
    VECTOR v;

    GsWSMATRIX = pv->view;
    if (pv->super != NULL) {
        GsGetLwUnit(pv->super, &m);
        TransposeMatrix(&m, &lm);
        ApplyMatrixLV(&lm, (VECTOR *) m.t, &v);
        lm.t[0] = -v.vx;
        lm.t[1] = -v.vy;
        lm.t[2] = -v.vz;
        GsMulCoord2(&GsWSMATRIX, &lm);
        GsWSMATRIX = lm;
    }
    GsWSMATRIX_ORG = GsWSMATRIX;
    return 0;
}
