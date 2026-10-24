#include "common.h"
#include <sys/types.h>
#include <stdio.h>
#include <libetc.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>

extern s32 D_000024D0;
extern char RO_STR_00001ED8[];

PACKET *dmyGsTMDdivG3L(TMD_P_F3 *op, VERT *vp, VERT *np, PACKET *pk) {
    if (D_000024D0 == 0) {
        printf(RO_STR_00001ED8 + 176);
        D_000024D0 = 1;
    }
    return pk;
}
