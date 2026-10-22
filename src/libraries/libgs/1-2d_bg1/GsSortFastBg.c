INCLUDE_ASM("build/libraries/nonmatchings/libgs_1", GsSortFastBg);


/* PARKED by /auto_decompilation_loop on 2026-10-22T03:58:46.522Z.
 * Reason: escalation-exhausted.
 * Escalation reached: deepseek-v4-1-flash-1017.
 * The best non-matching attempt is preserved verbatim below, disabled.
 * Findings and the decision needed: notes/human-needed-approvals/libgs_1::GsSortFastBg.md
 */

#if 0
/* Best non-matching attempt, preserved for the next session. */
#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>
#include <stdio.h>

extern s16 GsORGOFSX;
extern s16 GsORGOFSY;

typedef struct {
    u_long tag;
    u_long tpage;
    u_long color;
    short x0, y0;
    u_char u0, v0;
    u_short cba;
    u_long wh;
} PKT18;

typedef struct {
    u_long tag;
    u_long color;
    short x0, y0;
    u_char u0, v0; u_short cba;
    short x1, y1;
    u_char u1, v1; u_short tpage;
    short x2, y2;
    u_char u2, v2; u_short pad1;
    short x3, y3;
    u_char u3, v3; u_short pad2;
} PKT28;

void GsSortFastBg(GsBG *bg, GsOT *ot, unsigned short pri)
{
    u_long attribute;
    GsMAP *map;
    u16 tpage;
    u32 c18, c28, dmaword;
    s32 w, h, xpr, yp;
    u16 cellw, cellh;
    s32 xp;
    s32 cellh16;
    u16 cellw16;
    u16 ncellw, ncellh;
    s32 mapw, maph;
    s32 wend, yend;
    s32 sx, sy, yoff, xoff, x, xclip, hclip;
    u32 xy, wh;
    s32 odd;
    s32 index;
    u16 cellidx;
    GsCELL *cell;
    u8 *p;
    PKT28 *ft4;
    PKT18 *pk;
    GsOT_TAG *tag;
    s32 z;
    s32 syfix;
    attribute = bg->attribute;
    if ((s32) attribute < 0) {
        return;
    }
    map = bg->map;
    cellw = map->cellw;
    if (cellw == 0) {
        cellw = 0x100;
    }
    cellh = map->cellh;
    if (cellh == 0) {
        cellh = 0x100;
    }
    cellw16 = cellw;
    (void) cellw16;
    ncellw = map->ncellw;
    mapw = cellw16 * ncellw;
    tpage = ((attribute >> 17) & 0x180) | ((attribute >> 23) & 0x60);
    sx = (s16) bg->scrollx % mapw;
    c18 = 0x64000000 | ((attribute >> 5) & 0x02000000)
        | ((attribute << 18) & 0x01000000) | bg->r | (bg->g << 8) | (bg->b << 16);
    c28 = 0x2C000000 | ((attribute >> 5) & 0x02000000)
        | ((attribute << 18) & 0x01000000) | bg->r | (bg->g << 8) | (bg->b << 16);
    xpr = (bg->x - bg->mx) + GsORGOFSX;
    ncellh = map->ncellh;
    cellh16 = cellh & 0xFFFF;
    maph = cellh16 * ncellh;
    p = GsOUT_PACKET_P;
    w = bg->w;
    yp = (bg->y - bg->my) + GsORGOFSY;
    h = bg->h;
    if (sx < 0) {
        sx += mapw;
    }
    syfix = (s16) bg->scrolly % maph;
    if (syfix < 0) {
        syfix += maph;
    }
    sy = syfix;
    yoff = sy % cellh16;
    xy &= 0xFFFF;
    xy |= yp << 16;
    wh &= 0xFFFF;
    wh |= (cellh16 - yoff) << 16;
    if (h < (s32) (wh >> 16)) {
        wh &= 0xFFFF;
        wh |= h << 16;
    }
    xp = xpr & 0xFFFF;
    dmaword = tpage | 0xE1000200;
    wend = sx + w;
    yend = sy + h;
    do {
        x = sx;
        xoff = x % cellw16;
        xy = (xy & 0xFFFF0000) | xp;
        xclip = (cellw - xoff) & 0xFFFF;
        wh &= 0xFFFF0000;
        wh |= xclip;
        if (w < xclip) {
            wh &= 0xFFFF0000;
            wh |= (u16) w;
        }
        index = ((sy % maph) / cellh) * ncellw + (x % mapw) / cellw16;
        cellidx = bg->map->index[index];
        if (cellidx != 0xFFFF) {
            cell = &bg->map->base[cellidx];
            odd = x & 1;
            if (odd) {
                ft4 = (PKT28 *) p;
                ft4->tag = (u_long) (p + 0x28);
                ((u8 *) ft4)[3] = 9;
                *(u_long *) &ft4->x0 = xy;
                ft4->color = c28;
                ft4->u0 = cell->u + xoff;
                ft4->v0 = cell->v + yoff;
                ft4->cba = cell->cba;
                ft4->x1 = (short) (xy + 1);
                ft4->y1 = (short) (xy >> 16);
                ft4->u1 = cell->u + xoff;
                ft4->v1 = cell->v + yoff;
                ft4->x2 = (short) xy;
                ft4->y2 = (short) ((xy >> 16) + (wh >> 16));
                ft4->tpage = tpage | (cell->tpage & 0x81F);
                ft4->u2 = cell->u + xoff;
                ft4->v2 = (wh >> 16) + (cell->v + yoff);
                ft4->x3 = (short) (xy + 1);
                ft4->y3 = (short) ((xy >> 16) + (wh >> 16));
                ft4->u3 = cell->u + xoff;
                ft4->v3 = (wh >> 16) + (cell->v + yoff);
                p += 0x28;
            }
            if (wh & 0xFFFE) {
                pk = (PKT18 *) p;
                pk->tag = (u_long) (p + 0x18);
                ((u8 *) pk)[3] = 5;
                pk->tpage = dmaword | (cell->tpage & 0x81F);
                pk->color = c18;
                pk->x0 = (short) (xy + odd);
                pk->y0 = (short) (xy >> 16);
                pk->u0 = (cell->u + xoff + 1) & ~1;
                pk->v0 = cell->v + yoff;
                pk->wh = wh & ~1;
                pk->cba = cell->cba;
                p += 0x18;
            }
        }
        index++;
        if ((index % ncellw) == 0) {
            index -= ncellw;
        }
        x += wh & 0xFFFF;
        xy = (xy & 0xFFFF0000) | ((xy + wh) & 0xFFFF);
        wh = (wh & 0xFFFF0000) | ((wend - x) & 0xFFFF);
        if ((u32) cellw16 < (u32) (wh & 0xFFFF)) {
            wh &= 0xFFFF0000;
            wh |= cellw16;
        }
        cellidx = bg->map->index[index];
        while (x < wend) {
            if (cellidx != 0xFFFF) {
                cell = &bg->map->base[cellidx];
                pk = (PKT18 *) p;
                pk->tag = (u_long) (p + 0x18);
                ((u8 *) pk)[3] = 5;
                pk->u0 = cell->u;
                pk->color = c18;
                *(u_long *) &pk->x0 = xy;
                pk->tpage = dmaword | (cell->tpage & 0x81F);
                pk->v0 = cell->v + yoff;
                pk->wh = wh;
                pk->cba = cell->cba;
                p += 0x18;
            }
            index++;
            if ((index % ncellw) == 0) {
                index -= ncellw;
            }
            x += wh & 0xFFFF;
            xy = (xy & 0xFFFF0000) | ((xy + wh) & 0xFFFF);
            wh = (wh & 0xFFFF0000) | ((wend - x) & 0xFFFF);
            if ((u32) cellw16 < (u32) (wh & 0xFFFF)) {
                wh &= 0xFFFF0000;
                wh |= cellw16;
            }
            cellidx = bg->map->index[index];
        }
        sy += wh >> 16;
        xy = (xy & 0xFFFF) | (((xy >> 16) + (wh >> 16)) << 16);
        wh &= 0xFFFF;
        wh |= (yend - sy) << 16;
        if ((u32) cellh < (u32) (wh >> 16)) {
            wh &= 0xFFFF;
            wh |= (u32) cellh << 16;
        }
        yoff = 0;
    } while (sy < yend);

    z = pri + ot->offset;
    if (z < 0) {
        printf("ps_sort_sprite,bg: z resolution overflow\n");
    }
    if (p != GsOUT_PACKET_P) {
        tag = &ot->org[z];
        p -= 0x18;
        *(u_long *) p = *(u_long *) tag;
        p[3] = 5;
        p += 0x18;
        *(u_long *) tag = (u_long) GsOUT_PACKET_P;
        ((u8 *) tag)[3] = 0;
    }
    GsOUT_PACKET_P = p;
}
#endif
