#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>
#include <libhmd.h>

void GsMapUnit(u_long *p) {
    u_long *base;
    u_long *hp;
    u_long *tp;
    s32 i;
    s32 j;
    s32 n;
    s32 m;

    base = p;
    p++;
    if (!(*p & 1)) {
        *p |= 1;
        p++;
        tp = base + *p;
        *p = (u_long) tp;
        hp = tp;
        n = *hp++;
        for (i = 0; i < n; i++) {
            m = *hp++;
            for (j = 0; j < m; j++, hp++) {
                if ((s32) *hp < 0)
                    *hp = (u_long) (base + (*hp & 0x7fffffff));
            }
        }
        p++;
        n = *p++;
        for (i = 0; i < n; i++, p++) {
            if (*p != 0) {
                tp = base + *p;
                *p = (u_long) tp;
                hp = tp;
                while (*hp != (u_long) -1) {
                    if (!(hp[2] & 0x80000000))
                        break;
                    hp[0] = (u_long) (base + hp[0]);
                    hp[1] = (u_long) (base + hp[1]);
                    hp[2] &= 0x7fffffff;
                    hp = (u_long *) hp[0];
                }
                if (hp[2] & 0x80000000) {
                    hp[1] = (u_long) (base + hp[1]);
                    hp[2] &= 0x7fffffff;
                }
            }
        }
    }
}
