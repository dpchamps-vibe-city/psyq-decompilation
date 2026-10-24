#include "common.h"
#include <sys/types.h>
#include <stdio.h>
#include <libetc.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>

extern s32 D_000024E4;
extern char RO_STR_00001FC4[];

PACKET *dmyGsPrstTNF3(TMD_P_F3 *op, VERT *vp, VERT *np, PACKET *pk,
                      int n, int shift, GsOT *ot, u_long *scratch) {
    if (D_000024E4 == 0) {
        printf(RO_STR_00001FC4);
        D_000024E4 = 1;
    }
    return pk;
}
