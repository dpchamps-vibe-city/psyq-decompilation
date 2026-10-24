#include "common.h"
#include <sys/types.h>
#include <stdio.h>
#include <libetc.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>

extern s32 D_00002520;
extern char RO_STR_00001ED8[];

PACKET *dmyGsPrstF4L(TMD_P_F4 *op, VERT *vp, VERT *np, PACKET *pk,
                     int n, int shift, GsOT *ot, u_long *scratch) {
    if (D_00002520 == 0) {
        printf(RO_STR_00001ED8 + 432);
        D_00002520 = 1;
    }
    return pk;
}
