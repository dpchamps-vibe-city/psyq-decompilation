#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>

extern GsCOORDINATE2 *DSTACK[2];

void GsGetLw(GsCOORDINATE2 *m, MATRIX *out) {
    GsCOORDINATE2 **dst;
    GsCOORDINATE2 *cur;
    GsCOORDINATE2 *top;
    int idx;
    int saved;

    cur = m;
    idx = 0;
    saved = 100;
    while (1) {
        DSTACK[idx] = cur;
        top = cur->super;
        if (top != NULL)
            goto get_nn;
        if (cur->flg == PSDCNT)
            goto set_flg;
        if (cur->flg != 0)
            goto get_saved;
set_flg:
        cur->workm = cur->coord;
        *out = cur->workm;
        cur->flg = PSDCNT;
        break;
get_saved:
        idx = saved + 1;
        if (saved == 100) {
            *out = DSTACK[0]->workm;
            idx = 0;
        } else {
            *out = DSTACK[idx]->workm;
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
        u_long b = (u_long)DSTACK - 4;
        u_long s = idx << 2;
        dst = (GsCOORDINATE2 **)(s + b);
        do {
            GsMulCoord3(out, &(*dst)->coord);
            idx--;
            (*dst)->workm = *out;
            (*dst)->flg = PSDCNT;
            dst--;
        } while (idx > 0);
    }
}
