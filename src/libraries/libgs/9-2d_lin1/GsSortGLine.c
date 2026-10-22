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
    u_char r0, g0, b0, code;
    short x0, y0;
    u_char r1, g1, b1, p1;
    short x1, y1;
} GsGLINEPKT;

void GsSortGLine(GsGLINE *lp, GsOT *ot, unsigned short pri) {
    GsGLINEPKT *p;
    u_long attribute;

    attribute = lp->attribute;
    if ((s32) attribute < 0) {
        return;
    }
    p = (GsGLINEPKT *) GsOUT_PACKET_P;
    p->drawmode = (((s32) attribute >> 23) & 0x60) | 0xE1000200;
    p->r0 = lp->r0;
    p->g0 = lp->g0;
    p->b0 = lp->b0;
    p->code = (((s32) attribute >> 29) & 0x02) | 0x50;
    p->x0 = lp->x0 + GsORGOFSX;
    p->y0 = lp->y0 + GsORGOFSY;
    p->r1 = lp->r1;
    p->g1 = lp->g1;
    p->b1 = lp->b1;
    p->x1 = lp->x1 + GsORGOFSX;
    p->y1 = lp->y1 + GsORGOFSY;
    GsOUT_PACKET_P = _make_packet((u_char *) p, ot, pri, 5);
}
