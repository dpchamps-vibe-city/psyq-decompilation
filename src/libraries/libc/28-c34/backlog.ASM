.include "build/libraries/nonmatchings/libc_28/__library_member_symbols.s"
.include "build/libraries/nonmatchings/libc_28/__library_member_assembly.s"
/* PSX parked attempt: original pre-switch sources, preserved without assembly rewriting. */
#if 0
/* Preserved pre-switch part: _shared-0.h */
/* Original TU: library-input/redux/libc/28-c34.o[0] 28-c34.o
 * sha256: 18517eaf92568dc9950d77adab423907477d18423effc76b3694b1ca70b2763e
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: strcspn
 */
#include "common.h"
#include "include_asm.h"


/* Preserved pre-switch part: strcspn.c */
#include "library/psx_bios_tailjump.h"

int strcspn(const char *arg0, const char *arg1) {
    PSX_BIOS_TAILJUMP(0xa0, 0x22);
}

#endif
