.include "build/libraries/nonmatchings/libapi_58/__library_member_symbols.s"
.include "build/libraries/nonmatchings/libapi_58/__library_member_assembly.s"
/* PSX parked attempt: original pre-switch sources, preserved without assembly rewriting. */
#if 0
/* Preserved pre-switch part: _shared-0.h */
/* Original TU: library-input/redux/libapi/58-a70.o[0] 58-a70.o
 * sha256: e0c62386cd3f8f8b871da979e05b24eeb64dfc55d8a37110dc69f09968d413c4
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: undelete
 */
#include "common.h"
#include "include_asm.h"


/* Preserved pre-switch part: undelete.c */
#include "library/psx_bios_tailjump.h"

long undelete(char *arg0) {
    PSX_BIOS_TAILJUMP(0xb0, 0x46);
}

#endif
