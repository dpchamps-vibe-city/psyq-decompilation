#include "common.h"

void StopCARD2(void);
void _ExitCard(void);

s32 StopCARD(void) {
    StopCARD2();
    _ExitCard();
    return 0;
}
