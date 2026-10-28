#include "libpad-com.h"

void PadStartCom(void) {
    volatile u32 *irq;

    _padIntExec = 0;
    EnterCriticalSection();
    SysDeqIntRP(2, &_padVsyncParam);
    SysEnqIntRP(2, &_padVsyncParam);
    irq = D_00000180;
    irq[0] = -2;
    irq[1] |= 1;
    ChangeClearRCnt(3, 0);
    ExitCriticalSection();
    _padFuncClrInfo(_padInfoDir);
    _padFuncClrInfo(_padInfoDir + 1);
    _padRestPeriod[0] = _padRestPeriod[1] = 0;
    _padIntExec = 1;
}
