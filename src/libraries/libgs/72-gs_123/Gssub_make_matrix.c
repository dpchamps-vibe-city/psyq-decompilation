#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>

void Gssub_make_matrix(MATRIX *out, short x, short y, int mode)
{
    signed char sub;

    memcpy(out, &GsIDMATRIX, sizeof(MATRIX));

    sub = mode - 0x58;
    switch (sub) {
    case 0:
    case 32:
        out->m[1][1] = y;
        out->m[2][2] = y;
        out->m[1][2] = -x;
        out->m[2][1] = x;
        break;
    case 1:
    case 33:
        out->m[0][0] = y;
        out->m[2][2] = y;
        out->m[0][2] = x;
        out->m[2][0] = -x;
        break;
    case 2:
    case 34:
        out->m[0][0] = y;
        out->m[1][1] = y;
        out->m[0][1] = -x;
        out->m[1][0] = x;
        break;
    default:
        break;
    }
}
