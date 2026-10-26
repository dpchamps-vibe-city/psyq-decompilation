#include "common.h"
#include <sys/types.h>
#include <libgte.h>
#include "libgte-regs.h"

long p2otz(long p, long projection) {
    s32 d;
    s32 dqa;
    s32 dqb;

    gte_ReadDQA(dqa);
    gte_ReadDQB(dqb);
    d = p - (dqb >> 12);
    if (d != 0) {
        return dqa * projection * 4 / d;
    }
    return -1;
}
