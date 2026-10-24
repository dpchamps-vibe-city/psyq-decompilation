#include "common.h"
#include <sys/types.h>
#include <stdio.h>
#include <libetc.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>

extern s32 D_0000249C;
extern char RO_STR_00001ED8[];

PACKET *dmyGsPrstF3LFG(TMD_P_F3 *op, VERT *vp, VERT *np, PACKET *pk,
                       int n, int shift, GsOT *ot, u_long *scratch) {
    if (D_0000249C == 0) {
        printf(RO_STR_00001ED8 + 12);
        D_0000249C = 1;
    }
    return pk;
}
