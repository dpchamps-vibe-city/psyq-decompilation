#include "common.h"
#include <sys/types.h>
#include <libgte.h>

void EigenMatrix(MATRIX *m, MATRIX *t)
{
    MATRIX a;
    long d[9];
    VECTOR v0, v1, v2, v3, v4, v5;
    long i, j;
    long max;
    unsigned long index;

    a.m[0][0] = m->m[0][0] - 4096;
    a.m[0][1] = m->m[0][1];
    a.m[0][2] = m->m[0][2];
    a.m[1][0] = m->m[1][0];
    a.m[1][1] = m->m[1][1] - 4096;
    a.m[1][2] = m->m[1][2];
    a.m[2][0] = m->m[2][0];
    a.m[2][1] = m->m[2][1];
    a.m[2][2] = m->m[2][2] - 4096;

    d[0] = a.m[1][1] * a.m[2][2] - a.m[1][2] * a.m[2][1];
    d[1] = a.m[1][0] * a.m[2][2] - a.m[1][2] * a.m[2][0];
    d[2] = a.m[1][0] * a.m[2][1] - a.m[1][1] * a.m[2][0];
    d[3] = a.m[0][1] * a.m[2][2] - a.m[0][2] * a.m[2][1];
    d[4] = a.m[0][0] * a.m[2][2] - a.m[0][2] * a.m[2][0];
    d[5] = a.m[0][0] * a.m[2][1] - a.m[0][1] * a.m[2][0];
    d[6] = a.m[0][1] * a.m[1][2] - a.m[0][2] * a.m[1][1];
    d[7] = a.m[0][0] * a.m[1][2] - a.m[0][2] * a.m[1][0];
    d[8] = a.m[0][0] * a.m[1][1] - a.m[0][1] * a.m[1][0];

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (d[i * 3 + j] < 0) d[i * 3 + j] = -d[i * 3 + j];
        }
    }
    index = 0;
    max = d[0];
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (max < d[i * 3 + j]) {
                index = i * 3 + j;
                max = d[i * 3 + j];
            }
        }
    }
    switch (index) {
    case 6: case 7: case 8:
        v0.vx = a.m[0][0];
        v0.vy = a.m[0][1];
        v0.vz = a.m[0][2];
        v1.vx = a.m[1][0];
        v1.vy = a.m[1][1];
        v1.vz = a.m[1][2];
        break;
    case 3: case 4: case 5:
        v0.vx = a.m[0][0];
        v0.vy = a.m[0][1];
        v0.vz = a.m[0][2];
        v1.vx = a.m[2][0];
        v1.vy = a.m[2][1];
        v1.vz = a.m[2][2];
        break;
    case 0: case 1: case 2:
        v0.vx = a.m[1][0];
        v0.vy = a.m[1][1];
        v0.vz = a.m[1][2];
        v1.vx = a.m[2][0];
        v1.vy = a.m[2][1];
        v1.vz = a.m[2][2];
        break;
    }
    OuterProduct12(&v0, &v1, &v2);
    VectorNormal(&v2, &v3);
    t->m[0][0] = v3.vx;
    t->m[1][0] = v3.vy;
    t->m[2][0] = v3.vz;
    VectorNormal(&v0, &v5);
    t->m[0][1] = v5.vx;
    t->m[1][1] = v5.vy;
    t->m[2][1] = v5.vz;
    OuterProduct12(&v3, &v5, &v2);
    VectorNormal(&v2, &v4);
    t->m[0][2] = v4.vx;
    t->m[1][2] = v4.vy;
    t->m[2][2] = v4.vz;
}
