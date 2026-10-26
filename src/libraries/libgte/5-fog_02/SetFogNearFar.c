#include "common.h"
#include <sys/types.h>
#include <libgte.h>

void SetDQA(s32);
void SetDQB(s32);

void SetFogNearFar(long a, long b, long h) {
    s32 d;
    s32 dqa;
    s32 dqb;

    d = b - a;
    if (d < 100) {
        return;
    }
    dqa = (s32) (((s32) (-a * b) / d) << 8) / h;
    dqb = ((s32) (b << 12) / d) << 12;
    if (dqa < -0x8000) {
        dqa = -0x8000;
    }
    if (dqa > 0x7FFF) {
        dqa = 0x7FFF;
    }
    SetDQA(dqa);
    SetDQB(dqb);
}
