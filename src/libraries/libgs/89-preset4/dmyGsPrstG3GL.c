#include "common.h"
#include <sys/types.h>
#include <stdio.h>
#include <libetc.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>

extern s32 D_0000263C;
extern char RO_STR_00001ED8[];

PACKET *dmyGsPrstG3GL(TMD_P_F3 *op, VERT *vp, VERT *np, PACKET *pk) {
    if (D_0000263C == 0) {
        printf(RO_STR_00001ED8 + 1428);
        D_0000263C = 1;
    }
    return pk;
}
