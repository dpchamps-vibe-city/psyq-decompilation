#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>
#include <libhmd.h>

extern GsCOORDUNIT *USTACK[2];

void GsGetLwUnit(GsCOORDUNIT *m, MATRIX *out) {
    GsCOORDUNIT **usp;
    GsCOORDUNIT *cur;
    GsCOORDUNIT *top;
    int idx;
    int saved;

    cur = m;
    idx = 0;
    saved = 100;
    while (1) {
        USTACK[idx] = cur;
        top = cur->super;
        if (top != NULL)
            goto get_nn;
        if (cur->flg == PSDCNT)
            goto set_flg;
        if (cur->flg != 0)
            goto get_saved;
set_flg:
        cur->workm = cur->matrix;
        *out = cur->workm;
        cur->flg = PSDCNT;
        break;
get_saved:
        idx = saved + 1;
        if (saved == 100) {
            *out = USTACK[0]->workm;
            idx = 0;
        } else {
            *out = USTACK[idx]->workm;
        }
        break;
get_nn:
        if (cur->flg != PSDCNT)
            goto walk;
        *out = cur->workm;
        break;
walk:
        if (cur->flg == 0)
            saved = idx;
        cur = top;
        idx++;
    }
    if (idx > 0) {
        u_long b = (u_long)USTACK - 4;
        u_long s = idx << 2;
        usp = (GsCOORDUNIT **)(s + b);
        do {
            GsMulCoord3(out, &(*usp)->matrix);
            idx--;
            (*usp)->workm = *out;
            (*usp)->flg = PSDCNT;
            usp--;
        } while (idx > 0);
    }
}
