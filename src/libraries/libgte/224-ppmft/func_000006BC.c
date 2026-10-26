#include "common.h"
#include <sys/types.h>
#include <libgte.h>

static int func_000006BC(int *p, int n)
{
    int i;
    int v;
    int best;

    best = 0;
    for (i = 0; i < n; i++) {
        v = p[i];
        if (v < 0)
            v = -v;
        if (best < v)
            best = v;
    }
    return best;
}
