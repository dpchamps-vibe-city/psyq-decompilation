.include "build/libraries/nonmatchings/libcard_12/__library_member_symbols.s"
.include "build/libraries/nonmatchings/libcard_12/__library_member_assembly.s"
/* PSX parked attempt: original pre-switch sources, preserved without assembly rewriting. */
#if 0
/* Preserved pre-switch part: _shared-0.h */
/* Original TU: library-input/redux/libcard/12-a93.o[0] 12-a93.o
 * sha256: 212843c55bc02a75bb2ad7a7529fee8a8fc01c321faa8e6d1994b893dbd9bfc2
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: _card_wait
 */
#include "common.h"
#include "include_asm.h"


/* Preserved pre-switch part: _card_wait.c */
#include "library/psx_bios_tailjump.h"

long _card_wait(long drv) {
    PSX_BIOS_TAILJUMP(0xb0, 0x5d);
}

#endif
