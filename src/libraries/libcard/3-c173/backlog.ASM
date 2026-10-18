.include "build/libraries/nonmatchings/libcard_3/__library_member_symbols.s"
.include "build/libraries/nonmatchings/libcard_3/__library_member_assembly.s"
/* PSX parked attempt: original pre-switch sources, preserved without assembly rewriting. */
#if 0
/* Preserved pre-switch part: _shared-0.h */
/* Original TU: library-input/redux/libcard/3-c173.o[0] 3-c173.o
 * sha256: 930011120785466eaf7e8467a458c9bab7ec227e1ba06d5d4141ef04582d5575
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: _card_auto
 */
#include "common.h"
#include "include_asm.h"


/* Preserved pre-switch part: _card_auto.c */
#include "library/psx_bios_tailjump.h"

long _card_auto(long val) {
    PSX_BIOS_TAILJUMP(0xa0, 0xad);
}

#endif
