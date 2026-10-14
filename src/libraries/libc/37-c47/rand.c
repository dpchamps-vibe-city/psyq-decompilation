#include "library/psx_bios_tailjump.h"

int rand(void) {
    PSX_BIOS_TAILJUMP(0xa0, 0x2f);
}
