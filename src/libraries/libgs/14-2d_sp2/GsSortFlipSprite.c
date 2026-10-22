#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>

extern s16 GsORGOFSX;
extern s16 GsORGOFSY;
extern u_char *_make_packet(u_char *p, GsOT *ot, u_short z, u_char flag);

void GsSortFlipSprite(GsSPRITE *sp, GsOT *ot, unsigned short pri) {
    u_long attribute;
    u_long *p;
    s32 sx;
    s32 sy;
    u_long u0, u1, v0, v1;
    u_long tp, dm;

    attribute = sp->attribute;
    if ((s32) attribute < 0) {
        return;
    }
    if (sp->w == 0) {
        return;
    }
    if (sp->h == 0) {
        return;
    }

    p = (u_long *) GsOUT_PACKET_P;
    sx = sp->x + GsORGOFSX - sp->mx;
    sy = sp->y + GsORGOFSY - sp->my;

    if (attribute & 0x800000) {
        u0 = (sp->u + (u_char) sp->w) - 1;
        u1 = sp->u - 1;
    } else {
        u0 = sp->u;
        u1 = sp->u + (u_char) sp->w;
    }
    if (attribute & 0x400000) {
        v0 = (sp->v + (u_char) sp->h) - 1;
        v1 = sp->v - 1;
    } else {
        v0 = sp->v;
        v1 = sp->v + (u_char) sp->h;
    }

    tp = (attribute >> 5) & 0x02000000;
    dm = ((attribute << 18) & 0x01000000) | 0x2C000000;
    p[1] = tp | dm | (sp->b << 16) | (sp->g << 8) | sp->r;
    p[2] = (sx & 0xFFFF) | (sy << 16);
    p[3] = (u0 & 0xFF) | ((v0 & 0xFF) << 8) | (sp->cy << 22)
         | ((sp->cx << 12) & 0x3F0000);
    p[4] = ((sx + sp->w) & 0xFFFF) | (sy << 16);
    p[5] = (u1 & 0xFF) | ((v0 & 0xFF) << 8) | ((sp->tpage & 0x1F) << 16)
         | ((attribute >> 1) & 0x01800000) | ((attribute >> 7) & 0x600000);
    p[6] = (sx & 0xFFFF) | ((sy + sp->h) << 16);
    p[7] = (u0 & 0xFF) | ((v1 & 0xFF) << 8);
    p[8] = ((sx + sp->w) & 0xFFFF) | ((sy + sp->h) << 16);
    p[9] = (u1 & 0xFF) | ((v1 & 0xFF) << 8);
    GsOUT_PACKET_P = _make_packet((u_char *) p, ot, pri, 9);
}
