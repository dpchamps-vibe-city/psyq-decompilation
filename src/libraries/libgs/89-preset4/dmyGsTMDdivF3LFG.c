#include "common.h"
#include <stdio.h>

extern s32 D_000024AC;
extern char RO_STR_00001ED8[];

PACKET *dmyGsTMDdivF3LFG(TMD_P_F3 *op, VERT *vp, VERT *np, PACKET *pk,
                         int n, int shift, GsOT *ot, u_long *scratch) {
    if (D_000024AC == 0) {
        printf(RO_STR_00001ED8 + 60);
        D_000024AC = 1;
    }
    return pk;
}
