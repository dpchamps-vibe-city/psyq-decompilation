#include "common.h"

void StartCARD2(void);

s32 StartCARD(void) {
    s32 temp_s0;

    temp_s0 = EnterCriticalSection();
    StartCARD2();
    ChangeClearPAD(0);
    if (temp_s0 == 1) {
        ExitCriticalSection();
    }
    return 0;
}
