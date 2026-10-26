#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>

typedef struct {
    s16 x;
    s16 y;
    s16 z;
    u8 unk6;
    u8 unk7;
    u8 r;
    u8 g;
    u8 b;
    u8 cd;
} VecCol;

void func_00000A8C(VecCol *dst, VecCol *a, VecCol *b) {
    dst->x = (a->x + b->x) / 2;
    dst->y = (a->y + b->y) / 2;
    dst->z = (a->z + b->z) / 2;
    dst->r = (a->r + b->r) >> 1;
    dst->g = (a->g + b->g) >> 1;
    dst->b = (a->b + b->b) >> 1;
    dst->cd = a->cd;
    dst->unk6 = (a->unk6 + b->unk6) >> 1;
    dst->unk7 = (a->unk7 + b->unk7) >> 1;
}
