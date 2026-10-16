#include "library/api-pad-patch.h"

static s32 func_00000254(void);
static s32 func_000002BC(void);

static s32 func_000001DC(void) {
    ApiPadPatchHandler *handlers;
    ApiPadPatchHandler *slot;
    void *queue;

    EnterCriticalSection();
    slot = apiPadPatchHandlers;
    handlers = slot;
    queue = (u8 *)handlers - 4;
    slot = handlers++;
    *slot = func_00000254;
    *handlers = func_000002BC;
    apiPadPatchNext = 0;
    apiPadPatchReserved = 0;
    SysDeqIntRP(1, queue);
    SysEnqIntRP(1, queue);
    ExitCriticalSection();
    return 1;
}
