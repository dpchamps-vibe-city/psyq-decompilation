#include "common.h"
#include <sys/types.h>
#include <stdio.h>
#include <libetc.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>

extern s32 D_000024A0;
extern char RO_STR_00001ED8[];

PACKET *dmyGsPrstF3L(TMD_P_F3 *op, VERT *vp, VERT *np, PACKET *pk,
                     int n, int shift, GsOT *ot, u_long *scratch) {
    if (D_000024A0 == 0) {
        printf(RO_STR_00001ED8 + 24);
        D_000024A0 = 1;
    }
    return pk;
}
