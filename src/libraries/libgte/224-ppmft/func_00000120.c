#include "common.h"
#include <sys/types.h>
#include <libgte.h>

static void func_00000120(DVECTOR *v, int *order)
{
    int i;
    int min, max;

    for (i = 0; i < 4; i++)
        order[i] = -1;

    max = v[0].vy;
    min = max;
    for (i = 3; i >= 0; i--) {
        if (min >= v[i].vy) {
            order[0] = i;
            min = v[i].vy;
        }
    }

    if (order[0] == 0) {
        if (v[0].vy == v[3].vy) {
            order[0] = 3;
            if (v[3].vy == v[2].vy) {
                order[0] = 2;
                if (v[2].vy == v[1].vy)
                    order[0] = 1;
            }
        }
    }

    for (i = 0; i < 4; i++) {
        if (v[i].vy >= max) {
            order[1] = i;
            max = v[i].vy;
        }
    }

    if (order[0] == 3) {
        if (v[3].vy == v[0].vy) {
            order[1] = 0;
            if (v[0].vy == v[1].vy) {
                order[1] = 1;
                if (v[1].vy == v[2].vy)
                    order[1] = 2;
            }
        }
    }

    for (i = 0; i < 2; i++) {
        if ((order[0] + 3) % 4 == order[1])
            return;
        order[2] = order[1];
        order[1] = (order[0] + 3) % 4;
        if ((order[0] + 2) % 4 == order[2])
            return;
        order[3] = order[2];
        order[2] = (order[0] + 2) % 4;
    }
}
