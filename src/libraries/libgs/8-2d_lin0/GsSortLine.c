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
    short x0, y0, x1, y1;
} GsLINEPKT;

void GsSortLine(GsLINE *lp, GsOT *ot, unsigned short pri) {
    GsLINEPKT *p;
    u_long attribute;

    attribute = lp->attribute;
    if ((s32) attribute < 0) {
        return;
    }
    p = (GsLINEPKT *) GsOUT_PACKET_P;
    p->drawmode = (((s32) attribute >> 23) & 0x60) | 0xE1000200;
    p->r = lp->r;
    p->g = lp->g;
    p->b = lp->b;
    p->code = (((s32) attribute >> 29) & 0x02) | 0x40;
    p->x0 = lp->x0 + GsORGOFSX;
    p->y0 = lp->y0 + GsORGOFSY;
    p->x1 = lp->x1 + GsORGOFSX;
    p->y1 = lp->y1 + GsORGOFSY;
    GsOUT_PACKET_P = _make_packet((u_char *) p, ot, pri, 4);
}
