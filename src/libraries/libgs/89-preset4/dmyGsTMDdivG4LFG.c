#include "common.h"
#include <sys/types.h>
#include <stdio.h>
#include <libetc.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>

extern s32 D_0000254C;
extern char RO_STR_00001ED8[];

PACKET *dmyGsTMDdivG4LFG(TMD_P_F4 *op, VERT *vp, VERT *np, PACKET *pk,
                         int n, int shift, GsOT *ot, u_long *scratch) {
    if (D_0000254C == 0) {
        printf(RO_STR_00001ED8 + 568);
        D_0000254C = 1;
    }
    return pk;
}
