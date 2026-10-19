/* Original TU: library-input/psyq/LIB/LIBAPI.LIB[77] PADSTOP.OBJ
 * sha256: 8bd903c9921915361a11b7598c504eaeb3d6293ce1200d1656cf21f40fdfacf6
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: StopPAD
 */
#include "common.h"
#include "include_asm.h"

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
#include "library/api-pad-patch.h"

static s32 func_000000A0(void) {
    EnterCriticalSection();
    SysDeqIntRP(1, &apiPadPatchNext);
    ExitCriticalSection();
    return 1;
}
