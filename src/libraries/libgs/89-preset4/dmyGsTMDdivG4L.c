#include "common.h"
#include <stdio.h>
#include <libetc.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>

extern s32 D_00002550;
extern char RO_STR_00001ED8[];

PACKET *dmyGsTMDdivG4L(TMD_P_F4 *op, VERT *vp, VERT *np, PACKET *pk) {
    if (D_00002550 == 0) {
        printf(RO_STR_00001ED8 + 584);
        D_00002550 = 1;
    }
    return pk;
}
