.include "build/libraries/nonmatchings/libcard_8/__library_member_symbols.s"
.include "build/libraries/nonmatchings/libcard_8/__library_member_assembly.s"
/* PSX parked attempt: original pre-switch sources, preserved without assembly rewriting. */
#if 0
/* Preserved pre-switch part: _shared-0.h */
/* Original TU: library-input/redux/libcard/8-a79.o[0] 8-a79.o
 * sha256: 50c1eb60dff7ef98a5978dfe4cc8e8abeb15818a5c9986936b93857d1d2ce2f8
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: _card_read
 */
#include "common.h"
#include "include_asm.h"


/* Preserved pre-switch part: _card_read.c */
#include "library/psx_bios_tailjump.h"

long _card_read(long chan, long block, unsigned char *buf) {
    PSX_BIOS_TAILJUMP(0xb0, 0x4f);
}

#endif
