#include "common.h"
#include <stdio.h>

extern s32 D_00002538;
extern char RO_STR_00001ED8[];

PACKET *dmyGsPrstG4NL(TMD_P_F4 *op, VERT *vp, VERT *np, PACKET *pk,
                      int n, int shift, GsOT *ot, u_long *scratch) {
    if (D_00002538 == 0) {
        printf(RO_STR_00001ED8 + 508);
        D_00002538 = 1;
    }
    return pk;
}
