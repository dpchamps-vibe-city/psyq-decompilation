#include "common.h"
#include <sys/types.h>
#include <stdio.h>
#include <libetc.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>

extern s32 D_000024D8;
extern char RO_STR_00001FA0[];

PACKET *dmyGsPrstTF3NL(TMD_P_F3 *op, VERT *vp, VERT *np, PACKET *pk,
                       int n, int shift, GsOT *ot, u_long *scratch) {
    if (D_000024D8 == 0) {
        printf(RO_STR_00001FA0);
        D_000024D8 = 1;
    }
    return pk;
}
