#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include "libgte-regs.h"

long otz2p(long otz, long projection) {
    long z;
    long d;
    long dqb;
    z = otz;
    if (z == 0) {
        return 0;
    }
    gte_ReadDQA(otz);
    gte_ReadDQB(dqb);
    d = otz * (projection << 2) / z + (dqb >> 12);
    if (d > 0x1000) {
        d = 0x1000;
    }
    if (d < 0) {
        d = 0;
    }
    return d;
}
