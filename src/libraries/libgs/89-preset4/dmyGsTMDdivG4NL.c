#include "common.h"
#include <stdio.h>

extern s32 D_00002548;
extern char RO_STR_00001ED8[];

PACKET *dmyGsTMDdivG4NL(TMD_P_F4 *op, VERT *vp, VERT *np, PACKET *pk,
                        int n, int shift, GsOT *ot, u_long *scratch) {
    if (D_00002548 == 0) {
        printf(RO_STR_00001ED8 + 556);
        D_00002548 = 1;
    }
    return pk;
}
