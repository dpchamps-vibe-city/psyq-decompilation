#include "common.h"

short *GsSetBetaParam(short beta1, short beta2, void *sequence,
                      long unused, void *animation)
{
    long square, cube, denominator;
    long c0, c1, c2, c3, c4, c5, c6, c7, c8, c9, c10, c11;
    unsigned long *indices, *parameters;
    unsigned short index;
    short *out;

    square = (beta1 * beta1) >> 10;
    cube = (square * beta1) >> 10;
    denominator = 2 * cube + 4 * square + 4 * beta1 + beta2 + 2048;
    c0 = ((-2 * cube) << 12) / denominator;
    c1 = ((cube + square + beta1 + beta2) << 13) / denominator;
    c2 = -((square + beta1 + beta2 + 1024) << 13) / denominator;
    c3 = (3 * cube) << 13;
    c3 /= denominator;
    c4 = ((-3 * (2 * (cube + square) + beta2)) << 12) / denominator;
    c5 = ((3 * (2 * square + beta2)) << 12) / denominator;
    c6 = -((3 * cube) << 13) / denominator;
    c7 = ((3 * (cube - beta1)) << 13) / denominator;
    c8 = ((3 * beta1) << 13) / denominator;
    c9 = (cube << 13) / denominator;
    c10 = ((4 * (cube + beta1) + beta2) << 12) / denominator;
    c11 = 0x800000 / denominator;

    indices = *(unsigned long **)((unsigned char *)animation + 12);
    parameters = *(unsigned long **)((unsigned char *)animation + 16);
    index = *(unsigned short *)((unsigned char *)sequence + 24);
    out = (short *)(parameters + *(unsigned short *)(indices + index));
    out[0] = c0;
    out[1] = c1;
    out[2] = c2;
    out[3] = c3;
    out[4] = c4;
    out[5] = c5;
    out[6] = c6;
    out[7] = c7;
    out[8] = c8;
    out[9] = c9;
    out[10] = c10;
    out[11] = c11;
    return out;
}
