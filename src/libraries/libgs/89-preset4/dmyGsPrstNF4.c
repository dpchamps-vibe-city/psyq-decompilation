#include "common.h"
#include <stdio.h>

extern s32 D_00002524;
extern char RO_STR_00001ED8[];

PACKET *dmyGsPrstNF4(TMD_P_F4 *op, VERT *vp, VERT *np, PACKET *pk,
                     int n, int shift, GsOT *ot, u_long *scratch) {
    if (D_00002524 == 0) {
        printf(RO_STR_00001ED8 + 444);
        D_00002524 = 1;
    }
    return pk;
}
