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
    short w, h;
    u_long tex;
} PKT24;

void GsInitFixBg32(GsBG *bg, u_long *work) {
    PKT24 *pk;
    u_long *p;
    u_long attribute;
    u_long color;
    s32 i, j, k;
    s32 ofs;
    u_long *head;
    u_char hlen;
    u_long tpage;

    attribute = bg->attribute;
    tpage = 0xE1000000;
    color = 0x65000000 + ((attribute >> 5) & 0x02000000);
    head = work + 2;
    p = head;
    i = 0;
    hlen = 1;
    for (; i < 2; i++) {
        work[i] = (u_long) p;
        p[0] = (u_long) (p + 2);
        ((u_char *) p)[3] = hlen;
        p[1] = 0xE5000000;
        p += 2;
        for (j = 0; j < VWD0 + 0x20; j += 0x20) {
            for (k = 0; k < HWD0 + 0x20; k += 0x20) {
                pk = (PKT24 *) p;
                pk->tag = (u_long) (p + 6);
                ((u_char *) pk)[3] = 5;
                pk->tpage = tpage;
                pk->color = color;
                pk->x = k;
                pk->y = j + i * VWD0;
                pk->tex = 0x200020;
                p += 6;
            }
        }
        ofs = i * 2;
        if (PSDGPU != 0) {
            p[1] = POSITION.offx + *((s16 *) ((u8 *) &PSDOFSX + ofs))
                 + ((POSITION.offy + *((s16 *) ((u8 *) &PSDOFSY + ofs))) << 0xB) + 0xE5000000;
        } else {
            p[1] = 0xE5000000;
        }
        p += 2;
    }
}
