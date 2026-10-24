#include "common.h"
#include <stdio.h>

extern s32 D_000024D4;
extern char RO_STR_00001ED8[];

PACKET *dmyGsTMDdivNG3(TMD_P_F3 *op, VERT *vp, VERT *np, PACKET *pk,
                       int n, int shift, GsOT *ot, u_long *scratch) {
    if (D_000024D4 == 0) {
        printf(RO_STR_00001ED8 + 188);
        D_000024D4 = 1;
    }
    return (PACKET *)np;
}
