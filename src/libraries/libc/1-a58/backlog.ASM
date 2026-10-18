.include "build/libraries/nonmatchings/libc_1/__library_member_symbols.s"
.include "build/libraries/nonmatchings/libc_1/__library_member_assembly.s"
/* PSX parked attempt: original pre-switch sources, preserved without assembly rewriting. */
#if 0
/* Preserved pre-switch part: _shared-0.h */
/* Original TU: library-input/redux/libc/1-a58.o[0] 1-a58.o
 * sha256: 999fda80403a7914d491154247b86b1250f504dd213b2ab30e88801d0e89c170
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: getc
 */
#include "common.h"
#include "include_asm.h"


/* Preserved pre-switch part: getc.c */
#include "library/psx_bios_tailjump.h"

char getc(int arg0) {
    PSX_BIOS_TAILJUMP(0xb0, 0x3a);
}

#endif
