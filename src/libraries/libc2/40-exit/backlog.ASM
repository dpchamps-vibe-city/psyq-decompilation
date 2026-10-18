.include "build/libraries/nonmatchings/libc2_40/__library_member_symbols.s"
.include "build/libraries/nonmatchings/libc2_40/__library_member_assembly.s"
/* PSX parked attempt: original pre-switch sources, preserved without assembly rewriting. */
#if 0
/* Preserved pre-switch part: _shared-0.h */
/* Original TU: library-input/redux/libc2/40-exit.o[0] 40-exit.o
 * sha256: c46a969049c8a7b6f901d07514d0a3d21e29f8fd82d5d4fe0c4b905cbb4639c1
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: exit
 */
#include "common.h"
#include "include_asm.h"


/* Preserved pre-switch part: exit.c */
#include "library/psx_bios_tailjump.h"

void exit() {
    PSX_BIOS_TAILJUMP(0xb0, 0x38);
}

#endif
