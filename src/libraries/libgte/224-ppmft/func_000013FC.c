#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <stdio.h>
#include "libgte-ppmft.h"

static int func_00000080(int, int, int, int);
static int func_000000D0(int, int, int, int);
static int func_000006BC(int *, int);
static void func_00001AFC(MATRIX *, int [3][3]);

static void func_000013FC(int page, short *quad, int uv[4][2],
                          MATRIX *transform, unsigned short *image)
{
    MATRIX map;
    int inverse[3][3];
    MATRIX rotation;
    int boundMin[2], boundMax[2];
    int clipMin[2], clipMax[2];
    RECT rect;
    int order0[4];
    int order1[4];
    int y0[4];
    int y1[4];
    int slope0[4];
    int slope1[4];
    int slopes[4];
    long ofx, ofy;
    long screen;
    unsigned long *buffer;
    int area;
    int shift;
    int n;
    int j, i;
    int edge;
    int (*base)[3];
    int *row, *cell;
    int start0, start1;
    int value;
    int *minCoord, *maxCoord;

    area = (uv[2][1] - uv[3][1]) * (uv[2][0] - uv[1][0])
         - (uv[2][0] - uv[3][0]) * (uv[2][1] - uv[1][1]);
    if (area == 0) {
        printf(RO_STR_00001CC0);
        return;
    }
    map.m[0][2] = uv[0][0] * 16;
    map.m[1][2] = uv[0][1] * 16;
    map.m[2][0] = (((uv[2][1] - uv[3][1]) * (uv[1][0] - uv[0][0])
                 + (uv[1][1] - uv[0][1]) * (uv[3][0] - uv[2][0])) << 12) / area;
    map.m[2][1] = (((uv[2][1] - uv[1][1]) * (uv[3][0] - uv[0][0])
                 + (uv[3][1] - uv[0][1]) * (uv[1][0] - uv[2][0])) << 12) / -area;
    map.m[0][0] = (((map.m[2][0] + 4096) * uv[1][0]) << 4) / 4096 - uv[0][0] * 16;
    map.m[0][1] = (((map.m[2][1] + 4096) * uv[3][0]) << 4) / 4096 - uv[0][0] * 16;
    map.m[1][0] = (((map.m[2][0] + 4096) * uv[1][1]) << 4) / 4096 - uv[0][1] * 16;
    map.m[1][1] = (((map.m[2][1] + 4096) * uv[3][1]) << 4) / 4096 - uv[0][1] * 16;
    map.m[2][2] = 4096;
    func_00001AFC(transform, inverse);
    base = inverse;
    n = Lzc(func_000006BC(base[0], 9));
    if (n >= 18) shift = 0;
    else shift = 18 - n;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            base[i][j] >>= shift;
        }
    }
    rotation.t[0] = 0;
    rotation.t[1] = 0;
    rotation.t[2] = 0;
    rotation.m[0][0] = inverse[0][0];
    rotation.m[0][1] = inverse[0][1];
    rotation.m[0][2] = inverse[0][2];
    rotation.m[1][0] = inverse[1][0];
    rotation.m[1][1] = inverse[1][1];
    rotation.m[1][2] = inverse[1][2];
    rotation.m[2][0] = inverse[2][0];
    rotation.m[2][1] = inverse[2][1];
    rotation.m[2][2] = inverse[2][2];
    PushMatrix();
    ReadGeomOffset(&ofx, &ofy);
    screen = ReadGeomScreen();
    MulMatrix2(&map, &rotation);
    SetRotMatrix(&rotation);
    SetTransMatrix(&rotation);
    SetGeomOffset(0, 0);
    SetGeomScreen(256);
    buffer = B_00001D00;
    minCoord = boundMin;
    maxCoord = boundMax;
    *minCoord++ = func_00000080(*quad, *(quad + 2), *(quad + 4), *(quad + 6));
    *minCoord = func_00000080(*(quad + 1), *(quad + 3), *(quad + 5), *(quad + 7));
    *maxCoord++ = func_000000D0(*quad, *(quad + 2), *(quad + 4), *(quad + 6));
    *maxCoord = func_000000D0(*(quad + 1), *(quad + 3), *(quad + 5), *(quad + 7));
    if (boundMin[0] < 0) clipMin[0] = 0;
    else clipMin[0] = boundMin[0];
    if (boundMin[0] >= 320) clipMin[0] = 319;
    if (boundMax[0] < 0) clipMax[0] = 0;
    else clipMax[0] = boundMax[0];
    if (boundMax[0] >= 320) clipMax[0] = 319;
    if (boundMin[1] < 0) clipMin[1] = 0;
    else clipMin[1] = boundMin[1];
    if (boundMin[1] >= 240) clipMin[1] = 239;
    if (boundMax[1] < 0) clipMax[1] = 0;
    else clipMax[1] = boundMax[1];
    if (boundMax[1] >= 240) clipMax[1] = 239;
    rect.x = clipMin[0];
    rect.y = clipMin[1] + ((1 - page) * 240);
    rect.w = clipMax[0] - clipMin[0] + 1;
    rect.h = clipMax[1] - clipMin[1] + 1;
    if (rect.h % 2 == 1) rect.h++;
    DrawSync(0);
    StoreImage(&rect, B_00001D00);
    func_00000528((DVECTOR *)quad, slopes);
    func_00000120((DVECTOR *)quad, order0);
    func_00000324((DVECTOR *)quad, order1);
    for (edge = 0; edge < 4; edge++) {
        slope0[edge] = slopes[(order0[edge] + 3) % 4];
        slope1[edge] = slopes[order1[edge]];
        y0[edge] = quad[order0[edge] * 2 + 1];
        y1[edge] = quad[order1[edge] * 2 + 1];
    }
    start0 = quad[order0[0] * 2] << 12;
    start1 = quad[order1[0] * 2] << 12;
    DrawSync(0);
    ScanXY0(boundMin[1], clipMin[0], clipMin[1], clipMax[0], clipMax[1], start0, start1,
            &buffer, y0, slope0, y1, slope1, 128, image);
    LoadImage(&rect, B_00001D00);
    SetGeomOffset(ofx, ofy);
    SetGeomScreen(screen);
    PopMatrix();
}
