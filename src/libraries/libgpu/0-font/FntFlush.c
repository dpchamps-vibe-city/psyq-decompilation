#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <memory.h>
#include <strings.h>

extern s32 D_00000D30;
extern s32 D_00000D34;

u_long *FntFlush(int id) {
    FENTRY *fp;
    u_long *ot;
    SPRT_8 *sp;
    SPRT_8 *spt;
    s8 *p;
    s32 x;
    s32 y;
    s32 xend;
    s32 maxx;
    s32 yend;
    s32 step;
    s32 flag;
    s32 brk;
    s32 r;
    s32 g;
    s32 b;
    s32 c;

    maxx = 0;
    r = 0x80;
    g = 0x80;
    b = 0x80;
    if ((id < 0) || (id >= D_00000D30)) {
        id = D_00000D34;
        if (Font[id].text == 0) {
            return 0;
        }
    }
    fp = &Font[id];
    ot = (u_long *)&fp->drmode;
    p = (s8 *)fp->text;
    step = fp->step;
    x = fp->tile.x0;
    y = fp->tile.y0;
    xend = x + fp->tile.w;
    yend = y + fp->tile.h;
    sp = fp->sprt;
    spt = sp;
    flag = fp->flag;
    TermPrim(ot);
    while (*p != 0) {
        if (step == 0) {
            break;
        }
        brk = 0;
        switch (*p) {
        case 0x7E:
            p++;
            if (*p == 0x63) {
                p++;
                r = (*p++ - 0x30) * 0x10;
                g = (*p++ - 0x30) * 0x10;
                b = (*p - 0x30) * 0x10;
            }
            break;
        case 0x9:
            x += 0x20;
            if ((x >= xend) && (flag == 0)) {
                brk = 1;
            }
            break;
        case 0xA:
            brk = 1;
            break;
        case 0x20:
            x += 8;
            if ((x >= xend) && (flag == 0)) {
                brk = 1;
            }
            break;
        default:
            if ((u_char)(*p - 0x61) < 0x1A) {
                c = *p - 0x40;
            } else {
                c = *p - 0x20;
            }
            spt->u0 = (c % 0x10) * 8;
            spt->v0 = (c / 0x10) * 8;
            spt->x0 = x;
            spt->y0 = y;
            spt->r0 = r;
            spt->g0 = g;
            spt->b0 = b;
            AddPrim(ot, spt++);
            x += 8;
            if ((x >= xend) && (flag == 0)) {
                brk = 1;
            }
            break;
        }
        if (brk != 0) {
            if (maxx < x) {
                maxx = x;
            }
            y += 8;
            x = fp->tile.x0;
            if (y >= yend) {
                break;
            }
        }
        p++;
        step--;
    }
    if (fp->tile.code != 0) {
        AddPrim(ot, fp);
        if (flag != 0) {
            fp->tile.w = maxx - fp->tile.x0;
            fp->tile.h = y - (s16)(fp->tile.y0 - 8);
        }
    }
    DrawOTag(ot);
    fp->pos = 0;
    *fp->text = 0;
    return ot;
}
