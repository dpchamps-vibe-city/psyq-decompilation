.include "build/libraries/nonmatchings/libc_37/__library_member_symbols.s"
.include "build/libraries/nonmatchings/libc_37/__library_member_assembly.s"
/* PSX parked attempt: original pre-switch sources, preserved without assembly rewriting. */
#if 0
/* Preserved pre-switch part: _shared-0.h */
/* Original TU: library-input/redux/libc/37-c47.o[0] 37-c47.o
 * sha256: 04585dccf793bdc0d01d69269d0f1cdf12543b74426dd6be31be8773887e1715
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: rand
 */
#include "common.h"
#include "include_asm.h"


/* Preserved pre-switch part: rand.c */
#include "library/psx_bios_tailjump.h"

int rand(void) {
    PSX_BIOS_TAILJUMP(0xa0, 0x2f);
}

#endif
