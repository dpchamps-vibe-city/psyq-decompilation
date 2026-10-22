#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>

extern s16 PSDGPU;
extern s16 PSDOFSX;
extern s16 PSDOFSY;

void GsSortFixBg32(GsBG *bg, u_long *work, GsOT *otp, unsigned short pri) {
    GsCELL *base;
    GsCELL *cell;
    GsMAP *map;
    GsOT_TAG *tag;
    u16 *rowp;
    u_long *p0;
    u_long *p;
    u_long attribute;
    s32 scrollx, scrolly;
    s32 sx, sy;
    s32 wc, hc;
    s32 col, row;
    s32 startcol;
    s32 i, j;
    s32 index;
    s32 lo;
    s32 ncellw, ncellh;
    u16 cellidx;
    u16 tpage;

    attribute = bg->attribute;
    if ((s32) attribute < 0) {
        return;
    }
    wc = (HWD0 + 31) / 32 + 1;
    hc = (VWD0 + 31) / 32 + 1;
    tpage = (u16) (((attribute >> 17) & 0x180) | ((attribute >> 23) & 0x60));
    if (PSDIDX == 0) {
        p0 = (u_long *) work[1];
        p = p0;
    } else {
        p0 = (u_long *) work[0];
        p = p0;
    }
    scrollx = bg->scrollx;
    scrolly = bg->scrolly;
    sx = scrollx & ~0x1F;
    sy = scrolly & ~0x1F;
    p[1] = ((sx - scrollx) & 0x7FF) + (((sy - scrolly) & 0x7FF) << 0xB) + 0xE5000000;
    p += 2;
    map = bg->map;
    ncellw = map->ncellw;
    ncellh = map->ncellh;
    startcol = ((sx / 32) % ncellw);
    if (startcol < 0) {
        startcol += ncellw;
    }
    row = ((sy / 32) % ncellh);
    if (row < 0) {
        row += ncellh;
    }
    index = (s32) map->index;
    base = map->base;
    for (i = 0; i < hc; i++) {
        lo = row * ncellw;
        rowp = (u16 *) ((u8 *) index + lo * 2);
        col = startcol;
        for (j = 0; j < wc; j++) {
            cellidx = rowp[col];
            if (cellidx == 0xFFFF) {
                ((u_char *) p)[3] = 0;
            } else {
                cell = &base[cellidx];
                ((u_char *) p)[3] = 5;
                *(u16 *) ((u_char *) p + 4) = tpage | (cell->tpage & 0x81F);
                *(u_long *) ((u_char *) p + 0x10) = *(u_long *) cell;
            }
            p = (u_long *) ((u_char *) p + 0x18);
            col++;
            if (col >= ncellw) {
                col = 0;
            }
        }
        row++;
        if (row >= ncellh) {
            row = 0;
        }
        lo = row * ncellw;
    }
    if (PSDGPU != 0) {
        p[1] = POSITION.offx + (&PSDOFSX)[(PSDIDX + 1) & 1]
             + ((POSITION.offy + (&PSDOFSY)[(PSDIDX + 1) & 1]) << 0xB) + 0xE5000000;
    } else {
        p[1] = 0xE5000000;
    }
    tag = &otp->org[(pri & 0xFFFF) + otp->offset];
    p[0] = *(u_long *) tag;
    ((u_char *) p)[3] = 1;
    *(u_long *) tag = (u_long) p0;
    ((u_char *) tag)[3] = 0;
}
