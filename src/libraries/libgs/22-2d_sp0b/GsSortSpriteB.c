INCLUDE_ASM("build/libraries/nonmatchings/libgs_22", GsSortSpriteB);


/* PARKED by /auto_decompilation_loop on 2026-10-23T16:34:20.929Z.
 * Reason: escalation-exhausted.
 * Escalation reached: deepseek-v4-1-flash-1017.
 * The best non-matching attempt is preserved verbatim below, disabled.
 * Findings and the decision needed: notes/human-needed-approvals/libgs_22::GsSortSpriteB.md
 */

#if 0
/* Best non-matching attempt, preserved for the next session. */
#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>

extern s16 GsORGOFSX;
extern s16 GsORGOFSY;
extern u_char *_make_packet(u_char *p, GsOT *ot, u_short z, u_char flag);

void GsSortSpriteB(GsSPRITE *sp, GsOT *ot, unsigned short pri, unsigned short flip) {
    MATRIX m;
    SVECTOR rot;
    VECTOR vec;
    SVECTOR v0;
    SVECTOR v1;
    SVECTOR v2;
    SVECTOR v3;
    long sxy[4];
    long pz;
    long flg;
    u_long attribute;
    u_long *p;
    u_long u0;
    u_long u1;
    u_long vv0;
    u_long vv1;
    u_long word;
    u_long hibits;
    s32 flag;
    s32 ofsx;
    s32 ofsy;
    s32 sx;
    s32 sy;
    s32 rotoff;

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
    rotoff = (attribute >> 27) & 1;
    flag = 0;
    if (*(s32 *) &sp->scalex == 0x10001000 && sp->rotate == 0) {
        flag = (attribute & 0xC00000) == 0;
    }
    if (rotoff | flag) {
        sx = sp->x + GsORGOFSX;
        sy = sp->y + GsORGOFSY;
        p[1] = (sp->tpage & 0x81F) | 0xE1000200
             | ((attribute >> 17) & 0x180)
             | ((attribute >> 23) & 0x60)
             | ((flip & 3) << 12);
        p[2] = ((attribute >> 5) & 0x02000000) | 0x64000000
             | ((attribute << 18) & 0x01000000)
             | (sp->b << 16) | (sp->g << 8) | sp->r;
        p[3] = ((sx - sp->mx) & 0xFFFF) | ((sy - sp->my) << 16);
        p[4] = sp->u | (sp->v << 8) | (sp->cy << 22)
             | ((sp->cx << 12) & 0x3F0000);
        word = sp->w;
        p[5] = word | (sp->h << 16);
        p = (u_long *) _make_packet((u_char *) p, ot, pri, 5);
    } else {
        if (sp->rotate == 0) {
            m = GsIDMATRIX;
        } else {
            rot.vx = 0;
            rot.vy = 0;
            rot.vz = sp->rotate / 360;
            RotMatrix(&rot, &m);
        }
        if (*(s32 *) &sp->scalex != 0x10001000) {
            vec.vx = sp->scalex;
            vec.vy = sp->scaley;
            vec.vz = 0;
            ScaleMatrix(&m, &vec);
        }
        vec.vx = sp->x;
        vec.vy = sp->y;
        vec.vz = ReadGeomScreen();
        TransMatrix(&m, &vec);
        SetRotMatrix(&m);
        SetTransMatrix(&m);
        ofsx = -sp->mx;
        ofsy = -sp->my;
        v0.vx = ofsx;
        v0.vy = ofsy;
        v0.vz = 0;
        v1.vx = sp->w + ofsx;
        v1.vy = ofsy;
        v1.vz = 0;
        v2.vx = ofsx;
        v2.vy = sp->h + ofsy;
        v2.vz = 0;
        v3.vx = sp->w + ofsx;
        v3.vy = sp->h + ofsy;
        v3.vz = 0;
        RotTransPers4(&v0, &v1, &v2, &v3, &sxy[0], &sxy[1], &sxy[2], &sxy[3],
                      &pz, &flg);
        if (attribute & 0x800000) {
            u0 = (sp->u + (u_char) sp->w) - 1;
            u1 = sp->u;
        } else {
            u0 = sp->u;
            u1 = (sp->u + (u_char) sp->w) - 1;
        }
        if (attribute & 0x400000) {
            vv0 = (sp->v + (u_char) sp->h) - 1;
            vv1 = sp->v;
        } else {
            vv0 = sp->v;
            vv1 = (sp->v + (u_char) sp->h) - 1;
        }
        p[1] = ((attribute >> 5) & 0x02000000) | 0x2C000000
             | ((attribute << 18) & 0x01000000)
             | (sp->b << 16) | (sp->g << 8) | sp->r;
        p[2] = sxy[0];
        p[4] = sxy[1];
        p[3] = (u0 & 0xFF) | ((vv0 & 0xFF) << 8) | (sp->cy << 22)
             | ((sp->cx << 12) & 0x3F0000);
        hibits = attribute >> 1;
        p[6] = sxy[2];
        p[7] = (u0 & 0xFF) | ((vv1 & 0xFF) << 8);
        p[8] = sxy[3];
        p[9] = (u1 & 0xFF) | ((vv1 & 0xFF) << 8);
        word = (u1 & 0xFF) | ((vv0 & 0xFF) << 8) | ((sp->tpage & 0x81F) << 16)
             | (hibits & 0x01800000);
        p[5] = word | ((attribute >> 7) & 0x600000);
        p = (u_long *) _make_packet((u_char *) p, ot, pri, 9);
    }
    GsOUT_PACKET_P = (PACKET *) p;
}
#endif
