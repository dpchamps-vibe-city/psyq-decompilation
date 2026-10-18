.include "build/libraries/nonmatchings/libcard_7/__library_member_symbols.s"
.include "build/libraries/nonmatchings/libcard_7/__library_member_assembly.s"
/* PSX parked attempt: original pre-switch sources, preserved without assembly rewriting. */
#if 0
/* Preserved pre-switch part: _shared-0.h */
/* Original TU: library-input/redux/libcard/7-a78.o[0] 7-a78.o
 * sha256: 2a1244c5feed6b41e099c6459faaa509caeb8ee8af762cd1edfeb76ad45b7e36
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: _card_write
 */
#include "common.h"
#include "include_asm.h"


/* Preserved pre-switch part: _card_write.c */
#include "library/psx_bios_tailjump.h"

long _card_write(long chan, long block, unsigned char *buf) {
    PSX_BIOS_TAILJUMP(0xb0, 0x4e);
}

#endif
