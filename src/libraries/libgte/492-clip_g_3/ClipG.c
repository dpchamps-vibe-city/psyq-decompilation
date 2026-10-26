#include "common.h"
#include <sys/types.h>
#include <libgte.h>

extern EVECTOR *CLIPEvbf;
extern long CLIPFarz, CLIPNearz, CLIPHdkx, CLIPHdky;
static void ZClipG(EVECTOR *a, EVECTOR *b, EVECTOR *out, long num, long den);

long ClipG(long n, EVECTOR **evmx)
{
    long i, count, used;
    long d0, plane;
    long z0, z1, den;
    EVECTOR **tmp;
    EVECTOR *a, *b;

    used = n;
    tmp = evmx + 10;
    count = 0;
    for (i = 0; i < n; i++) {
        a = evmx[i];
        b = (i + 1 == n) ? evmx[0] : evmx[i + 1];
        z0 = a->sxyz.vz;
        plane = CLIPFarz;
        if (z0 < plane) {
            tmp[count++] = a;
            z1 = b->sxyz.vz;
            if (z1 >= plane) {
                den = a->sxyz.vz - z1;
                ZClipG(b, a, &CLIPEvbf[used], plane - z1, den);
                tmp[count++] = &CLIPEvbf[used++];
            }
        } else {
            z1 = b->sxyz.vz;
            if (z1 < plane) {
                den = z1 - z0;
                ZClipG(a, b, &CLIPEvbf[used], plane - z0, den);
                tmp[count++] = &CLIPEvbf[used++];
            }
        }
    }
    n = count;
    count = 0;
    for (i = 0; i < n; i++) {
        a = tmp[i];
        b = (i + 1 == n) ? tmp[0] : tmp[i + 1];
        z0 = a->sxyz.vz;
        plane = CLIPNearz;
        if (z0 >= plane) {
            evmx[count++] = a;
            z1 = b->sxyz.vz;
            if (z1 < plane) {
                den = a->sxyz.vz - z1;
                ZClipG(b, a, &CLIPEvbf[used], plane - z1, den);
                evmx[count++] = &CLIPEvbf[used++];
            }
        } else {
            z1 = b->sxyz.vz;
            if (z1 >= plane) {
                den = z1 - z0;
                ZClipG(a, b, &CLIPEvbf[used], plane - z0, den);
                evmx[count++] = &CLIPEvbf[used++];
            }
        }
    }
    n = count;
    count = 0;
    for (i = 0; i < n; i++) {
        a = evmx[i];
        b = (i + 1 == n) ? evmx[0] : evmx[i + 1];
        if (a->sxyz.vy >= -a->chy) {
            tmp[count++] = a;
            if (b->sxyz.vy < -b->chy) {
                d0 = b->sxyz.vz + ((CLIPHdky * b->sxyz.vy) >> 12);
                den = a->sxyz.vz + ((CLIPHdky * a->sxyz.vy) >> 12);
                ZClipG(b, a, &CLIPEvbf[used], d0, d0 - den);
                tmp[count++] = &CLIPEvbf[used++];
            }
        } else if (b->sxyz.vy >= -b->chy) {
            d0 = a->sxyz.vz + ((CLIPHdky * a->sxyz.vy) >> 12);
            den = b->sxyz.vz + ((CLIPHdky * b->sxyz.vy) >> 12);
            ZClipG(a, b, &CLIPEvbf[used], d0, d0 - den);
            tmp[count++] = &CLIPEvbf[used++];
        }
    }
    n = count;
    count = 0;
    for (i = 0; i < n; i++) {
        a = tmp[i];
        b = (i + 1 == n) ? tmp[0] : tmp[i + 1];
        if (a->sxyz.vy <= a->chy) {
            evmx[count++] = a;
            if (b->sxyz.vy > b->chy) {
                d0 = b->sxyz.vz - ((CLIPHdky * b->sxyz.vy) >> 12);
                den = a->sxyz.vz - ((CLIPHdky * a->sxyz.vy) >> 12);
                ZClipG(b, a, &CLIPEvbf[used], d0, d0 - den);
                evmx[count++] = &CLIPEvbf[used++];
            }
        } else if (b->sxyz.vy <= b->chy) {
            d0 = a->sxyz.vz - ((CLIPHdky * a->sxyz.vy) >> 12);
            den = b->sxyz.vz - ((CLIPHdky * b->sxyz.vy) >> 12);
            ZClipG(a, b, &CLIPEvbf[used], d0, d0 - den);
            evmx[count++] = &CLIPEvbf[used++];
        }
    }
    n = count;
    count = 0;
    for (i = 0; i < n; i++) {
        a = evmx[i];
        b = (i + 1 == n) ? evmx[0] : evmx[i + 1];
        if (a->sxyz.vx >= -a->chx) {
            tmp[count++] = a;
            if (b->sxyz.vx < -b->chx) {
                d0 = b->sxyz.vz + ((CLIPHdkx * b->sxyz.vx) >> 12);
                den = a->sxyz.vz + ((CLIPHdkx * a->sxyz.vx) >> 12);
                ZClipG(b, a, &CLIPEvbf[used], d0, d0 - den);
                tmp[count++] = &CLIPEvbf[used++];
            }
        } else if (b->sxyz.vx >= -b->chx) {
            d0 = a->sxyz.vz + ((CLIPHdkx * a->sxyz.vx) >> 12);
            den = b->sxyz.vz + ((CLIPHdkx * b->sxyz.vx) >> 12);
            ZClipG(a, b, &CLIPEvbf[used], d0, d0 - den);
            tmp[count++] = &CLIPEvbf[used++];
        }
    }
    n = count;
    count = 0;
    for (i = 0; i < n; i++) {
        a = tmp[i];
        b = (i + 1 == n) ? tmp[0] : tmp[i + 1];
        if (a->sxyz.vx <= a->chx) {
            evmx[count++] = a;
            if (b->sxyz.vx > b->chx) {
                d0 = b->sxyz.vz - ((CLIPHdkx * b->sxyz.vx) >> 12);
                den = a->sxyz.vz - ((CLIPHdkx * a->sxyz.vx) >> 12);
                ZClipG(b, a, &CLIPEvbf[used], d0, d0 - den);
                evmx[count++] = &CLIPEvbf[used++];
            }
        } else if (b->sxyz.vx <= b->chx) {
            d0 = a->sxyz.vz - ((CLIPHdkx * a->sxyz.vx) >> 12);
            den = b->sxyz.vz - ((CLIPHdkx * b->sxyz.vx) >> 12);
            ZClipG(a, b, &CLIPEvbf[used], d0, d0 - den);
            evmx[count++] = &CLIPEvbf[used++];
        }
    }
    n = count;
    return n;
}
