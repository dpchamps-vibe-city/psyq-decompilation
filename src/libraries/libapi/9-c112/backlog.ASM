.include "build/libraries/nonmatchings/libapi_9/__library_member_symbols.s"
.include "build/libraries/nonmatchings/libapi_9/__library_member_assembly.s"
/* PSX parked attempt: original pre-switch sources, preserved without assembly rewriting. */
#if 0
/* Preserved pre-switch part: _shared-0.h */
/* Original TU: library-input/redux/libapi/9-c112.o[0] 9-c112.o
 * sha256: 9df0200bbf8e3ab94444e64f82ee4e7cd40fc1fcec54badf9f2591c89b823ad6
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: _bu_init
 */
#include "common.h"
#include "include_asm.h"


/* Preserved pre-switch part: _bu_init.c */
#include "library/psx_bios_tailjump.h"

void _bu_init(void) {
    PSX_BIOS_TAILJUMP(0xa0, 0x70);
}

#endif
