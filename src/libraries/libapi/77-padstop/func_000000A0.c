#include "library/api-pad-patch.h"

static s32 func_000000A0(void) {
    EnterCriticalSection();
    SysDeqIntRP(1, &apiPadPatchNext);
    ExitCriticalSection();
    return 1;
}
