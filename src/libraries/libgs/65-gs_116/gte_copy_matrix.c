#include "common.h"

typedef struct {
    u16 m[9];
    s32 v[3];
} GteMatrix;

void gte_copy_matrix(void *src, void *dst) {
    GteMatrix *s = src;
    GteMatrix *d = dst;
    d->m[0] = s->m[0];
    d->m[1] = s->m[1];
    d->m[2] = s->m[2];
    d->m[3] = s->m[3];
    d->m[4] = s->m[4];
    d->m[5] = s->m[5];
    d->m[6] = s->m[6];
    d->m[7] = s->m[7];
    d->m[8] = s->m[8];
    d->v[0] = s->v[0];
    d->v[1] = s->v[1];
    d->v[2] = s->v[2];
}
