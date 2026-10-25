#include "common.h"
#include <sys/types.h>
#include <stdio.h>
#include <libetc.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>

extern s32 D_000025E0;
extern char RO_STR_00001ED8[];

PACKET *dmyGsTMDfastF4L(TMD_P_F4 *op, VERT *vp, VERT *np, PACKET *pk,
                        int n, int shift, GsOT *ot, u_long *scratch) {
    if (D_000025E0 == 0) {
        printf(RO_STR_00001ED8 + 1088);
        D_000025E0 = 1;
    }
    return pk;
}
