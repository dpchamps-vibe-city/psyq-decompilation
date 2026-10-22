#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>

extern s16 PSDGPU;
extern s16 PSDOFSX;
extern s16 PSDOFSY;

typedef struct {
    u_long tag;
    u_long tpage;
    u_long color;
    short x, y;
    u_char u, v;
    u_short cba;
} PKT20;

void GsInitFixBg16(GsBG *bg, u_long *work) {
    PKT20 *pk;
    u_long *p;
    u_long attribute;
    u_long color;
    s32 w, h;
    s32 i, j, k;
    s16 *ofsx;
    u_long *head;
    u_char hlen;
    u_long tpage;

    w = HWD0 / 16 + 1;
    h = VWD0 / 16 + 1;
    tpage = 0xE1000000;
    attribute = bg->attribute;
    color = 0x7D000000 + ((attribute >> 5) & 0x02000000);
    head = work + 2;
    work[0] = (u_long) head;
    work[1] = w * h * 5 * 4 + (u_long) work + 0x18;
    p = head;
    i = 0;
    hlen = 1;
    ofsx = &PSDOFSX;
    for (; i < 2; i++) {
        p[0] = (u_long) (p + 2);
        ((u_char *) p)[3] = hlen;
        p[1] = 0xE5000000;
        p += 2;
        for (j = 0; j < VWD0 + 0x10; j += 0x10) {
            for (k = 0; k < HWD0 + 0x10; k += 0x10) {
                pk = (PKT20 *) p;
                pk->tag = (u_long) (p + 5);
                ((u_char *) pk)[3] = 4;
                pk->tpage = tpage;
                pk->color = color;
                pk->x = k;
                pk->y = j + i * VWD0;
                p += 5;
            }
        }
        if (PSDGPU != 0) {
            p[1] = POSITION.offx + ofsx[i]
                 + ((POSITION.offy + (&PSDOFSY)[i]) << 0xB) + 0xE5000000;
        } else {
            p[1] = 0xE5000000;
        }
        p += 2;
    }
}
