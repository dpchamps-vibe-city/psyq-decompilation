#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>

extern u16 GsORGOFSX;
extern u16 GsORGOFSY;

void GsSortFastSpriteA(GsSPRITE *sp, GsOT *ot, u_short pri) {
    u_long attribute;
    u_long *p;
    u_long *tag;
    s32 sx;
    s32 sy;

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
    sx = (u_short) sp->x + GsORGOFSX;
    sy = (u_short) sp->y + GsORGOFSY;
    p[1] = (sp->tpage & 0x7F) | 0xE1000000
         | ((attribute >> 15) & 0x600)
         | ((attribute >> 21) & 0x180);
    p[2] = ((attribute >> 5) & 0x02000000) | 0x64000000
         | ((attribute << 18) & 0x01000000)
         | (sp->b << 16) | (sp->g << 8) | sp->r;
    p[3] = (sx & 0xFFFF) | (sy << 16);
    p[4] = sp->u | (sp->v << 8) | (sp->cy << 22)
         | ((sp->cx << 12) & 0x3F0000);
    p[5] = sp->w | (sp->h << 16);
    tag = (u_long *) &ot->org[pri & 0xFFFF] - ot->offset;
    p[0] = *tag + 0x05000000;
    *tag = (u_long) p & 0xFFFFFF;
    GsOUT_PACKET_P = (PACKET *) (p + 6);
}
