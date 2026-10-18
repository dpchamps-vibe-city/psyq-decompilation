.include "build/libraries/nonmatchings/libcard_9/__library_member_symbols.s"
.include "build/libraries/nonmatchings/libcard_9/__library_member_assembly.s"
/* PSX parked attempt: original pre-switch sources, preserved without assembly rewriting. */
#if 0
/* Preserved pre-switch part: _shared-0.h */
/* Original TU: library-input/redux/libcard/9-a80.o[0] 9-a80.o
 * sha256: 9ff8aeebd1c6cb1ad072ac0a76eccc45873542a3a8cc5d0d133b91a6690a3402
 * One original member, one TU. Replace INCLUDE_ASM stubs with C; keep neighboring code/data.
 * Functions: _new_card
 */
#include "common.h"
#include "include_asm.h"


/* Preserved pre-switch part: _new_card.c */
#include "library/psx_bios_tailjump.h"

void _new_card(void) {
    PSX_BIOS_TAILJUMP(0xb0, 0x50);
}

#endif
