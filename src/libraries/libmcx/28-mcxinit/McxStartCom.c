#include "common.h"
#include <libapi.h>
#include <libmcx.h>
#include "libmcx_init.h"

static void func_00000120(int priority, McxInterruptRecord *record);

void McxStartCom(void) {
    volatile unsigned int *interrupt;

    EnterCriticalSection();
    SysDeqIntRP(2, &_mcxTblCardEnt);
    func_00000120(2, &_mcxTblCardEnt);
    interrupt = D_00000180;
    interrupt[0] = ~1;
    interrupt[1] |= 1;
    ChangeClearRCnt(3, 0);
    ExitCriticalSection();
}
