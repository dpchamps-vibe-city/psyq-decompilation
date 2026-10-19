/* Original member: LIBAPI.LIB PADSTOP.OBJ */
#include "common.h"
#include "library/api-pad-patch.h"

void DisablePAD(void);
void StopPAD2(void);
static s32 DequeuePadPatchRP(void);
void SetInitPadFlag(s32);

void StopPAD(void) {
    DisablePAD();
    StopPAD2();
    DequeuePadPatchRP();
    SetInitPadFlag(0);
}

static s32 DequeuePadPatchRP(void) {
    EnterCriticalSection();
    SysDeqIntRP(1, &apiPadPatchNext);
    ExitCriticalSection();
    return 1;
}
