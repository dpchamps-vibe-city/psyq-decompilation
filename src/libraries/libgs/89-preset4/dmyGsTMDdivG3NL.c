#include "common.h"
#include <stdio.h>

extern s32 D_000024C8;
extern char RO_STR_00001ED8[];

PACKET *dmyGsTMDdivG3NL(TMD_P_F3 *op, VERT *vp, VERT *np, PACKET *pk,
                        int n, int shift, GsOT *ot, u_long *scratch) {
    if (D_000024C8 == 0) {
        printf(RO_STR_00001ED8 + 148);
        D_000024C8 = 1;
    }
    return pk;
}
