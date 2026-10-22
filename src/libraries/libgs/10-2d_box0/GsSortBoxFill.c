#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>

extern s16 GsORGOFSX;
extern s16 GsORGOFSY;
extern u_char *_make_packet(u_char *p, GsOT *ot, u_short z, u_char flag);

typedef struct {
    u_long tag;
    u_long drawmode;
    u_char r, g, b, code;
    short x, y;
    unsigned short w, h;
} GsBOXF_PKT;

void GsSortBoxFill(GsBOXF *bp, GsOT *ot, unsigned short pri) {
    GsBOXF_PKT *p;
    u_long attribute;
    u_long tpage;
    u_long drawmode;

    attribute = bp->attribute;
    if ((s32) attribute < 0) {
        return;
    }
    tpage = ((s32) attribute >> 17) & 0x180;
    drawmode = (((s32) attribute >> 23) & 0x60) | 0xE1000200;
    p = (GsBOXF_PKT *) GsOUT_PACKET_P;
    p->drawmode = tpage | drawmode;
    p->r = bp->r;
    p->g = bp->g;
    p->b = bp->b;
    p->code = (((s32) attribute >> 29) & 0x02) | 0x60;
    p->x = bp->x + GsORGOFSX;
    p->y = bp->y + GsORGOFSY;
    p->w = bp->w;
    p->h = bp->h;
    GsOUT_PACKET_P = _make_packet((u_char *) p, ot, pri, 4);
}
