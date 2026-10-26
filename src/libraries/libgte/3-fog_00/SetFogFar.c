#include "common.h"
#include <sys/types.h>
#include <libgte.h>

void SetDQA(s32);
void SetDQB(s32);

void SetFogFar(long a, long h) {
    SetDQA(((-a) << 6) / h);
    SetDQB(0x1400000);
}
