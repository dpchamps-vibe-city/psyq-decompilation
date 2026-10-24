#include "common.h"
#include <sys/types.h>
#include <stdio.h>
#include <libetc.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>

extern s32 D_000024C4;
extern char RO_STR_00001ED8[];

PACKET *dmyGsPrstNG3(TMD_P_F3 *op, VERT *vp, VERT *np, PACKET *pk) {
    if (D_000024C4 == 0) {
        printf(RO_STR_00001ED8 + 136);
        D_000024C4 = 1;
    }
    return pk;
}
