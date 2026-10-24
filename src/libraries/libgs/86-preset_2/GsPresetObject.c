#include "common.h"
#include <sys/types.h>
#include <stdio.h>
#include <libetc.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>

extern char RO_STR_000009C8[];

u_long *GsPresetObject(GsDOBJ5 *objp, u_long *base_addr) {
    struct TMD_STRUCT *tmd;
    u_long *prim;
    u_long *p;
    u_long *h;
    u_long n;
    u_long i;
    u_long type;
    int cnt;
    u_long grd;
    u_long oldcode;
    u_long ptype;
    u_short pgrd;
    u_long w;
    u_long v;

    tmd = (struct TMD_STRUCT *) objp->tmd;
    prim = tmd->primtop;
    n = tmd->primn;
    grd = 0;
    type = 0;
    cnt = 0;
    p = base_addr;
    h = p;
    objp->packet = p;
    p += 2;

    for (i = 0; i < n; i++) {
        w = prim[0];
        oldcode = type;
        type = w >> 24;
        ptype = oldcode & 0xFF;
        pgrd = grd;
        grd = (w >> 16) & 4;
        if (ptype != 0) {
            if ((type != ptype) || (grd != (pgrd & 0xFF))) {
                if (pgrd & 0xFF) {
                    *h++ = (ptype << 24) | 0x10000000 | (((u_long) p) & 0xFFFFFF);
                } else {
                    *h++ = (ptype << 24) | (((u_long) p) & 0xFFFFFF);
                }
                *h = cnt;
                cnt = 0;
                h = p;
                p += 2;
            }
        }
        p += 1;


        switch (type & 0xFD) {

        case 0x20:
            if (grd) {
                w = prim[0];
                v = prim[1] | 0x10000000;
                *p = v;
                v = prim[2];
                p += 2;
                *p = v;
                v = prim[3];
                p += 2;
                *p = v;
                v = prim[1] | 0x10000000;
                p += 3;
                *p = v;
                v = prim[2];
                p += 2;
                *p = v;
                p += 2;
                v = prim[3];
                *p = v;
                p += 2;
                prim += 6;
            } else {
                v = prim[1];
                *p = v;
                p += 5;
                v = prim[1];
                *p = v;
                p += 4;
                prim += 4;
            }
            break;
        case 0x21:
            v = prim[1];
            *p = v;
            p += 5;
            v = prim[1];
            *p = v;
            p += 4;
            prim += 4;
            break;
        case 0x24:
            v = (prim[0] & 0xFF000000) | 0x808080;
            *p = v;
            v = prim[1];
            p += 2;
            *p = v;
            v = prim[2];
            p += 2;
            *p = v;
            v = prim[3];
            p += 2;
            *p = v;
            p += 2;
            v = (prim[0] & 0xFF000000) | 0x808080;
            *p = v;
            v = prim[1];
            p += 2;
            *p = v;
            v = prim[2];
            p += 2;
            *p = v;
            p += 2;
            v = prim[3];
            *p = v;
            p += 1;
            prim += 6;
            break;
        case 0x30:
            if (grd) {
                v = prim[1] | 0x10000000;
                *p = v;
                v = prim[2];
                p += 2;
                *p = v;
                v = prim[3];
                p += 2;
                *p = v;
                v = prim[1] | 0x10000000;
                p += 3;
                *p = v;
                v = prim[2];
                p += 2;
                *p = v;
                p += 2;
                v = prim[3];
                *p = v;
                p += 2;
                prim += 7;
            } else {
                v = prim[1];
                *p = v;
                v = prim[1];
                p += 2;
                *p = v;
                v = prim[1];
                p += 2;
                *p = v;
                v = prim[1];
                p += 3;
                *p = v;
                v = prim[1];
                p += 2;
                *p = v;
                p += 2;
                v = prim[1];
                *p = v;
                p += 2;
                prim += 5;
            }
            break;
        case 0x34:
            v = (prim[0] & 0xFF000000) | 0x808080;
            *p = v;
            v = prim[1];
            p += 2;
            *p = v;
            p += 1;
            *p = 0x808080;
            v = prim[2];
            p += 2;
            *p = v;
            p += 1;
            *p = 0x808080;
            v = prim[3];
            p += 2;
            *p = v;
            p += 2;
            v = (prim[0] & 0xFF000000) | 0x808080;
            *p = v;
            v = prim[1];
            p += 2;
            *p = v;
            p += 1;
            *p = 0x808080;
            v = prim[2];
            p += 2;
            *p = v;
            p += 1;
            *p = 0x808080;
            v = prim[3];
            p += 2;
            *p = v;
            p += 1;
            prim += 7;
            break;
        case 0x28:
            v = prim[1];
            *p = v;
            p += 6;
            v = prim[1];
            *p = v;
            p += 5;
            prim += 5;
            break;
        case 0x29:
            v = prim[1];
            *p = v;
            p += 6;
            v = prim[1];
            *p = v;
            p += 5;
            prim += 4;
            break;
        case 0x2C:
            v = (prim[0] & 0xFF000000) | 0x808080;
            *p = v;
            v = prim[1];
            p += 2;
            *p = v;
            v = prim[2];
            p += 2;
            *p = v;
            v = prim[3];
            p += 2;
            *p = v;
            v = prim[4];
            p += 2;
            *p = v;
            p += 2;
            v = (prim[0] & 0xFF000000) | 0x808080;
            *p = v;
            v = prim[1];
            p += 2;
            *p = v;
            v = prim[2];
            p += 2;
            *p = v;
            v = prim[3];
            p += 2;
            *p = v;
            p += 2;
            v = prim[4];
            *p = v;
            p += 1;
            prim += 8;
            break;
        case 0x38:
            v = prim[1];
            *p = v;
            v = prim[1];
            p += 2;
            *p = v;
            v = prim[1];
            p += 2;
            *p = v;
            v = prim[1];
            p += 2;
            *p = v;
            v = prim[1];
            p += 3;
            *p = v;
            v = prim[1];
            p += 2;
            *p = v;
            v = prim[1];
            p += 2;
            *p = v;
            p += 2;
            v = prim[1];
            *p = v;
            p += 2;
            prim += 6;
            break;
        case 0x3C:
            v = (prim[0] & 0xFF000000) | 0x808080;
            *p = v;
            v = prim[1];
            p += 2;
            *p = v;
            p += 1;
            *p = 0x808080;
            v = prim[2];
            p += 2;
            *p = v;
            p += 1;
            *p = 0x808080;
            v = prim[3];
            p += 2;
            *p = v;
            p += 1;
            *p = 0x808080;
            v = prim[4];
            p += 2;
            *p = v;
            p += 2;
            v = (prim[0] & 0xFF000000) | 0x808080;
            *p = v;
            v = prim[1];
            p += 2;
            *p = v;
            p += 1;
            *p = 0x808080;
            v = prim[2];
            p += 2;
            *p = v;
            p += 1;
            *p = 0x808080;
            v = prim[3];
            p += 2;
            *p = v;
            p += 1;
            *p = 0x808080;
            p += 2;
            v = prim[4];
            *p = v;
            p += 1;
            prim += 9;
            break;
        case 0x31:
            v = prim[1];
            *p = v;
            v = prim[2];
            p += 2;
            *p = v;
            v = prim[3];
            p += 2;
            *p = v;
            v = prim[1];
            p += 3;
            *p = v;
            v = prim[2];
            p += 2;
            *p = v;
            p += 2;
            v = prim[3];
            *p = v;
            p += 2;
            prim += 6;
            break;
        case 0x25:
            v = (prim[0] & 0xFE000000) | prim[4];
            *p = v;
            v = prim[1];
            p += 2;
            *p = v;
            v = prim[2];
            p += 2;
            *p = v;
            v = prim[3];
            p += 2;
            *p = v;
            p += 2;
            v = (prim[0] & 0xFE000000) | prim[4];
            *p = v;
            v = prim[1];
            p += 2;
            *p = v;
            v = prim[2];
            p += 2;
            *p = v;
            p += 2;
            v = prim[3];
            *p = v;
            p += 1;
            prim += 7;
            break;
        case 0x35:
            v = (prim[0] & 0xFE000000) | prim[4];
            *p = v;
            v = prim[1];
            p += 2;
            *p = v;
            v = prim[5];
            p += 1;
            *p = v;
            v = prim[2];
            p += 2;
            *p = v;
            v = prim[6];
            p += 1;
            *p = v;
            v = prim[3];
            p += 2;
            *p = v;
            p += 2;
            v = (prim[0] & 0xFE000000) | prim[4];
            *p = v;
            v = prim[1];
            p += 2;
            *p = v;
            v = prim[5];
            p += 1;
            *p = v;
            v = prim[2];
            p += 2;
            *p = v;
            v = prim[6];
            p += 1;
            *p = v;
            p += 2;
            v = prim[3];
            *p = v;
            p += 1;
            prim += 9;
            break;
        case 0x39:
            v = prim[1];
            *p = v;
            v = prim[2];
            p += 2;
            *p = v;
            v = prim[3];
            p += 2;
            *p = v;
            v = prim[4];
            p += 2;
            *p = v;
            v = prim[1];
            p += 3;
            *p = v;
            v = prim[2];
            p += 2;
            *p = v;
            v = prim[3];
            p += 2;
            *p = v;
            p += 2;
            v = prim[4];
            *p = v;
            p += 2;
            prim += 7;
            break;
        case 0x2D:
            v = (prim[0] & 0xFE000000) | prim[5];
            *p = v;
            v = prim[1];
            p += 2;
            *p = v;
            v = prim[2];
            p += 2;
            *p = v;
            v = prim[3];
            p += 2;
            *p = v;
            v = prim[4];
            p += 2;
            *p = v;
            p += 2;
            v = (prim[0] & 0xFE000000) | prim[5];
            *p = v;
            v = prim[1];
            p += 2;
            *p = v;
            v = prim[2];
            p += 2;
            *p = v;
            v = prim[3];
            p += 2;
            *p = v;
            p += 2;
            v = prim[4];
            *p = v;
            p += 1;
            prim += 8;
            break;
        case 0x3D:
            v = (prim[0] & 0xFE000000) | prim[5];
            *p = v;
            v = prim[1];
            p += 2;
            *p = v;
            v = prim[6];
            p += 1;
            *p = v;
            v = prim[2];
            p += 2;
            *p = v;
            v = prim[7];
            p += 1;
            *p = v;
            v = prim[3];
            p += 2;
            *p = v;
            v = prim[8];
            p += 1;
            *p = v;
            v = prim[4];
            p += 2;
            *p = v;
            p += 2;
            v = (prim[0] & 0xFE000000) | prim[5];
            *p = v;
            v = prim[1];
            p += 2;
            *p = v;
            v = prim[6];
            p += 1;
            *p = v;
            v = prim[2];
            p += 2;
            *p = v;
            v = prim[7];
            p += 1;
            *p = v;
            v = prim[3];
            p += 2;
            *p = v;
            v = prim[8];
            p += 1;
            *p = v;
            p += 2;
            v = prim[4];
            *p = v;
            p += 1;
            prim += 11;
            break;
        default:
            printf(RO_STR_000009C8, *(u_char *) prim);
            break;
        }
        cnt += 1;
    }

    if (pgrd & 0xFF) {
        *h++ = (type << 24) | 0x10000000;
    } else {
        *h++ = type << 24;
    }
    *h = cnt;
    return p;
}

