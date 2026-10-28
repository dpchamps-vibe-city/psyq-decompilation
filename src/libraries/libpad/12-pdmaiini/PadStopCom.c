#include "libpad-com-stop.h"

void PadStopCom(void) {
    EnterCriticalSection();
    ChangeClearRCnt(3, 1);
    SysDeqIntRP(2, &_padVsyncParam);
    ExitCriticalSection();
}
