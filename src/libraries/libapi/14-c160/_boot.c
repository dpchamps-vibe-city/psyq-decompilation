#include "library/psx_bios_tailjump.h"

void _boot(void) {
    PSX_BIOS_TAILJUMP(0xa0, 0xa0);
}
