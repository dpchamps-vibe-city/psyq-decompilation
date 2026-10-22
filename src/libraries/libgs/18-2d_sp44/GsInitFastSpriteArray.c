#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>

typedef struct {
    u_long attribute;
    short x, y;
    u_long pk[2][3];
    u_long sp[2][5];
} GsFastSprite2;

void GsInitFastSpriteArray(GsFastSprite2 *sp, short n) {
    SPRT *q;
    u_long attr;
    u_long mask;
    u_long code1;
    u_long code2;
    int i;
    int opk;
    int osp;
    int otk;

    while (n-- > 0) {
        mask = 0xFFFFFF;
        code1 = 0x01000000;
        code2 = 0x04000000;
        attr = sp->attribute & 0x40;
        for (i = 0, otk = 0x50, osp = 0x20, opk = 8; i < 2; otk += 12, osp += 20, i++, opk += 12) {
            *(u_long *)((u_char *)sp + opk) = ((u_long)((u_char *)sp + osp) & mask) + code1;
            q = (SPRT *)((u_char *)sp + osp);
            q->tag = ((u_long)((u_char *)sp + otk) & mask) + code2;
            setlen(q, 4);
            setcode(q, 0x64);
            if (attr) {
                setcode(q, 0x65);
            }
        }
        sp++;
    }
}
