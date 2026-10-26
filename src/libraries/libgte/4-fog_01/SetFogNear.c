#include "common.h"
#include <sys/types.h>
#include <libgte.h>

void SetDQA(s32);
void SetDQB(s32);

void SetFogNear(long a, long h) {
    SetDQA(-(a * 0x140) / h);
    SetDQB(0x1400000);
}
