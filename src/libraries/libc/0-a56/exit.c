#include "library/psx_bios_tailjump.h"

void exit() {
    PSX_BIOS_TAILJUMP(0xb0, 0x38);
}
