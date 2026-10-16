#include "common.h"

void DisablePAD(void);
void StopPAD2(void);
s32 func_000000A0(void);
void SetInitPadFlag(s32);

void StopPAD(void) {
    DisablePAD();
    StopPAD2();
    func_000000A0();
    SetInitPadFlag(0);
}
