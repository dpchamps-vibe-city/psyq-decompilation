INCLUDE_ASM("build/libraries/nonmatchings/libgte_224", pers_map);


/* PARKED by /auto_decompilation_loop on 2026-10-26T11:37:10.414Z.
 * Reason: escalation-exhausted.
 * Escalation reached: gpt-6.1-sol.
 * The best non-matching attempt is preserved verbatim below, disabled.
 * Findings and the decision needed: notes/human-needed-approvals/libgte_224::pers_map.md
 */

#if 0
/* Best non-matching attempt, preserved for the next session. */
#include "common.h"
#include <sys/types.h>
#include <libgte.h>

static int func_00000C84();
static void func_000013FC(int abuf, short *sxy, int (*tex)[2], MATRIX *m, u_short *dtext);

/*
 * Perspective-map a quad: rotate four vertices, clip them, project each
 * resulting vertex and draw the textured polygon.
 */
void pers_map(int abuf, SVECTOR **vertex, int tex[4][2], u_short *dtext)
{
    struct {
        VECTOR  clipped[2][4];
        int     clipTex[8][2];
        DVECTOR projected[2][4];
    } buf;
    VECTOR transformed[4];
    MATRIX m;
    long flag[2];
    long ofx, ofy;
    long n;
    long i;
    DVECTOR *dst;
    long screen;
    long x, y;

    RotTrans(vertex[0], &transformed[0], &flag);
    RotTrans(vertex[1], &transformed[1], &flag);
    RotTrans(vertex[2], &transformed[2], &flag);
    RotTrans(vertex[3], &transformed[3], &flag);

    m.m[0][0] = transformed[1].vx - transformed[0].vx;
    m.m[0][1] = transformed[3].vx - transformed[0].vx;
    m.m[0][2] = transformed[0].vx;
    m.m[1][0] = transformed[1].vy - transformed[0].vy;
    m.m[1][1] = transformed[3].vy - transformed[0].vy;
    m.m[1][2] = transformed[0].vy;
    m.m[2][0] = transformed[1].vz - transformed[0].vz;
    m.m[2][1] = transformed[3].vz - transformed[0].vz;
    m.m[2][2] = transformed[0].vz;

    n = func_00000C84(transformed, tex, 8, buf.clipped[0], buf.clipTex);

    for (i = 0; i < n; i++) {
        dst = (DVECTOR *)((char *)buf.projected + (i << 4));
        screen = ReadGeomScreen();
        ReadGeomOffset(&ofx, &ofy);
        x = ofx + buf.clipped[i][0].vx * screen / buf.clipped[i][0].vz;
        y = ofy + buf.clipped[i][0].vy * screen / buf.clipped[i][0].vz;
        if (x < -0x8000) x = -0x8000;
        if (x > 0x7FFF) x = 0x7FFF;
        if (y < -0x8000) y = -0x8000;
        if (y > 0x7FFF) y = 0x7FFF;
        dst[0].vx = x;
        dst[0].vy = y;

        screen = ReadGeomScreen();
        ReadGeomOffset(&ofx, &ofy);
        {
            VECTOR *cv = &buf.clipped[i][1];
            x = ofx + cv->vx * screen / cv->vz;
            y = ofy + cv->vy * screen / cv->vz;
        }
        if (x < -0x8000) x = -0x8000;
        if (x > 0x7FFF) x = 0x7FFF;
        if (y < -0x8000) y = -0x8000;
        if (y > 0x7FFF) y = 0x7FFF;
        dst[1].vx = x;
        dst[1].vy = y;

        screen = ReadGeomScreen();
        ReadGeomOffset(&ofx, &ofy);
        {
            VECTOR *cv = &buf.clipped[i][2];
            x = ofx + cv->vx * screen / cv->vz;
            y = ofy + cv->vy * screen / cv->vz;
        }
        if (x < -0x8000) x = -0x8000;
        if (x > 0x7FFF) x = 0x7FFF;
        if (y < -0x8000) y = -0x8000;
        if (y > 0x7FFF) y = 0x7FFF;
        dst[2].vx = x;
        dst[2].vy = y;

        screen = ReadGeomScreen();
        ReadGeomOffset(&ofx, &ofy);
        {
            VECTOR *cv = &buf.clipped[i][3];
            x = ofx + cv->vx * screen / cv->vz;
            y = ofy + cv->vy * screen / cv->vz;
        }
        if (x < -0x8000) x = -0x8000;
        if (x > 0x7FFF) x = 0x7FFF;
        if (y < -0x8000) y = -0x8000;
        if (y > 0x7FFF) y = 0x7FFF;
        dst[3].vx = x;
        dst[3].vy = y;

        if (NormalClip(*(long *)&buf.projected[i][0], *(long *)&buf.projected[i][1], *(long *)&buf.projected[i][2]) <= 0)
            break;

        func_000013FC(abuf, (short *)dst, tex, &m, dtext);
    }
}
#endif
