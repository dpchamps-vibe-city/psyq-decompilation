#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>

void GsMulCoord3(MATRIX *m1, MATRIX *m2) {
    VECTOR sp10;

    ApplyMatrixLV(m1, (VECTOR *) m2->t, &sp10);
    MulMatrix(m1, m2);
    m1->t[0] = sp10.vx + m1->t[0];
    m1->t[1] = sp10.vy + m1->t[1];
    m1->t[2] = sp10.vz + m1->t[2];
}
