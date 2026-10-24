#include "common.h"
#include <stdio.h>

extern s32 D_0000252C;
extern char RO_STR_00001ED8[];

PACKET *dmyGsTMDdivF4LFG(TMD_P_F4 *op, VERT *vp, VERT *np, PACKET *pk,
                         int n, int shift, GsOT *ot, u_long *scratch) {
    if (D_0000252C == 0) {
        printf(RO_STR_00001ED8 + 468);
        D_0000252C = 1;
    }
    return pk;
}
