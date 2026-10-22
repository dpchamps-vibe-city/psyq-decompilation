#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>

extern s16 GsORGOFSX;
extern s16 GsORGOFSY;
extern u_char *_make_packet(u_char *p, GsOT *ot, u_short z, int flag);

void GsSortPoly(void *pp, GsOT *ot, unsigned short pri) {
    u_char *src;
    u_char *dst;
    u_char code;
    s32 gouraud;
    s32 quad;
    s32 texture;
    s32 len;
    s16 ofsx;

    src = (u_char *)pp;
    dst = (u_char *)GsOUT_PACKET_P;
    code = *(u_char *)(src + 7);
    gouraud = code & 0x10;
    quad = code & 0x8;
    texture = code & 0x4;
    ofsx = GsORGOFSX;
    *(u_long *)(dst + 4) = *(u_long *)(src + 4);
    len = 4;
    *(s16 *)(dst + 8) = *(u16 *)(src + 8) + ofsx;
    *(s16 *)(dst + 0xA) = *(u16 *)(src + 0xA) + GsORGOFSY;
    if (texture) {
        *(u_long *)(dst + 0xC) = *(u_long *)(src + 0xC);
        src += 4;
        dst += 4;
        len = 5;
    }
    if (gouraud) {
        *(u_long *)(dst + 0xC) = *(u_long *)(src + 0xC);
        src += 4;
        dst += 4;
        len += 1;
    }
    *(s16 *)(dst + 0xC) = *(u16 *)(src + 0xC) + GsORGOFSX;
    *(s16 *)(dst + 0xE) = *(u16 *)(src + 0xE) + GsORGOFSY;
    if (texture) {
        *(u_long *)(dst + 0x10) = *(u_long *)(src + 0x10);
        src += 4;
        dst += 4;
        len += 1;
    }
    if (gouraud) {
        *(u_long *)(dst + 0x10) = *(u_long *)(src + 0x10);
        src += 4;
        dst += 4;
        len += 1;
    }
    *(s16 *)(dst + 0x10) = *(u16 *)(src + 0x10) + GsORGOFSX;
    *(s16 *)(dst + 0x12) = *(u16 *)(src + 0x12) + GsORGOFSY;
    if (texture) {
        *(u_long *)(dst + 0x14) = *(u_long *)(src + 0x14);
        src += 4;
        dst += 4;
        len += 1;
    }
    if (quad) {
        if (gouraud) {
            *(u_long *)(dst + 0x14) = *(u_long *)(src + 0x14);
            src += 4;
            dst += 4;
            len += 1;
        }
        *(s16 *)(dst + 0x14) = *(u16 *)(src + 0x14) + GsORGOFSX;
        *(s16 *)(dst + 0x16) = *(u16 *)(src + 0x16) + GsORGOFSY;
        len += 1;
        if (texture) {
            *(u_long *)(dst + 0x18) = *(u_long *)(src + 0x18);
            len += 1;
        }
    }
    GsOUT_PACKET_P = _make_packet((u_char *)GsOUT_PACKET_P, ot, pri, len);
}
