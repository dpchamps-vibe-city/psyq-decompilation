INCLUDE_ASM("build/libraries/nonmatchings/libgs_0", GsSortBg);


/* PARKED by /auto_decompilation_loop on 2026-10-22T01:59:57.555Z.
 * Reason: escalation-exhausted.
 * Escalation reached: deepseek-v4-1-flash-1017.
 * The best non-matching attempt is preserved verbatim below, disabled.
 * Findings and the decision needed: notes/human-needed-approvals/libgs_0::GsSortBg.md
 */

#if 0
/* Best non-matching attempt, preserved for the next session. */
#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>

typedef struct {
    u_char code;
    u_char r, g, b;
    u_short tpage;
    u_short cba;
    u_char u, v;
    short x, y;
    u_short w, h;
    short mx, my;
    u_short flag;
    int rotate;
} GsSPKT;

extern void _mk_spr_packet(u_char *p, GsSPKT *sp, MATRIX *m, GsCELL *cell);
extern void gte_rotate_z_matrix(MATRIX *m, long r);
extern int gte_scale_matrix(MATRIX *m, short sx, short sy, short sz);

void GsSortBg(GsBG *bg, GsOT *ot, unsigned short pri) {
    u32 attribute;
    GsCELL *cell;
    MATRIX m;
    GsSPKT sp;
    u16 ncellw;
    u16 ncellh;
    u16 tpage;
    s32 bgw;
    s32 mapw;
    s32 maph;
    u16 cellw;
    u16 cellh;
    s32 y;
    s32 ch;
    s32 yend;
    s32 sx;
    s32 sy;
    s32 sy0;
    s32 yoff;
    s32 hclip;
    s32 xpos;
    s32 x;
    s32 wend;
    s32 bgh;
    s32 index;
    s32 xclip;
    u16 cellidx;
    u_char *p;
    u_char *p4;
    u_char *p4b;
    GsOT_TAG *tag;

    attribute = bg->attribute;
    if ((s32) attribute < 0) {
        return;
    }
    ncellw = bg->map->ncellw;
    if (ncellw == 0) {
        return;
    }
    ncellh = bg->map->ncellh;
    if (ncellh == 0) {
        return;
    }
    cellw = bg->map->cellw;
    if (cellw == 0) {
        cellw = 0x100;
    }
    cellh = bg->map->cellh;
    if (cellh == 0) {
        cellh = 0x100;
    }
    sp.code = ((attribute >> 29) & 2) | (((attribute >> 6) & 1) | 0x2C);
    sp.r = bg->r;
    sp.g = bg->g;
    sp.b = bg->b;
    mapw = cellw * ncellw;
    maph = cellh * ncellh;
    tpage = ((attribute >> 17) & 0x180) | ((attribute >> 23) & 0x60);
    if ((attribute & 0x08000000) || ((*(s32 *) &bg->scalex == 0x10001000) && (bg->rotate == 0))) {
        sp.rotate = 0;
    } else {
        sp.rotate = 1;
        m = GsIDMATRIX;
        gte_rotate_z_matrix(&m, bg->rotate);
        gte_scale_matrix(&m, bg->scalex, bg->scaley, 0x1000);
    }
    sx = (s16) bg->scrollx % mapw;
    p = GsOUT_PACKET_P;
    bgw = bg->w;
    bgh = bg->h;
    if (sx < 0) {
        sx += mapw;
    }
    sy = (s16) bg->scrolly % maph;
    if (sy < 0) {
        sy += maph;
    }
    sy0 = sy;
    yoff = sy % cellh;
    y = bg->y;
    hclip = cellh - yoff;
    if (bgh < (hclip & 0xFFFF)) {
        hclip = bgh;
    }
    wend = sx + bgw;
    yend = sy0 + bgh;
    ch = cellh;
    sp.h = hclip;
    sp.y = (short) y;
    sp.my = -bg->my;
    p4 = p + 4;
    while (sy < yend) {
        x = sx;
        xpos = bg->x;
        xclip = cellw - (x % cellw);
        if (bgw < (xclip & 0xFFFF)) {
            xclip = bgw;
        }
        index = ((x % mapw) / cellw) + (((sy % maph) / cellh) * ncellw);
        cellidx = bg->map->index[index];
        if (cellidx != 0xFFFF) {
            cell = &bg->map->base[cellidx];
            *(u32 *) p = (u32) (p + 0x28);
            p4[-1] = 9;
            sp.tpage = tpage | (cell->tpage & 0x81F);
            sp.x = (short) xpos;
            sp.cba = cell->cba;
            if (cell->flag & 2) {
                sp.u = cell->u;
            } else {
                sp.u = cell->u + (x % cellw);
            }
            if (cell->flag & 1) {
                sp.v = ((cellh + (s32) cell->v) - hclip) - yoff;
            } else {
                sp.v = cell->v + yoff;
            }
            sp.w = xclip;
            sp.mx = (x - sx) - bg->mx;
            sp.flag = cell->flag;
            _mk_spr_packet(p4, &sp, &m, cell);
            p += 0x28;
            p4 += 0x28;
        }
        if (x < wend) {
            p4b = p + 4;
            index++;
            do {
                if ((index % ncellw) == 0) {
                    index -= ncellw;
                }
                x += (xclip & 0xFFFF);
                xpos += (xclip & 0xFFFF);
                xclip = wend - x;
                if ((u32) cellw < (u32) (xclip & 0xFFFF)) {
                    xclip = cellw;
                }
                cellidx = bg->map->index[index];
                if (cellidx != 0xFFFF) {
                    cell = &bg->map->base[cellidx];
                    *(u32 *) p = (u32) (p + 0x28);
                    p[3] = 9;
                    sp.tpage = tpage | (cell->tpage & 0x81F);
                    sp.x = (short) ((xpos - x) + sx);
                    sp.cba = cell->cba;
                    if (cell->flag & 2) {
                        sp.u = (cellw + cell->u) - xclip;
                    } else {
                        sp.u = cell->u;
                    }
                    if (cell->flag & 1) {
                        sp.v = ((cellh + (s32) cell->v) - hclip) - yoff;
                    } else {
                        sp.v = cell->v + yoff;
                    }
                    sp.w = xclip;
                    sp.mx = (x - sx) - bg->mx;
                    sp.flag = cell->flag;
                    _mk_spr_packet(p4b, &sp, &m, cell);
                    p += 0x28;
                    p4 += 0x28;
                    p4b += 0x28;
                }
                index++;
            } while (x < wend);
            index--;
        }
        y += (hclip & 0xFFFF);
        sy += (hclip & 0xFFFF);
        hclip = yend - sy;
        if ((u32) ch < (u32) (hclip & 0xFFFF)) {
            hclip = cellh;
        }
        sp.h = hclip;
        sp.y = (short) (y - sy + sy0);
        sp.my = (short) (sy - sy0 - bg->my);
        yoff = 0;
    }
    index = pri + ot->offset;
    if (index < 0) {
        index = 0;
    }
    if (p != GsOUT_PACKET_P) {
        p -= 0x28;
        tag = &ot->org[index];
        *(u32 *) p = *(u32 *) tag;
        p[3] = 9;
        p += 0x28;
        *(u32 *) tag = (u32) GsOUT_PACKET_P;
        ((u8 *) tag)[3] = 0;
    }
    GsOUT_PACKET_P = p;
}
#endif
