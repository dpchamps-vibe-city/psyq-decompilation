.include "build/libraries/nonmatchings/libapi_56/__library_member_symbols.s"
.include "build/libraries/nonmatchings/libapi_56/__library_member_assembly.s"
/* PSX parked attempt: original pre-switch sources, preserved without assembly rewriting. */
#if 0
/* Preserved pre-switch part: _shared-0.h */
/* Original TU: library-input/redux/libapi/56-a68.o[0] 56-a68.o
 * sha256: 529d9f86ea15ba3f45e96a152680c0620c43ab1d782cc2f5a75f609333c71e0c
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: rename
 */
#include "common.h"
#include "include_asm.h"


/* Preserved pre-switch part: rename.c */
#include "library/psx_bios_tailjump.h"

long rename(char *arg0, char *arg1) {
    PSX_BIOS_TAILJUMP(0xb0, 0x44);
}

#endif
