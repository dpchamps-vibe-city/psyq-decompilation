#include "common.h"
#include <libapi.h>
#include <libmcx.h>
#include "libmcx_init.h"

void McxStopCom(void) {
    EnterCriticalSection();
    _mcxStopFastDsr();
    SysDeqIntRP(2, &_mcxTblCardEnt);
    ExitCriticalSection();
}
