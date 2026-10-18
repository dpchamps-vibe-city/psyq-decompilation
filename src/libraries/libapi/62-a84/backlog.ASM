.include "build/libraries/nonmatchings/libapi_62/__library_member_symbols.s"
.include "build/libraries/nonmatchings/libapi_62/__library_member_assembly.s"
/* PSX parked attempt: original pre-switch sources, preserved without assembly rewriting. */
#if 0
/* Preserved pre-switch part: _shared-0.h */
/* Original TU: library-input/redux/libapi/62-a84.o[0] 62-a84.o
 * sha256: 16fe291777697fb715d65f992d631003774705f6946f859524b6942a9a3c39e1
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: _get_errno
 */
#include "common.h"
#include "include_asm.h"


/* Preserved pre-switch part: _get_errno.c */
#include "library/psx_bios_tailjump.h"

long _get_errno(void) {
    PSX_BIOS_TAILJUMP(0xb0, 0x54);
}

#endif
