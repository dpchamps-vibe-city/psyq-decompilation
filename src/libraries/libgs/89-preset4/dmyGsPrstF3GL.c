#include "common.h"
#include <sys/types.h>
#include <stdio.h>
#include <libetc.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>

extern s32 D_00002630;
extern char RO_STR_00001ED8[];

PACKET *dmyGsPrstF3GL(TMD_P_F3 *op, VERT *vp, VERT *np, PACKET *pk,
                      int n, int shift, GsOT *ot, u_long *scratch) {
    if (D_00002630 == 0) {
        printf(RO_STR_00001ED8 + 1392);
        D_00002630 = 1;
    }
    return pk;
}
