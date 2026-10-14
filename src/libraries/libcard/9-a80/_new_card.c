#include "library/psx_bios_tailjump.h"

void _new_card(void) {
    PSX_BIOS_TAILJUMP(0xb0, 0x50);
}
